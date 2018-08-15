#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

typedef enum{ENTRY_STRING, ENTRY_NUMBER, ENTRY_OTHER} entryType_t;

typedef struct{
	entryType_t type;
	int level;
	int isKey;
	int posStart, posEnd;
} jsonEntry_t;

/* beolvassa a fajl tartalmat a bufferbe */
int readJSONFile(const char *filename, char **jsonStr){
	FILE *fp;
	int size;
	fp=fopen(filename,"rb");
	if(fp==NULL){
		printf("Error: cannot open JSON file.\n\n");
		exit(1);
	}
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	*jsonStr=(char*)malloc((size+1)*sizeof(char));
	fread(*jsonStr,sizeof(char),size,fp);
	(*jsonStr)[size]=0;
	fclose(fp);
	return size;
}

/* egyszeru JSON parser (hianyossagok: hibas szintaktika kezelese, escape karakterek, Unicode, tombok) */
int parseJSON(const char *jsonStr, jsonEntry_t *entries){
	int numEntries=0, pos, level=-1, parsingString=0, parsingOther=0;
	for(pos=0;jsonStr[pos];pos++){
		switch(jsonStr[pos]){
			case '\"':
				if(parsingString==0){ //string kezdete
					parsingString=1;
					entries[numEntries].type=ENTRY_STRING;
					entries[numEntries].isKey=0;
					entries[numEntries].level=level;
					entries[numEntries].posStart=pos+1;
				}
				else{ //string vege
					entries[numEntries].posEnd=pos-1;
					parsingString=0;
					numEntries++;
				}
				break;
			case '{': //objektum kezdete
				if(parsingString==0) level++;
				break;
			case '}': //objektum vege
				if(parsingString==0) level--;
				if(parsingOther==1){
					entries[numEntries].posEnd=pos-1;
					parsingOther=0;
					numEntries++;
				}
				break;
			case ':': //kettospont elotti string kulcs
				entries[numEntries-1].isKey=1;
				break;
			case ' ': case '\t': case '\n': case '\r': case ',': case '[': case ']': //szokoz stb...
				if(parsingOther==1){
					entries[numEntries].posEnd=pos-1;
					parsingOther=0;
					numEntries++;
				}
				break;
			default: //szam, true, false, null
				if(parsingString==0 && parsingOther==0){
					parsingOther=1;
					if(((jsonStr[pos]>='0')&&(jsonStr[pos]<='9')) || (jsonStr[pos]=='.') || (jsonStr[pos]=='-'))
						entries[numEntries].type=ENTRY_NUMBER;
					else
						entries[numEntries].type=ENTRY_OTHER;
					entries[numEntries].isKey=0;
					entries[numEntries].level=level;
					entries[numEntries].posStart=pos;
				}
				break;
		}
	}
	return numEntries;
}

/* formazottan kiirja a bejegyzeseket */
void printEntries(const jsonEntry_t *entries, const char *jsonStr, int numEntries){
	int i, j;
	for(i=0;i<numEntries;i++){
		if(entries[i].isKey){
			printf("\n");
			for(j=0;j<entries[i].level;j++) printf("    ");
		}
		for(j=entries[i].posStart;j<=entries[i].posEnd;j++) printf("%c",jsonStr[j]);
		if(entries[i].isKey) printf(": ");
	}
	printf("\n\n");
}

/* lekeri a JSON fajlt a szerverrol */
void getWeather(const char *appId, const char *cityId, const char *filename){
	char request[256], response[8192], *text;
	struct hostent *server;
	struct sockaddr_in serverAddr;
	int sock, bytes, byteCntr;
	FILE *fp;
	/* csatlakozas */
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		printf("Error: cannot create socket.\n\n");
		exit(1);
	}
	server=gethostbyname("api.openweathermap.org");
	if(server==NULL){
		printf("Error: cannot find host.\n\n");
		exit(1);
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(80);
	memcpy(&serverAddr.sin_addr.s_addr,server->h_addr,server->h_length);
	if(connect(sock,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
		printf("Error: cannot connect to server.\n\n");
		exit(1);	
	}
	/* keres kuldese */
	sprintf(request,"GET /data/2.5/weather?id=%s&appid=%s HTTP/1.0\r\nHost: api.openweathermap.org\r\nConnection: close\r\n\r\n",cityId,appId);
	byteCntr=0;
	do{
		bytes=write(sock,request+byteCntr,strlen(request)-byteCntr);
		if(bytes<0){
			printf("Error while sending to socket.\n\n");
			exit(1);
		}
		if(bytes==0) break;
		byteCntr+=bytes;
	} while(byteCntr<strlen(request));
	/* valasz fogadasa */
	memset(response,0,sizeof(response));
	byteCntr=0;
	do{
		bytes=read(sock,response+byteCntr,sizeof(response)-1-byteCntr);
		if(bytes<0){
			printf("Error while reading from socket.\n\n");
			exit(1);
		}
		if(bytes==0) break;
		byteCntr+=bytes;
	} while(byteCntr<sizeof(response)-1);
	close(sock);
	/* fajlba iras */
	fp=fopen(filename,"w");
	text=strstr(response,"\r\n\r\n")+4;
	fputs(text,fp);
	fclose(fp);
}

/* foprogram */
int main(int argc, char *argv[]){
	int numEntries;
	char *jsonStr;
	jsonEntry_t entries[256];
	if(argc!=2){
		printf("Usage: %s [appid]\n\n",argv[0]);
		exit(1);
	}
	getWeather(argv[1],"7284824","weather.json");
	readJSONFile("weather.json",&jsonStr);
	numEntries=parseJSON(jsonStr,entries);
	printEntries(entries,jsonStr,numEntries);
	free(jsonStr);
	return 0;
}
