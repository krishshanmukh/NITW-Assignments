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
	/*for(i=0;i<15;i++)
		printf("%d - %d - %d\n",i,ticket[i],pno);*/

	//create a socket for sending and receiving
	int rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	
	/*int set=1;  
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0) // urself include IP Header
		derror("set socket opt");*/

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
		printf("Receiving\n");
		recvfrom(rsfd, buf, sizeof(buf), 0, 0, 0);
		printf("Received %d\n",*no);
		if(find(ticket,flag,size,*no))
			no_found++;
		if(no_found==size)
		{
			*no = pno;
			iph->ip_v=4;
	    	iph->ip_hl=5;
    		iph->ip_tos=0;
	    	iph->ip_len = sizeof(struct iphdr);
    		iph->ip_id = htonl (54321);;
    		iph->ip_off=0;
    		iph->ip_ttl=255;
    		iph->ip_p=26;
    		iph->ip_sum=0;
    		iph->ip_src.s_addr = inet_addr("127.0.0.1");
    		iph->ip_dst.s_addr = inet_addr("127.0.0.2");
			sendto(rsfd,buf,sizeof(buf),0,(SA*)&to_addr,sizeof(SA_IN));
		}
	}

	return ;

}


int main(){

	int tickets[][16]={{4,8,9,16,18,27,32,43,44,59,61,64,77,78,85,86},
					{5,5,9,13,14,25,35,45,48,54,58,60,70,75,85,89},
					{6,2,8,14,19,20,34,43,45,52,55,65,68,70,80,90}};
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