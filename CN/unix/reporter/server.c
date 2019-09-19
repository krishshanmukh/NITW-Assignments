#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <errno.h>
#define derror(msg) {printf("%s\n", msg); exit(0);}
#define SOCK_PATH "./temp_socket"

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
 	sendmsg(socket, &message, 0);
 	temp = errno;
 	printf("temp %d \n",temp);
 	return 1;
}

int queue[3][10],start[3],end[3];


void enqueue(int x,int index)
{
	if(start[index]==-1)
		start[index]++;
	end[index] = (end[index]+1)%10;
	queue[index][end[index]] = x;
}

int dequeue(int index)
{
	if(start[index]==-1)
		return -1;
	else
	{
		int x = queue[index][start[index]];
		if(start[index]==end[index])
			start[index]=end[index]=-1;
		else
			start[index] = (start[index]+1)%10;
		return x;
	}
}



int main(int argc,char* args[])
{
	int sfd,nos,usfd,nusfd[3],uset[3];
	struct sockaddr_in ser_addr,cli_addr;
	struct sockaddr_un ser_uaddr,cli_uaddr;

	int portno,cli_len,cli_ulen,i,j,max; // max holds max fd value + 1
	
	fd_set readfds;

	nos = 2;

	for(i=0;i<nos;i++)
	{
		uset[i]=0;
		start[i] = end[i] = -1;
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

	for(i=0;i<nos;i++)
	{
		nusfd[i] =  accept(usfd,(struct sockaddr *)&cli_uaddr, &cli_ulen);
		if(nusfd[i]<0)
			derror("Socket accept error\n");
		printf("%d\n", nusfd[i]);
	}

	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(sfd,&readfds);
		for(i=0;i<nos;i++)
			FD_SET(nusfd[i],&readfds);

		// find max fd

		max=0;
		if(sfd>max)
			max=sfd;
		for(i=0;i<nos;i++)
			if(max<nusfd[i])
				max=nusfd[i];

		// pselect for finding if data is available
		int nsfd;
		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0); // pselect is used as timeleft is not updated after each select call
		{
			if(FD_ISSET(sfd,&readfds))
			{
				printf("Client came have fun mr.server :P\n");

				nsfd = accept(sfd, (struct sockaddr *)&cli_addr, &cli_len);

				if(nsfd<0)
					derror("Accept error");
				
				int ch; // for accepting service no
				//while(recv(sfd,(&ch),sizeof(int),0)<=0);
				recv(nsfd,(&ch),sizeof(int),0);

				printf("%d %d\n",ch,uset[ch-1]);
				ch--;
				if(uset[ch]==0) // if no client is there for this service
				{
					uset[ch]=1;
					printf("Send descriptor %d\n",send_file_descriptor(nusfd[ch],nsfd));
					
				}
				else // client there so add to queue
					enqueue(nsfd,ch);
				printf("done sending\n");
			}
			for(i=0;i<nos;i++)
			{
				
				if(FD_ISSET(nusfd[i],&readfds)) // receive a message once client is serviced
				{
					char buf[256];
					memset(buf,0,256);
					recv(nusfd[i],buf,256,0);
					int temp = dequeue(i);
					if(temp!=-1)
						send_file_descriptor(nusfd[i],temp);
					else
						uset[i]=0;
				}
			}
		}

	}
	return 0;
}