#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

struct message
{
	char buf[10];
	int cno;
	int length;
};

int cno,r,w;

void* read_server(void *arg)
{
	struct message msg;
	msg.cno=cno;
	while(1)
	{
		while(read(r,&msg,sizeof(struct message))<=0);
		if(msg.cno!=cno)
		{
			//printf("From %d ",msg.cno);
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
    mkfifo("./rclient1",0644);
    mkfifo("./wclient1",0644);
    r=open("./rclient1",O_RDONLY | O_NONBLOCK);
    while((w=open("./wclient1",O_WRONLY))<0);
	pthread_t rd,wt;
	pthread_create(&rd,NULL,read_server,NULL);
	pthread_create(&wt,NULL,write_server,NULL);
	pthread_join(rd,NULL);
	close(w);
	close(r);
  	return 0;
}