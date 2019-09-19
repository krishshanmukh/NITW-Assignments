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

int usfd,csfd[10],noc; // csfd holds fd of each client and noc hold no of clients 

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
       		csfd[noc++] = sd;
       		printf("Recieved\n");
      	}
    }
}


int main(int argc,char* args[])
{
	struct sockaddr_un ser_uaddr,cli_uaddr;
	int cli_ulen,i,j,max; // max holds max fd value + 1
	printf("Came to s1\n");

	fd_set readfds;
	noc = 0;
	
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

	struct timespec tim_dur;
	tim_dur.tv_sec = 2;   // waiting time of 1 sec for verifying set bits of FDSET
	tim_dur.tv_nsec = 0;

	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(usfd,&readfds);
		for(i=0;i<noc;i++)
			FD_SET(csfd[i],&readfds);

		// find max fd

		max=0;
		if(usfd>max)
			max=usfd;
		for(i=0;i<noc;i++)
			if(max<csfd[i])
				max=csfd[i];

		// pselect for finding if data is available
		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0); // pselect is used as timeleft is not updated after each select call
		{
			if(FD_ISSET(usfd,&readfds))
			{
				printf("Client came have fun mr.server :P\n");
				recv_file_descriptor(&usfd);
				sleep(2);
			}
			for(i=0;i<noc;i++)
			{
				if(FD_ISSET(csfd[i],&readfds))
				{
					printf("set");
					char buf[256];
					memset(buf,0,256);
					recv(csfd[i],buf,256,0);
					printf("%s",buf);
					send(csfd[i],buf,256,0);
				}
			}
		}
	}

	return 0;
}
