#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //vagy: Project->Properties->Linker->Input->Additional Dependencies->ws2_32.lib

int main(int argc, char* argv[]){
	/* Jol parametereztek? (pl.: 152.66.208.100 80 / index.php) */
	if(argc<5){
		printf("Hasznalat: %s [IP] [port] [oldal] [celfajl]\n\n",argv[0]);
		exit(1);
	}
	/* WinSock API inicializalasa */
	WSADATA wsd;
	if(WSAStartup(0x0202,&wsd)!=0){
		printf("WSAStartup hiba: %d\n\n",WSAGetLastError());
		exit(1);
	}
	/* IPv4 socket letrehozasa */
	SOCKET sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock<0){
		printf("Socket hiba: %d\n\n",WSAGetLastError());
		exit(1);
	}
	/* protokoll, cim, port kitoltese */
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(atoi(argv[2]));
	/* megprobalunk kapcsolodni a szerverhez */
	if(connect(sock,(struct sockaddr*)&addr,sizeof(addr))<0){
		printf("Kapcsolodasi hiba: %d\n\n",WSAGetLastError());
		exit(1);
	}
	/* ha eljutott ide a vezerles, akkor megvan a kapcsolat, most kikuldunk egy HTTP kerest */
	char req[256];
	int len=sprintf(req,"GET %s HTTP/1.0\r\n\r\n",argv[3]);
	send(sock,req,len,0);
	/* kiirjuk a szerver valaszat egy bufferbe (legalabb a fejlecnek bele kell fernie!!) */
	char recbuf[8192];
	len=recv(sock,recbuf,sizeof(recbuf),MSG_WAITALL);
	if(len<0){
		printf("Fogadasi hiba: %d\n\n",WSAGetLastError());
		exit(1);
	}
	/* dolgozzuk is fel a valaszt (irjuk ki a megadott fajlba, de persze fejlec nelkul) */
	int status;
	char error[256];
	sscanf(recbuf,"HTTP/1.%*d %d %256[^\r\n\r\n]",&status,error);
	if(status!=200){
		printf("Szerver hibauzenete: %s\n\n",error);
		exit(1);
	}
	char *body=strstr(recbuf,"\r\n\r\n");
	body+=4; //ez a pointer az uzenet torzsere mutat
	FILE* f;
	if(!(f=fopen(argv[4],"wb"))){
		printf("Fajl letrehozasi hiba.\n\n");
		exit(1);
	}
	fwrite(body,1,len-(body-recbuf),f);
	/* addig irjuk ki a beerkezo adatokat, amig a szerver le nem zarja a kapcsolatot */
	while((len=recv(sock,recbuf,sizeof(recbuf),0))>0) fwrite(recbuf,1,len,f);
	printf("Az adatok letoltese sikerult!\n\n");
	fclose(f);
	closesocket(sock);
	WSACleanup();
	return 0;
}
