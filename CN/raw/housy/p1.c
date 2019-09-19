//bind ip 127.0.0.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <sys/un.h>
#include <sys/uio.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h> // for inet_pton

#define derror(msg) {printf("%s\n",msg); exit(0);}
#define SA_IN struct sockaddr_in
#define SA struct sockaddr

void make_zero(int arr[],int size)
{
	int i;
	for(i=0;i<size;i++)
		arr[i]=0;
}

int find(int ticket[],int flag[],int size,int no)
{
	int temp = 0,i;
	for(i=0;i<size;i++)
	{
		if(ticket[i]==no)
		{
			flag[i]=1;
			temp=1;
			break;
		}
	}
	return temp;
}

void* player_thread(void *arg) //will hold player ticket details and player no:
{
	int *ticket;
	int flag[15],i,size=15;
	make_zero(flag,size);

	ticket = ((int*)(arg))+1;
	int pno = *((int*)(arg));

	//create a socket for sending and receiving
	int rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	
	int set=1;  
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0) // urself include IP Header
		derror("set socket opt");

	char buf[512];
	memset(buf, 0, sizeof(buf));
	
	SA_IN to_addr;
	memset(&to_addr, 0, sizeof(SA_IN));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.2", &to_addr.sin_addr);
	//to_addr.sin_addr.s_addr = ;

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &src_addr.sin_addr);

	if(bind(rsfd,(SA*)&src_addr,sizeof(SA_IN))<0)
		derror("Bind error");

	struct ip* iph = (struct ip*)buf;

	int *no, no_found=0;
	no =  ((int*)(buf+sizeof(struct ip)));
	*no=0;

	while(*no!=-1)
	{
		recvfrom(rsfd, buf, sizeof(buf), 0, 0, 0);
		if(find(ticket,flag,size,*no))
			no_found++;
		printf("%d - %d\n",pno,no_found);
		if(no_found==size)
		{
			*no = pno;
			sendto(rsfd,buf,sizeof(buf),0,(SA*)&to_addr,sizeof(SA_IN));
		}
	}

	return ;

}


int main(){

	int tickets[][16]={{1,3,5,12,14,25,32,42,44,58,62,64,72,76,84,86},
					{2,4,6,13,14,25,33,45,47,54,57,64,72,74,85,86},
					{3,3,7,14,18,22,37,42,49,59,62,65,69,71,80,90}};
	pthread_t player[3];
	int i;
	for(i=0;i<3;i++)
	{
		pthread_create(&player[i],NULL,player_thread,tickets[i]);
	}
	for(i=0;i<3;i++)
	{
		pthread_join(player[i],NULL);
	}

	return 0;
}