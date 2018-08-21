#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#define ID       1234
#define SEQ      55
#define BUFSIZE  2048

uint16_t checksum(uint16_t *addr, int len){
	int32_t nleft=len, sum=0;
	uint16_t *w=addr;
	while(nleft>1){
		sum+=*w++;
		nleft-=2;
	}
	if(nleft==1) sum+=*(uint8_t*)w;
	sum=(sum>>16)+(sum&0xffff);
	sum+=(sum>>16);
	return (uint16_t)(~sum);
}

int main(int argc, char** argv){
	struct hostent *host;
	struct sockaddr_in addr;
	struct icmphdr *icmp_hdr;
	struct iphdr *ip_hdr;
	struct timeval timeout;
	int sock, retval;
	uint8_t packet[BUFSIZE];
	char payload[]="ICMP ping test. :)";
	fd_set readfds;
	/* argumentumok ellenorzese */
	if(argc!=2){
		printf("Usage: %s [hostname]\n\n",argv[0]);
		return 1;
	}
	/* socket letrehozasa */
	sock=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP); //raw sockethez root jog kell!
	if(sock<0){
		printf("Cannot create socket,errno=%d\n",errno); //ha errno==13 --> sudo sysctl net.ipv4.ping_group_range="0 429496729"
		return 1;
	}
	setuid(getuid()); //innentol mar nem kell root jog
	/* cimzett megkeresese */
	host=gethostbyname(argv[1]);
	if(host==NULL){
		printf("Error: cannot find host.\n\n");
		return 1;
	}
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	memcpy(&addr.sin_addr.s_addr,host->h_addr,host->h_length);
	/* ICMP adatcsomag osszeallitasa */
	icmp_hdr=(struct icmphdr*)packet;
	memset(icmp_hdr,0,sizeof(struct icmphdr));
	icmp_hdr->type=ICMP_ECHO;
	icmp_hdr->un.echo.id=ID;
	icmp_hdr->un.echo.sequence=SEQ;
	memcpy(packet+sizeof(struct icmphdr),payload,sizeof(payload));
	icmp_hdr->checksum=checksum((uint16_t*)packet,sizeof(struct icmphdr)+sizeof(payload));
	/* adatcsomag elkuldese */
	retval=sendto(sock,packet,sizeof(struct icmphdr)+sizeof(payload),0,(struct sockaddr*)&addr,sizeof(addr));
	if(retval<0){
		printf("Cannot send ICMP echo request, errno=%d\n",errno);
		return 1;
	}
	printf("ICMP echo request sent.\n");
	/* varjuk a valaszt */
	while(1){
		timeout.tv_usec=0;
		timeout.tv_sec=10;
		FD_ZERO(&readfds);
		FD_SET(sock,&readfds);
		retval=select(sock+1,&readfds,NULL,NULL,&timeout);	
		if(retval==-1){
			printf("select() failed.");
			return 1;
		}
		else if(retval==0){
			printf("No ICMP activity in the last 10 seconds.\n");
			break;
		}
		else{
			recv(sock,packet,BUFSIZE,0);
			ip_hdr=(struct iphdr*)packet;
			icmp_hdr=(struct icmphdr*)&packet[sizeof(struct iphdr)];
			if(ip_hdr->protocol==IPPROTO_ICMP && icmp_hdr->type==ICMP_ECHOREPLY && icmp_hdr->un.echo.id==ID && icmp_hdr->un.echo.sequence==SEQ){
				printf("ICMP echo reply received.\n");
				break;
			}
			continue;
		}
	}
	return 0;
}
