#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>

struct message
{
   char buf[10];
   int cno;
   int length;
};

int main()
{  
   struct pollfd r[3];
   int w[3],i;
   mkfifo("./rclient1",0644);       // rclient is from where client reads and server writes to
   mkfifo("./rclient2",0644);
   mkfifo("./rclient3",0644);
   w[0] = open("./rclient1",O_WRONLY);
   w[1] = open("./rclient2",O_WRONLY);
   w[2] = open("./rclient3",O_WRONLY);
   r[0].fd = open("./wclient1",O_RDONLY | O_NONBLOCK);
   r[1].fd = open("./wclient2",O_RDONLY | O_NONBLOCK);
   r[2].fd = open("./wclient3",O_RDONLY | O_NONBLOCK);
   for(i=0;i<3;i++)
      r[i].events=POLLIN;
   struct message msg;
   while(1)
   {
      poll(r,3,100);
      for(i=0;i<3;i++)
      {
         if(r[i].revents&POLLIN)
         {
            read(r[i].fd,&msg,sizeof(struct message));
            printf("From %d Message %s",msg.cno,msg.buf);
            for(i=0;i<3;i++)
            {
               write(w[i],&msg,sizeof(struct message));
            }
         }
      }
   }
   close(r[0].fd);
   close(r[1].fd);
   close(r[2].fd);
   close(w[0]);
   close(w[1]);
   close(w[2]);
}