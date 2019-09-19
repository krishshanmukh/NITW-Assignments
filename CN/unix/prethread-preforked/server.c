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

int sfd,nos,usfd,nusfd[10],uset,nsfd,cusfd;
struct sockaddr_in ser_addr,cli_addr;
struct sockaddr_un ser_uaddr,cli_uaddr;

int portno,cli_len,cli_ulen,i,j,max; // max holds max fd value + 1


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
 	strcpy(data," ");
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


void* rcv_msg(void *arg)
{
	fd_set readfds;
	struct timespec tim_dur;
	tim_dur.tv_sec = 5;   // waiting time of 1 sec for verifying set bits of FDSET
	tim_dur.tv_nsec = 0;

	while(1)
	{
		FD_ZERO(&readfds);
		for(i=0;i<nos;i++)
			FD_SET(nusfd[i],&readfds);

		max=0;

		for(i=0;i<nos;i++)
			if(max<nusfd[i])
				max=nusfd[i];


		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0); // pselect is used as timeleft is not updated after each select call
		{
			for(i=0;i<nos;i++)
			{
				if(FD_ISSET(nusfd[i],&readfds))
				{
					char buf[256];
					memset(buf,0,256);
					recv(nusfd[i],buf,256,0);
					printf("Received!: %s\n",buf);
				}
			}
		}
	}
}

int recv_file_descriptor(void* param) /* Socket from which the file descriptor is read */
{

	int socket = *((int*)param);

 	int sent_fd;
 	struct msghdr message;
 	struct iovec iov[1];
 	struct cmsghdr *control_message = NULL;
 	char ctrl_buf[CMSG_SPACE(sizeof(int))];
 	char data[2];
 	int res;

 	printf("Waiting to receive fd %d\n",socket);
    
    memset(&message, 0, sizeof(struct msghdr));
    memset(ctrl_buf, 0, CMSG_SPACE(sizeof(int)));

   	/* For the dummy data */
    iov[0].iov_base = data;
    iov[0].iov_len = sizeof(data);

    message.msg_name = NULL;
    message.msg_namelen = 0;
    message.msg_control = ctrl_buf;
    message.msg_controllen = CMSG_SPACE(sizeof(int));
    message.msg_iov = iov;
    message.msg_iovlen = 1;

    if((res = recvmsg(socket, &message, 0)) < 0)
    printf("Does not receive\n");

     /* Iterate through header to find if there is a file descriptor */
    for(control_message = CMSG_FIRSTHDR(&message);
       	control_message != NULL;
       	control_message = CMSG_NXTHDR(&message,
                                      control_message))
    {
     	if( (control_message->cmsg_level == SOL_SOCKET) &&
       	  (control_message->cmsg_type == SCM_RIGHTS) )
     	{
       		int sd  =  *((int *) CMSG_DATA(control_message));
       		nsfd = sd;
       		printf("Recieved\n");
       		return 1;
      	}
    }
    return 0;
}


int main(int argc,char* args[])
{
	
	fd_set readfds;

	nos = 2;

	uset=0;

	portno = atoi(args[1]);
	ser_addr.sin_family = AF_INET;

	sfd = socket(AF_INET,SOCK_STREAM,0); // socket create... AF_INET for IPv4 domain and SOCK_STREAM for connection oriented systems
	
	if(sfd < 0)
		derror("Socket create");

	memset(&ser_addr,0,sizeof(struct sockaddr_in)); // Initialize to 0
	memset(&cli_addr,0,sizeof(struct sockaddr_in));

	ser_addr.sin_port = htons(portno); // converts int to 16 bit integer in network byte order

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

	printf("Hi\n");

	for(i=0;i<2;i++)
	{
		int c=fork();
		if(c>0)
		{
			nusfd[i] = accept(usfd, (struct sockaddr *)&cli_addr, &cli_len);
			continue;
		}
		else
		{
			for(j=0;j<i;j++)
				close(nusfd[i-1]);
			close(sfd);
			close(usfd);
			
			cusfd = socket(AF_UNIX,SOCK_STREAM,0); // socket create... 

			if(cusfd < 0)
				derror("Socket create");

			memset(&ser_uaddr,0,sizeof(struct sockaddr_un)); // Initialize to 0
			memset(&cli_uaddr,0,sizeof(struct sockaddr_un));

			ser_uaddr.sun_family = AF_UNIX;
    		strcpy(ser_uaddr.sun_path, SOCK_PATH);

			cli_ulen = sizeof(struct sockaddr_un);
			if(connect(cusfd, (struct sockaddr *)&ser_uaddr, cli_ulen) == -1)
			derror("connect erroe\n");

			goto child;
		}
	}

	while(1)
	{
		pthread_t receiver;
		pthread_create(&receiver,NULL,rcv_msg,NULL); // for rcving msg from server
		uset = 0;
		while(1) // sending file descriptor
		{
			int temp = accept(sfd, (struct sockaddr *)&cli_addr, &cli_len);
			send_file_descriptor(nusfd[uset++],temp);
		}

		pthread_join(receiver,NULL);
		return 0;
	}

	child:
	while(1)
	{
		while(recv_file_descriptor(&cusfd)==0);
		while(1)
		{
			char buf[256];
			memset(buf,0,256);
			recv(nsfd,buf,256,0);
			printf("In child%s",buf);
			send(cusfd,buf,256,0);
			send(nsfd,buf,256,0);
		}
	}

	return 0;
}