#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include <signal.h>

struct message
{
	char buf[10];
	int cno;
	int length;
};

int cno,r,w;
int *p;
int shmp,shms,shmc;
char *svr,*clt;

void* read_server(void *arg)
{
	struct message msg;
	msg.cno=cno;
	while(1)
	{
		while(read(r,&msg,sizeof(struct message))<=0);
		if(msg.cno!=cno)
		{
			printf("From %d ",msg.cno);
			write(1,msg.buf,msg.length);
		}
	}
}
void* write_server(void *arg)
{
	struct message msg;
	msg.cno=cno;
	while(1)
	{
		msg.length=read(0,msg.buf,10);
		write(w,&msg,sizeof(struct message));
	}
}
int main()
{
    cno=1;
    char buf[10];
    memset(buf,10,'\0');

   	shmp = shmget(ftok(".",2), sizeof(int), IPC_CREAT | 0666);
   	shms = shmget(ftok(".",4), sizeof(char)*10, IPC_CREAT | 0666);
   	shmc = shmget(ftok(".",6), sizeof(char)*10, IPC_CREAT | 0666);

   	svr = shmat(shms,NULL,SHM_RDONLY); // for storing server fifo name
   	clt = shmat(shmc,NULL,0); // for storing client fifo name
   	p = shmat(shmp,NULL,0); // for storing pid of server

   	memset(buf,10,'\0');
   	strcpy(buf,"./rclient1");
   	strcpy(clt,buf);
   	mkfifo(buf,0644);
   	r = open(buf, O_RDONLY|O_NONBLOCK);
   	w = open(svr, O_WRONLY);

   	kill(*p,SIGUSR1);
   	
	pthread_t rd,wt;
	pthread_create(&rd,NULL,read_server,NULL);
	pthread_create(&wt,NULL,write_server,NULL);
	pthread_join(rd,NULL);
	close(w);
	close(r);
  	return 0;
}