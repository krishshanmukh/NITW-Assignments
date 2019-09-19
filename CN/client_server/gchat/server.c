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
   int gno;
};

struct group
{
   int gno;
   int index;
   int count;
}gp[10];

int nog,noc,rd,wt[10][10];
int *p,*g;
int shmp,shms,shmc,shmg;
char *svr,*clt;

static void function(int x)
{
   if(x==SIGUSR1)
   {
      printf("%s\n",clt );
      
      int i;
      for(i=0;i<nog;i++)
         if(gp[i].gno==*g)
            break;

      if(i==nog) // if group is not avalialble
      {
         gp[nog].gno = *g;
         printf("%d\n", gp[nog].gno);
         gp[nog].count = 1;
         gp[nog].index = nog;
         nog++;
      }   
      else // group is available, increase its count
         gp[i].count++;

      wt[i][gp[i].count-1] = open(clt,O_WRONLY);
      memset(clt,10,'\0');
      signal(SIGUSR1,function);
   }
}

int main()
{
   int i,j;
   signal(SIGUSR1,function);

   mkfifo("./server",0644);
   rd = open("./server",O_RDONLY | O_NONBLOCK);
   nog=0;

   shmp = shmget(ftok(".",2), sizeof(int), IPC_CREAT | 0666);
   shms = shmget(ftok(".",4), sizeof(char)*10, IPC_CREAT | 0666);
   shmc = shmget(ftok(".",6), sizeof(char)*10, IPC_CREAT | 0666);
   shmg = shmget(ftok(".",8), sizeof(int), IPC_CREAT | 0666);

   svr = shmat(shms,NULL,0);
   clt = shmat(shmc,NULL,SHM_RDONLY);
   p = shmat(shmp,NULL,0);
   g = shmat(shmg,NULL,0);

   *p = getpid();

   char buf[10];
   memset(buf,10,'\0');
   strcpy(buf,"./server");
   strcpy(svr,buf);

   struct message msg;
   while(1)
   {
      while(read(rd,&msg,sizeof(struct message))<=0);
      printf("From %d Message %s Group %d\n",msg.cno,msg.buf,msg.gno);
      for(i=0;i<nog;i++)
         if(gp[i].gno==msg.gno)
            break;
      for(j=0;j<gp[i].count;j++)
      {
         write(wt[gp[i].index][j],&msg,sizeof(struct message));
      }
   }
   close(rd);
   return 0;
}