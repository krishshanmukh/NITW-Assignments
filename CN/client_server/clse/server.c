#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct message
{
   char buf[10];
   int cno;
   int length;
};

int main()
{
   int w[3],r,i;
   mkfifo("./server",0644);
   r = open("./server",O_RDONLY | O_NONBLOCK);
   w[0] = open("./rclient1",O_WRONLY);
   w[1] = open("./rclient2",O_WRONLY);
   w[2] = open("./rclient3",O_WRONLY);
   struct message msg;
   while(1)
   {
      while(read(r,&msg,sizeof(struct message))<=0);
      printf("From %d Message %s",msg.cno,msg.buf);
      for(i=0;i<3;i++)
      {
         write(w[i],&msg,sizeof(struct message));
      }
   }
   close(r);
   close(w[0]);
   close(w[1]);
   close(w[2]);
}
