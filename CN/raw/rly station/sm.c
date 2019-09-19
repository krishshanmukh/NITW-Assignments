//bind ip 127.0.0.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <sys/un.h>
#include <sys/uio.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h> // for inet_pton

#define derror(msg) {printf("%s\n",msg); exit(0);}
#define SA_IN struct sockaddr_in
#define SA struct sockaddr
#define SOCK_PATH "./temp_socket"

int rsfd;

static int send_file_descriptor(
 	int socket, /* Socket through which the file descriptor is passed */
 	int fd_to_send) /* File descriptor to be passed, could be another socket */
{
 	struct msghdr message;
 	struct iovec iov[1];
 	struct cmsghdr *control_message = NULL;
 	char ctrl_buf[CMSG_SPACE(sizeof(int))];
 	char data[2];

 	memset(&message, 0, sizeof(struct msghdr));
 	memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

 	/* We are passing at least one byte of data so that recvmsg() will not return 0 */
 	data[0] = ' ';
 	data[1] = '\0';
 	iov[0].iov_base = data;
 	iov[0].iov_len = sizeof(data);

 	message.msg_name = NULL;
 	message.msg_namelen = 0;
 	message.msg_iov = iov;
 	message.msg_iovlen = 1;
 	message.msg_controllen =  CMSG_SPACE(sizeof(int));
 	message.msg_control = ctrl_buf;

 	control_message = CMSG_FIRSTHDR(&message);
 	control_message->cmsg_level = SOL_SOCKET;
 	control_message->cmsg_type = SCM_RIGHTS;
 	control_message->cmsg_len = CMSG_LEN(sizeof(int));

 	*((int *) CMSG_DATA(control_message)) = fd_to_send;

 	int temp;
 	
 	
 	return sendmsg(socket, &message, 0);
}

int queue[10],start,end;


void enqueue(int x)
{
	if(start==-1)
		start++;
	end = (end+1)%10;
	queue[end] = x;
}

int dequeue()
{
	if(start==-1)
		return -1;
	else
	{
		int x = queue[start];
		if(start==end)
			start=end=-1;
		else
			start = (start+1)%10;
		return x;
	}
}

void announce(int ch)
{
	char buf[4096];
	memset(buf, 0, sizeof(buf));
	
	SA_IN to_addr;
	memset(&to_addr, 0, sizeof(SA_IN));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &to_addr.sin_addr);
	//to_addr.sin_addr.s_addr = INADDR_ANY;

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.3", &src_addr.sin_addr);
	
	struct ip* iph = (struct ip*)buf;

	iph->ip_v=4;
    iph->ip_hl=5;
    iph->ip_tos=0;
    iph->ip_len = sizeof(struct iphdr);
    iph->ip_id = htonl (54321);;
    iph->ip_off=0;
    iph->ip_ttl=255;
    iph->ip_p=251;
    iph->ip_sum=0;
    iph->ip_src.s_addr = inet_addr("127.0.0.2");
    iph->ip_dst.s_addr = inet_addr("127.0.0.1");
    char temp[10];
    snprintf(temp,10,"%d",ch);
    strcpy(buf+sizeof(struct ip),temp);

    sendto(rsfd, buf, sizeof(buf), 0, (SA*)&to_addr, sizeof(SA_IN));
}



int main(int argc,char* args[])
{
	int sfd,nop,usfd,nusfd[3],uset[3];
	struct sockaddr_in ser_addr,cli_addr;
	struct sockaddr_un ser_uaddr,cli_uaddr;

	int portno,cli_len,cli_ulen,i,j,max; // max holds max fd value + 1
	
	fd_set readfds;

	nop = 3;

	for(i=0;i<nop;i++)
	{
		uset[i]=0;
		start = end = -1;
	}
	
	sfd = socket(AF_INET,SOCK_STREAM,0); // socket create... AF_INET for IPv4 domain and SOCK_STREAM for connection oriented systems
	
	if(sfd < 0)
		derror("Socket create");

	memset(&ser_addr,0,sizeof(struct sockaddr_in)); // Initialize to 0
	memset(&cli_addr,0,sizeof(struct sockaddr_in));

	ser_addr.sin_family = AF_INET;
	portno = atoi(args[1]);
	ser_addr.sin_port = htons(portno); // converts int to 16 bit integer in network byte order
	ser_addr.sin_addr.s_addr = INADDR_ANY; // to get IP address of machine on which server is running

	if(bind(sfd,(struct sockaddr*)&ser_addr,sizeof(struct sockaddr_in))<0)
		derror("Bind error");
	
	if(listen(sfd,10)<0) // No. of clients that server can service
		derror("Listen error");

	cli_len = sizeof(struct sockaddr_in);

	usfd = socket(AF_UNIX,SOCK_STREAM,0); // socket create... for unix sockets
	
	if(usfd < 0)
		derror("Socket create");

	memset(&ser_uaddr,0,sizeof(struct sockaddr_un)); // Initialize to 0
	memset(&cli_uaddr,0,sizeof(struct sockaddr_un));

	ser_uaddr.sun_family = AF_UNIX;
    strcpy(ser_uaddr.sun_path, SOCK_PATH);
    unlink(ser_uaddr.sun_path);

	if(bind(usfd,(struct sockaddr*)&ser_uaddr,sizeof(ser_uaddr))<0)
		derror("Bind error");
	
	if(listen(usfd,10)<0) // No. of clients that server can service
		derror("Listen error");

	cli_ulen = sizeof(struct sockaddr_un);

	struct timespec tim_dur;
	tim_dur.tv_sec = 5;   // waiting time of 1 sec for verifying set bits of FDSET
	tim_dur.tv_nsec = 0;

	for(i=0;i<nop;i++)
	{
		nusfd[i] =  accept(usfd,(struct sockaddr *)&cli_uaddr, &cli_ulen);
		if(nusfd[i]<0)
			derror("Socket accept error\n");
		printf("%d\n", nusfd[i]);
	}


	//------raw socket

	rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	
	int set=1;
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0)
		derror("set socket opt");

	char buf[4096];
	memset(buf, 0, sizeof(buf));

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.2", &src_addr.sin_addr);

	if(bind(rsfd,(SA*)&src_addr,sizeof(SA_IN))<0)
		derror("Bind error");

	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(sfd,&readfds);
		for(i=0;i<nop;i++)
			FD_SET(nusfd[i],&readfds);

		// find max fd

		max=0;
		if(sfd>max)
			max=sfd;
		for(i=0;i<nop;i++)
			if(max<nusfd[i])
				max=nusfd[i];

		// pselect for finding if data is available
		int nsfd;
		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0); // pselect is used as timeleft is not updated after each select call
		{
			if(FD_ISSET(sfd,&readfds))
			{
				printf("Train requesting platform :P\n");

				nsfd = accept(sfd, (struct sockaddr *)&cli_addr, &cli_len);

				if(nsfd<0)
					derror("Accept error");
				
				int ch; // for accepting service no
				//while(recv(sfd,(&ch),sizeof(int),0)<=0);
				recv(nsfd,(&ch),sizeof(int),0);

				printf("%d\n",ch);
				for(i=0;i<nop;i++)
					if(uset[i]==0)
					{
						break;
					}
				if(i==nop) // client there so add to queue
					enqueue(nsfd);
				else
				{
					announce(ch);
					send_file_descriptor(nusfd[i],nsfd);
				}
			}
			for(i=0;i<nop;i++)
			{
				
				if(FD_ISSET(nusfd[i],&readfds)) // receive a message once client is serviced
				{
					char buf[256];
					memset(buf,0,256);
					recv(nusfd[i],buf,256,0);
					int temp = dequeue();
					if(temp!=-1)
					{
						announce(temp);
						send_file_descriptor(nusfd[i],temp);
					}
					else
						uset[i]=0;
				}
			}
		}

	}
	return 0;
}