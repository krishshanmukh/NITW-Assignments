#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define derror(msg) {printf("%s\n", msg); exit(0);}


int sfd,cno;
struct sockaddr_in ser_addr,cli_addr;
int portno,ser_len;

void* snd_msg(void* arg) // reads from keyboard and sends to server
{
	char buf[256];
	while(1)
	{
		memset(buf,0,256);
		read(0,buf,256);
		send(sfd,buf,256,0);
	}
}

void* rcv_msg(void* arg) // receives from server and displays on screen
{
	char buf[256];
	while(1)
	{
		memset(buf,0,256);
		while(recv(sfd,buf,256,0)<0);
		write(1,buf,256);
	}
}


int main(int argc,char* args[])
{
	char buf[256];
	int ch,portno;
	int cli_len;
	pthread_t sender,receiver;
	cli_len = sizeof(struct sockaddr_in);
	
	
	if(sfd < 0)
		derror("Socket create");

	memset(&ser_addr,0,sizeof(struct sockaddr_in)); // Initialize to 0

	ser_addr.sin_family = AF_INET;
	// ser_addr.sin_port = htons(portno); // converts int to 16 bit integer in network byte order
	ser_addr.sin_addr.s_addr = INADDR_ANY; // to get IP address of machine
	ser_len = sizeof(struct sockaddr_in);

	//read(0,ch,2); // ch[0] will hold '1' if client wants connection oriented server '2' if connection less
	
	//ch = atoi(args[1]); // get choice from command line argument
	
	sfd = socket(AF_INET,SOCK_STREAM,0); // socket create... AF_INET for IPv4 domain
	// and SOCK_STREAM for connection oriented systems
	portno = atoi(args[1]); // get port no
	ser_addr.sin_port = htons(portno);
	if(connect(sfd,(struct sockaddr*)&ser_addr,sizeof(struct sockaddr_in)) < 0)
		derror("Connect error"); // connect to server

	/*if(send(sfd,&ch,sizeof(ch),0)<0)
		derror("Send error!\n");*/

	/*while(1)
	{
		memset(buf,0,256);
		read(0,buf,256); // read input from keyboard
		send(sfd,buf,256,0);
		memset(buf,0,256);
		
		while(recv(sfd,buf,256,0)<=0); // receive capitalised version
		//write(1,buf,strlen(buf));
		printf("%s",buf);
	}*/
	pthread_create(&sender,NULL,snd_msg,NULL); // for sending msg to server
	pthread_create(&receiver,NULL,rcv_msg,NULL); // for rcving msg from server

	pthread_join(sender,NULL);

	return 0;
}