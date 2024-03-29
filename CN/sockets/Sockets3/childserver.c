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

int sfd,csfd[10],noc; // csfd holds fd of each client and noc hold no of clients 

struct message // structure of message to be sent
{
	char buf[100];
	int cno;
	int length;
};

int main(int argc,char* args[])
{
	
	struct sockaddr_in ser_addr,cli_addr;
	int portno,cli_len,i,j,max; // max holds max fd value + 1
	struct message msg;
	fd_set readfds;
	noc = 0;
	
	dup2(0,sfd);
	//dup2(1,sfd);

	memset(&ser_addr,0,sizeof(struct sockaddr_in)); // Initialize to 0
	memset(&cli_addr,0,sizeof(struct sockaddr_in));

	printf("Above accept\n");
	csfd[noc++] = accept(sfd,(struct sockaddr*)&cli_addr,&cli_len); // Type cast sockaddr_in to sockaddr and pass by reference and pointer of length to be passed
	printf("Below accept\n");
	cli_len = sizeof(struct sockaddr_in);

	struct timespec tim_dur;
	tim_dur.tv_sec = 5;   // waiting time of 1 sec for verifying set bits of FDSET
	tim_dur.tv_nsec = 0;

	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(sfd,&readfds);
		for(i=0;i<noc;i++)
			FD_SET(csfd[i],&readfds);

		// find max fd

		max=0;
		if(sfd>max)
			max=sfd;
		for(i=0;i<noc;i++)
			if(max<csfd[i])
				max=csfd[i];

		// pselect for finding if data is available
		printf("HEllo\n");
		if(pselect(max+1,&readfds,NULL,NULL,&tim_dur,NULL)>0) // pselect is used as timeleft is not updated after each select call
		{
			if(FD_ISSET(sfd,&readfds))
			{
					//printf("Client came have fun mr.server :P\n");
					csfd[noc++] = accept(sfd,(struct sockaddr*)&cli_addr,&cli_len); // Type cast sockaddr_in to sockaddr and pass by reference and pointer of length to be passed
					//if(csfd < 0)
					//derror("Accept error");
			}
			for(i=0;i<noc;i++)
			{
				if(FD_ISSET(csfd[i],&readfds))
				{
					recv(csfd[i],&msg,sizeof(struct message),0);
					for(j=0;j<noc;j++)
						if(i!=j)
							send(csfd[j],&msg,sizeof(struct message),0);
				}
			}
		}
	}

	return 0;
}
