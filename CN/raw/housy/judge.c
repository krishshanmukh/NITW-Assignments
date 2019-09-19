//bind ip 127.0.0.2

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



int main()
{
	fd_set readfds;
	int rsfd;
	int i,j,flag[91];

	make_zero(flag,91);

	rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	
	int set=1;  
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0) // urself include IP Header
		derror("set socket opt");

	char buf[512];
	memset(buf, 0, sizeof(buf));
	
	SA_IN to_addr;
	memset(&to_addr, 0, sizeof(SA_IN));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &to_addr.sin_addr);
	//to_addr.sin_addr.s_addr = ;

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.2", &src_addr.sin_addr);

	if(bind(rsfd,(SA*)&src_addr,sizeof(SA_IN))<0)
		derror("Bind error");

	struct ip* iph = (struct ip*)buf;

	int *no, no_found=0;
	no =  ((int*)(buf+sizeof(struct ip)));
	*no=0;

	struct timespec tim_dur;
	tim_dur.tv_sec = 2;   // waiting time of 1 sec for verifying set bits of FDSET
	tim_dur.tv_nsec = 0;

	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(rsfd,&readfds);
		if(pselect(rsfd+1,&readfds,NULL,NULL,&tim_dur,NULL)>0)
		{
			recvfrom(rsfd, buf, sizeof(buf), 0, 0, 0);
			printf("%d player won\n",*no);
			*no = -1;
			iph->ip_v=4;
	    	iph->ip_hl=5;
    		iph->ip_tos=0;
	    	iph->ip_len = sizeof(struct iphdr);
    		iph->ip_id = htonl (54321);;
    		iph->ip_off=0;
    		iph->ip_ttl=255;
    		iph->ip_p=250;
    		iph->ip_sum=0;
    		iph->ip_src.s_addr = inet_addr("127.0.0.2");
    		iph->ip_dst.s_addr = inet_addr("127.0.0.1");
			if(sendto(rsfd,buf,sizeof(buf),0,(SA*)&to_addr,sizeof(SA_IN))<0)
				derror("send error\n");
			break;
		}
		else
		{
			int temp;
			temp = (rand()+1)%91;
			while(flag[temp]!=0)
				temp = (rand()+1)%91;
			flag[temp]=1;

			*no = temp;
			iph->ip_v=4;
	    	iph->ip_hl=5;
    		iph->ip_tos=0;
	    	iph->ip_len = sizeof(struct iphdr);
    		iph->ip_id = htonl (54321);;
    		iph->ip_off=0;
    		iph->ip_ttl=255;
    		iph->ip_p=250;
    		iph->ip_sum=0;
    		iph->ip_src.s_addr = inet_addr("127.0.0.2");
    		iph->ip_dst.s_addr = inet_addr("127.0.0.1");
    		printf("Sending %d\n",*no);
			if(sendto(rsfd,buf,sizeof(buf),0,(SA*)&to_addr,sizeof(SA_IN))<0)
				derror("send error\n");
			printf("Sent\n");
		}
	}
	
	return 0;
}