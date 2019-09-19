#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <signal.h>

struct message
{
   char buf[10];
   int cno;
   int length;
};

int noc,rd,wt[10];
int *p;
int shmp,shms,shmc;
char *svr,*clt;

static void function(int x)
{
   if(x==SIGUSR1)
   {
      printf("%s\n",clt );
      wt[noc] = open(clt,O_WRONLY);
      memset(clt,10,'\0');
      noc++;
      signal(SIGUSR1,function);
   }
}

int main()
{
   int i;
   signal(SIGUSR1,function);

   mkfifo("./server",0644);
   rd = open("./server",O_RDONLY | O_NONBLOCK);
   noc=0;
   shmp = shmget(ftok(".",2), sizeof(int), IPC_CREAT | 0666);
   shms = shmget(ftok(".",4), sizeof(char)*10, IPC_CREAT | 0666);
   shmc = shmget(ftok(".",6), sizeof(char)*10, IPC_CREAT | 0666);

   svr = shmat(shms,NULL,0);
   clt = shmat(shmc,NULL,SHM_RDONLY);
   p = shmat(shmp,NULL,0);

   *p = getpid();

   char buf[10];
   memset(buf,10,'\0');
   strcpy(buf,"./server");
   strcpy(svr,buf);

   struct message msg;
   while(1)
   {
      while(read(rd,&msg,sizeof(struct message))<=0);
      printf("From %d Message %s",msg.cno,msg.buf);
      for(i=0;i<noc;i++)
      {
         write(wt[i],&msg,sizeof(struct message));
      }
   }
   close(rd);
}