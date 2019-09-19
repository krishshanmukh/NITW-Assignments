// having sys ip


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>

#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/udp.h>

#define derror(msg) {printf("%s\n", msg); exit(0);}
#define SA_IN struct sockaddr_in
#define SA struct sockaddr

int main(int argc, char* argv[]){

	int rsfd = socket(AF_INET, SOCK_RAW, 250);
	if(rsfd < 0)	derror("socket");
	SA_IN src_addr;
	memset(&src_addr, 0, sizeof(SA_IN));
	src_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.2", &src_addr.sin_addr);

	int len = sizeof(SA_IN);
	for(;;){
		char buf[4096], t[512];
		memset(buf, 0, sizeof(buf));

		recvfrom(rsfd, buf, sizeof(buf), 0, (SA*)&src_addr, &len) ;
		printf("\t\tpacket Received\n\n");
		struct ip* iph = (struct ip*)buf;

		printf("\t\tHEADER\n");
		printf("%4d", iph -> ip_v);
		printf("%4d", iph -> ip_hl);
		printf("%8d", iph -> ip_tos);
		printf("%16d\n", iph -> ip_len);
		printf("%16d", iph -> ip_id);
		printf("%16d\n", iph -> ip_off);
		printf("%8d", iph -> ip_ttl);
		printf("%8d", iph -> ip_p);
		printf("%16d\n", iph -> ip_sum);
		inet_ntop(AF_INET, &(iph->ip_src), t, sizeof(t));
		printf("%22s\n", t);
		
		inet_ntop(AF_INET, &(iph->ip_dst), t, sizeof(t));
		printf("%22s\n", t);
		
		printf("\n\t\tMESSAGE\n");
		printf("%s\n", buf+sizeof(struct ip));
	}
	return 0;	
}