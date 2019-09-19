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
#define derror(msg) {printf("%s\n", msg); exit(0);}


int main(int argc,char* args[])
{
	struct sockaddr_in ser_addr,cli_addr;
	int portno,cli_len,i,j,max; // max holds max fd value + 1

	fd_set readfds;

	int nog = 10;
	
	int sfd[nog];
	i=0;

	for(i=0;i<nog;i++)
	{
		sfd[i] = socket(AF_INET,SOCK_STREAM,0); // socket create... AF_INET for IPv4 domain and SOCK_STREAM for connection oriented systems
		if(sfd[i] < 0)
		derror("Socket create");
	}

	memset(&ser_addr,0,sizeof(struct sockaddr_in)); // Initialize to 0
	memset(&cli_addr,0,sizeof(struct sockaddr_in));

	ser_addr.sin_family = AF_INET;
	portno = atoi(args[1]);
	ser_addr.sin_port = htons(portno); // converts int to 16 bit integer in network byte order
	ser_addr.sin_addr.s_addr = INADDR_ANY; // to get IP address of machine on which server is running

	for(i=0;i<nog;i++)
	{
		if(bind(sfd[i],(struct sockaddr*)&ser_addr,sizeof(struct sockaddr_in))<0)
			derror("Bind error");
		portno++;
		ser_addr.sin_port = htons(portno);
	}
	
	for(i=0;i<nog;i++)
		if(listen(sfd[i],10)<0) // No. of clients that server can service
			derror("Listen error");

	cli_len = sizeof(struct sockaddr_in);

	int flag[nog];
	for(i=0;i<10;i++)
		flag[i] = 0;

	struct timespec tim_dur;
	tim_dur.tv_sec = 5;   // waiting time of 1 sec for verifying set bits of FDSET
	tim_dur.tv_nsec = 0;

	while(1)
	{
		FD_ZERO(&readfds);
		//FD_SET(sfd,&readfds);
		for(i=0;i<nog;i++)
			if(flag[i]==0)
				FD_SET(sfd[i],&readfds);

		// find max fd

		max=0;
		for(i=0;i<nog;i++)
			if(max<sfd[i])
				max=sfd[i];

		// pselect for finding if data is available
		//printf("HEllo\n");

		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0) // pselect is used as timeleft is not updated after each select call
		{
			/*if(FD_ISSET(sfd,&readfds))
			{
					printf("Client came have fun mr.server :P\n");
					csfd[nog++] = accept(sfd,(struct sockaddr*)&cli_addr,&cli_len); // Type cast sockaddr_in to sockaddr and pass by reference and pointer of length to be passed
					if(csfd < 0)
					derror("Accept error");
			}*/
			for(i=0;i<nog;i++)
			{
				if(FD_ISSET(sfd[i],&readfds))
				{
					printf("Client came have fun mr.server %d :P\n",i);
					int c = 0;
					c = fork();
					if(c>0)
					{
						flag[i]= 1;
					}
					else
					{
						int j=0;
						for(j;j<nog;j++)
							if(j!=i)
								close(sfd[j]);
						dup2(sfd[i],0);
						//dup2(sfd[i],1);
						execlp("./childserver.out","hello",(char *)0);
					}
				}
			}
		}
	}

	return 0;
}
