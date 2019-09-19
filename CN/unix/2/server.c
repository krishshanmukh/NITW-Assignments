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

 	return sendmsg(socket, &message, 0);
}


int main(int argc,char* args[])
{
	int sfd[10],nos,usfd,nusfd[10],uset[10];
	struct sockaddr_in ser_addr,cli_addr;
	struct sockaddr_un ser_uaddr,cli_uaddr;

	int portno,cli_len,cli_ulen,i,j,max; // max holds max fd value + 1
	
	fd_set readfds;

	nos = 2;

	for(i=0;i<nos;i++)
		uset[i]=0;

	portno = atoi(args[1]);
	ser_addr.sin_family = AF_INET;

	for(i=0;i<nos;i++)
	{
		sfd[i] = socket(AF_INET,SOCK_STREAM,0); // socket create... AF_INET for IPv4 domain and SOCK_STREAM for connection oriented systems
	
		if(sfd[i] < 0)
			derror("Socket create");

		memset(&ser_addr,0,sizeof(struct sockaddr_in)); // Initialize to 0
		memset(&cli_addr,0,sizeof(struct sockaddr_in));

		ser_addr.sin_port = htons(portno+i); // converts int to 16 bit integer in network byte order

		if(bind(sfd[i],(struct sockaddr*)&ser_addr,sizeof(struct sockaddr_in))<0)
			derror("Bind error");
	
		if(listen(sfd[i],10)<0) // No. of clients that server can service
			derror("Listen error");

	}
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

	char path[2][20];
	strcpy(path[0],"./s1");
	strcpy(path[1],"./s2");

	printf("Hi\n");

	while(1)
	{

		FD_ZERO(&readfds);
		for(i=0;i<nos;i++)
			FD_SET(sfd[i],&readfds);

		max=0;

		for(i=0;i<nos;i++)
			if(max<sfd[i])
				max=sfd[i];

		int nsfd;

		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0); // pselect is used as timeleft is not updated after each select call
		{
			for(i=0;i<nos;i++)
			{
				printf("set");
				if(FD_ISSET(sfd[i],&readfds))
				{
					nsfd = accept(sfd[i], (struct sockaddr *)&cli_addr, &cli_len);
					printf("acc");
					if(nsfd<0)
					derror("Accept error");
					if(uset[i]==0)
					{
						printf("LOL");
						uset[i]=1;
						int c = fork();
						if(c>0)
						{
							nusfd[i] = accept(usfd,(struct sockaddr *)&cli_uaddr, &cli_ulen);
						}
						else
						{
							execlp(path[i],"hello",(char*)0);
							derror("Error\n");
						}
						send_file_descriptor(nusfd[i],nsfd);
					}
					else
					send_file_descriptor(nusfd[i],nsfd);
		
				}
			}
		}
	}

	return 0;
}