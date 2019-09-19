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

 	//printf("Waiting to receive fd %d\n",socket);
    
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
       		int sd  =  *((int*) CMSG_DATA(control_message));
       		sfd = sd;
       		//printf("Recieved\n");
      	}
    }
}


void* advertisements(void* arg)
{
	//create a socket for sending and receiving
	int rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	
	int set=1;  
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0) // urself include IP Header
		derror("set socket opt");

	char buf[512];
	memset(buf, 0, sizeof(buf));
	
	SA_IN to_addr;
	memset(&to_addr, 0, sizeof(SA_IN));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.2", &to_addr.sin_addr);
	//to_addr.sin_addr.s_addr = ;

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &src_addr.sin_addr);

	if(bind(rsfd,(SA*)&src_addr,sizeof(SA_IN))<0)
		derror("Bind error");

	struct ip* iph = (struct ip*)buf;
	
	while(1)
	{
		recvfrom(rsfd, buf, sizeof(buf), 0, 0, 0);
		printf("-------------Advertisement----------\n%s\n",(char*)(buf+sizeof(struct ip)));
	}
}

void* announcements(void* arg)
{
		//create a socket for sending and receiving
	int rsfd = socket(AF_INET, SOCK_RAW, 251);
	if(rsfd < 0)	derror("socket");
	
	int set=1;  
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0) // urself include IP Header
		derror("set socket opt");

	char buf[512];
	memset(buf, 0, sizeof(buf));
	
	SA_IN to_addr;
	memset(&to_addr, 0, sizeof(SA_IN));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.2", &to_addr.sin_addr);
	//to_addr.sin_addr.s_addr = ;

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &src_addr.sin_addr);

	if(bind(rsfd,(SA*)&src_addr,sizeof(SA_IN))<0)
		derror("Bind error");

	struct ip* iph = (struct ip*)buf;
	
	while(1)
	{
		recvfrom(rsfd, buf, sizeof(buf), 0, 0, 0);
		printf("-------------Announcement----------\n%s\n",(char*)(buf+sizeof(struct ip)));
	}
}


void recv_train()
{
	recv_file_descriptor(&usfd);
	printf("Train\n");
	memset(buf,0,256);
	while(recv(sfd,buf,256,0)<=0); // recv msg from client
	printf("%s\n",buf);
	while(recv(sfd,buf,256,0)<=0); // recv msg from client
	printf("%s\n",buf);
	strcpy(buf,"done");
	send(usfd,buf,256,0); // client serviced .. send a message to server
	close(sfd);
	//write(1,buf,strlen(buf));
}


int main(int argc,char* args[])
{
	pthread_t th1,th2;

	struct sockaddr_un ser_uaddr,cli_uaddr;
	int cli_ulen,i,j,max;

	usfd = socket(AF_UNIX,SOCK_STREAM,0); // socket create... 

	if(usfd < 0)
		derror("Socket create");

	memset(&ser_uaddr,0,sizeof(struct sockaddr_un)); // Initialize to 0
	memset(&cli_uaddr,0,sizeof(struct sockaddr_un));

	ser_uaddr.sun_family = AF_UNIX;
    strcpy(ser_uaddr.sun_path, SOCK_PATH);

	cli_ulen = sizeof(struct sockaddr_un);
	if(connect(usfd, (struct sockaddr *)&ser_uaddr, cli_ulen) == -1)
		derror("connect error\n");

	pthread_create(&th1,NULL,advertisements,NULL);
	pthread_create(&th2,NULL,announcements,NULL);


	while(1)
	{
		recv_train();
	}
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	

	return 0;
}
