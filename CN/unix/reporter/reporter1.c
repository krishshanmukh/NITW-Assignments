#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define derror(msg) {printf("%s\n", msg); exit(0);}
#define SOCK_PATH "./temp_socket"

int usfd,sfd;
char buf[256];

void* recv_file_descriptor(void* param) /* Socket from which the file descriptor is read */
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
       		sfd = sd;
       		printf("Recieved\n");
      	}
    }
}


int main(int argc,char* args[])
{
	struct sockaddr_un ser_uaddr,cli_uaddr;
	int cli_ulen,i,j,max; // max holds max fd value + 1

	usfd = socket(AF_UNIX,SOCK_STREAM,0); // socket create... 

	if(usfd < 0)
		derror("Socket create");

	memset(&ser_uaddr,0,sizeof(struct sockaddr_un)); // Initialize to 0
	memset(&cli_uaddr,0,sizeof(struct sockaddr_un));

	ser_uaddr.sun_family = AF_UNIX;
    strcpy(ser_uaddr.sun_path, SOCK_PATH);

	cli_ulen = sizeof(struct sockaddr_un);
	if(connect(usfd, (struct sockaddr *)&ser_uaddr, cli_ulen) == -1)
		derror("connect erroe\n");

	
	while(1)
	{
		recv_file_descriptor(&usfd);
		printf("Received client in 1\n");
		memset(buf,0,256);
		while(recv(sfd,buf,256,0)<=0); // recv msg from client
		printf("%s\n",buf);
		for(i=0;i<strlen(buf);i++)
			buf[i]=toupper(buf[i]);
		send(sfd,buf,256,0); // send msg to client
		strcpy(buf,"done");
		send(usfd,buf,256,0); // client serviced .. send a message to server
		close(sfd);
		//write(1,buf,strlen(buf));
		
	}

	return 0;
}
