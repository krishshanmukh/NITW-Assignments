//bind ip 1.0.0.1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <sys/un.h>
#include <sys/uio.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define derror(msg) {printf("%s\n",msg); exit(0);}
#define SA_IN struct sockaddr_in
#define SA struct sockaddr

int main(){
	int rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	
	int set=1;
	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, &set, sizeof (set)) < 0)
		derror("set socket opt");

	char buf[4096];
	memset(buf, 0, sizeof(buf));
	
	SA_IN to_addr;
	memset(&to_addr, 0, sizeof(SA_IN));
	to_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &to_addr.sin_addr);
	//to_addr.sin_addr.s_addr = INADDR_ANY;

	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.3", &src_addr.sin_addr);

	if(bind(rsfd,(SA*)&src_addr,sizeof(SA_IN))<0)
		derror("Bind error");

	struct ip* iph = (struct ip*)buf;
	
	// spoofing
	iph->ip_v=4;
    iph->ip_hl=5;
    iph->ip_tos=0;
    iph->ip_len = sizeof(struct iphdr);
    iph->ip_id = htonl (54321);;
    iph->ip_off=0;
    iph->ip_ttl=255;
    iph->ip_p=250;
    iph->ip_sum=0;
    iph->ip_src.s_addr = inet_addr("127.0.0.3");
    iph->ip_dst.s_addr = inet_addr("127.0.0.1");
    //derror(INADDR_ANY);
	
	for(;;){
		printf("Enter message:\n");

		read(0, buf+sizeof(struct ip), sizeof(buf));	// sizeof(buf)
		
		sendto(rsfd, buf, sizeof(buf), 0, (SA*)&to_addr, sizeof(SA_IN));
		//send(rsfd, buf, sizeof(buf), 0);
		
		printf("Ad Sent\n");
	}

	return 0;
}
