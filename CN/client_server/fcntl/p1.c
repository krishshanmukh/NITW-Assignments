#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

int child_pid;
int fd;

static void p1(int p)
{
	if(p == SIGUSR1)
	{
		signal(SIGUSR1,p1);
		char buf[10];
		int n;
		if((n=read(fd,buf,10))>0)
		{
			printf("Writing from PARENT\n");
			write(1,buf,n);
			printf("\n");			
			kill(child_pid,SIGUSR2);
		}
		else
			exit(0);
	}
}

int main()
{
	
	fd = open("lol",O_RDONLY);
	close(0);
	fcntl(fd,F_DUPFD,0);
	// dup2(fd,0);
	
	child_pid = fork();
	
	if(child_pid > 0)
	{
		if(signal(SIGUSR1,p1)==SIG_ERR)
			printf("Signal Error in P1\n");
		wait();

	}
	else
	{
		execl("p2.out","hello",(char *)0);
	}
	return 0;
}
