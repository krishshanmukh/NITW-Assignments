#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/select.h>

struct message
{
   char buf[10];
   int cno;
   int length;
};


int main()
{
    int r,w,n,i=0,fd[3],max=0;
    struct timeval time;
    time.tv_sec=1;
    time.tv_usec=0;
    
   fd_set rfds;
  struct message msg;

   fd[0]=open("./wclient1",O_RDONLY);
   fd[1]=open("./wclient2",O_RDONLY);
   fd[2]=open("./wclient3",O_RDONLY);
  
   /*for( i=0;i<3;i++)
    if(fd[i]>=max)
    max=fd[i];*/
 
  while(1)
  {
   time.tv_sec=1;
      FD_ZERO(&rfds);
      for(i=0;i<3;i++)
        FD_SET(fd[i],&rfds);
     printf("%d\n",select(4,&rfds,NULL,NULL,&time));

     if(FD_ISSET(fd[0],&rfds))
     {
        n=read(fd[0],&msg,sizeof(struct message));

        w=open("./rclient2",O_WRONLY);
        write(w,&msg,sizeof(struct message));
        close(w);

        w=open("./rclient3",O_WRONLY);
        write(w,&msg,sizeof(struct message));
        close(w);
     }

    if(FD_ISSET(fd[1],&rfds))
    {
      n=read(fd[1],&msg,sizeof(struct message));

      w=open("./rclient1",O_WRONLY);
      write(w,&msg,sizeof(struct message));
      close(w);

      w=open("./rclient3",O_WRONLY);
      write(w,&msg,sizeof(struct message));
      close(w);
    }

    if(FD_ISSET(fd[2],&rfds))
    {
      n=read(fd[2],&msg,sizeof(struct message));

      w=open("./rclient2",O_WRONLY);
      write(w,&msg,sizeof(struct message));
      close(w);

      w=open("./rclient1",O_WRONLY);
      write(w,&msg,sizeof(struct message));
      close(w);
    }

   // for(i=0;i<3;i++)
   //close(fd[i]);
     
  }
  return 0;   
}