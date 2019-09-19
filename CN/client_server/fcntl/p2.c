#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
int fd;
static void p2(int p)
{
	if(p == SIGUSR2)
	{
		signal(SIGUSR2,p2);
		char buf[10];
		int n;
		if((n=read(fd,buf,10))>0)
		{
			printf("Writing from CHILD\n");
			write(1,buf,n);
			printf("\n");
			kill(getppid(),SIGUSR1);
		}
		else
			exit(0);
	}
}

int main(int argc, char **argv)
{

	signal(SIGUSR2,p2);
	kill(getppid(),SIGUSR1);
	while(1);

	return 0;
}
