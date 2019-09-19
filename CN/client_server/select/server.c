#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <poll.h>

struct message
{
   char buf[10];
   int cno;
   int length;
};

int main()
{  
   int w[3],i,r[3],j,max=0;
   mkfifo("./rclient1",0644);       // rclient is from where client reads and server writes to
   mkfifo("./rclient2",0644);
   mkfifo("./rclient3",0644);
   w[0] = open("./rclient1",O_WRONLY);
   w[1] = open("./rclient2",O_WRONLY);
   w[2] = open("./rclient3",O_WRONLY);
   r[0] = open("./wclient1",O_RDONLY);
   r[1] = open("./wclient2",O_RDONLY);
   r[2] = open("./wclient3",O_RDONLY);
   fd_set readfds;
   struct message msg;
   struct timeval tim;
   tim.tv_sec=1;
   tim.tv_usec=0;
   for(i=0;i<3;i++)
   {
      if(max<r[i])
         max=r[i];
   }
   while(1)
   {
      //printf("Hi");
      tim.tv_sec=1;
      FD_ZERO(&readfds);
      for(i=0;i<3;i++)
         FD_SET(r[i],&readfds);
      printf("%d",select(max+1,&readfds,NULL,NULL,&tim)); // NULL for infinite blocking
      //printf("Hi\n");
      for(i=0;i<3;i++)
      {
         if(FD_ISSET(r[i],&readfds))
         {
            read(r[i],&msg,sizeof(struct message));
            printf("From %d Message %s",msg.cno,msg.buf);
            for(j=0;j<3;j++)
            {
               write(w[j],&msg,sizeof(struct message));
            }
         }
      }
   }
   close(r[0]);
   close(r[1]);
   close(r[2]);
   close(w[0]);
   close(w[1]);
   close(w[2]);
}