#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cube.h"

void draw(const cube_t *cube){
	unsigned r, c;
	/* felso */
	for(r=0; r<cube->size; r++){
		for(c=0;c<cube->size;c++) putchar(' ');
		for(c=0;c<cube->size;c++) putchar(cube->colors[r*cube->size+c]);
		putchar('\n');
	}
	/* bal, szemkozti, jobb */
	for(r=0; r<cube->size; r++){
		for(c=0;c<cube->size;c++) putchar(cube->colors[r*cube->size+c+2*cube->size*cube->size]);
		for(c=0;c<cube->size;c++) putchar(cube->colors[r*cube->size+c+1*cube->size*cube->size]);
		for(c=0;c<cube->size;c++) putchar(cube->colors[r*cube->size+c+3*cube->size*cube->size]);
		putchar('\n');
	}
	/* also */
	for(r=0; r<cube->size; r++){
		for(c=0;c<cube->size;c++) putchar(' ');
		for(c=0;c<cube->size;c++) putchar(cube->colors[r*cube->size+c+4*cube->size*cube->size]);
		putchar('\n');
	}
	/* hatso */
	for(r=0; r<cube->size; r++){
		for(c=0;c<cube->size;c++) putchar(' ');
		for(c=0;c<cube->size;c++) putchar(cube->colors[r*cube->size+c+5*cube->size*cube->size]);
		putchar('\n');
	}
}

void move(const char *seq, cube_t *cube){
	unsigned m, i, j, N=cube->size;
	char temp[9];
	if(N!=2 && N!=3) return;
	m=0;
	while(seq[m]){
		switch(seq[m]){
			case 'F':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N-N+i];
				for(i=0;i<N;i++) cube->colors[N*N-1-i]=cube->colors[2*N*N+N*i+N-1];                          //felso <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+N*i+N-1]=cube->colors[4*N*N+i];                          //bal <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N-i-1]=cube->colors[3*N*N+N*i];                          //also <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i]=temp[i];                                            //jobb <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[2*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=temp[i];                                              //elso CW
				break;
			case 'f':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N-N+i];
				for(i=0;i<N;i++) cube->colors[N*N-N+i]=cube->colors[3*N*N+N*i];                              //felso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i]=cube->colors[4*N*N+N-i-1];                          //jobb <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+i]=cube->colors[2*N*N+N*i+N-1];                          //also <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-i*N-1]=temp[i];                                          //bal <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=temp[i];                                              //elso CCW
				break;
			case 'B':
				for(i=0;i<N;i++) temp[i]=cube->colors[i];
				for(i=0;i<N;i++) cube->colors[i]=cube->colors[3*N*N+N*i+N-1];                                //felso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i+N-1]=cube->colors[5*N*N-i-1];                        //jobb <-- also
				for(i=0;i<N;i++) cube->colors[5*N*N-N+i]=cube->colors[2*N*N+N*i];                            //also <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+N*i]=temp[N-i-1];                                        //bal <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[6*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=temp[i];                                            //hatso CW
				break;
			case 'b':
				for(i=0;i<N;i++) temp[i]=cube->colors[i];
				for(i=0;i<N;i++) cube->colors[N-i-1]=cube->colors[2*N*N+N*i];                                //felso <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-N*i-N]=cube->colors[5*N*N-i-1];                          //bal <-- also
				for(i=0;i<N;i++) cube->colors[5*N*N-i-1]=cube->colors[3*N*N+N*i+N-1];                        //also <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i+N-1]=temp[i];                                        //jobb <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[5*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=temp[i];                                            //hatso CCW
				break;
			case 'U':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N;i++) cube->colors[N*N+i]=cube->colors[3*N*N+i];                                  //elso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+i]=cube->colors[6*N*N-i-1];                              //jobb <-- hatso
				for(i=0;i<N;i++) cube->colors[6*N*N-i-1]=cube->colors[2*N*N+i];                              //hatso <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+i]=temp[i];                                              //bal <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                                                  //felso CW
				break;
			case 'u':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N;i++) cube->colors[N*N+i]=cube->colors[2*N*N+i];                                  //elso <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+i]=cube->colors[6*N*N-i-1];                              //bal <-- hatso
				for(i=0;i<N;i++) cube->colors[6*N*N-i-1]=cube->colors[3*N*N+i];                              //hatso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+i]=temp[i];                                              //jobb <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                                                  //felso CCW
				break;
			case 'D':
				for(i=0;i<N;i++) temp[i]=cube->colors[2*N*N-N+i];
				for(i=0;i<N;i++) cube->colors[2*N*N-N+i]=cube->colors[3*N*N-N+i];                            //elso <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-i-1]=cube->colors[5*N*N+i];                              //bal <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+i]=cube->colors[4*N*N-i-1];                              //hatso <-- jobb
				for(i=0;i<N;i++) cube->colors[4*N*N-N+i]=temp[i];                                            //jobb <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[5*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                                            //also CW
				break;
			case 'd':
				for(i=0;i<N;i++) temp[i]=cube->colors[2*N*N-N+i];
				for(i=0;i<N;i++) cube->colors[2*N*N-N+i]=cube->colors[4*N*N-N+i];                            //elso <-- jobb
				for(i=0;i<N;i++) cube->colors[4*N*N-i-1]=cube->colors[5*N*N+i];                              //jobb <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+i]=cube->colors[3*N*N-i-1];                              //hatso <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-N+i]=temp[i];                                            //bal <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[4*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                                            //also CCW
				break;
			case 'R':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i+N-1];
				for(i=0;i<N;i++) cube->colors[N*N+N*i+N-1]=cube->colors[4*N*N+N*i+N-1];                      //elso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i+N-1]=cube->colors[5*N*N+N*i+N-1];                    //also <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i+N-1]=cube->colors[N*i+N-1];                          //hatso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i+N-1]=temp[i];                                              //felso <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[4*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                                            //jobb CW
				break;
			case 'r':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i+N-1];
				for(i=0;i<N;i++) cube->colors[N*N+N*i+N-1]=cube->colors[N*i+N-1];                            //elso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i+N-1]=cube->colors[5*N*N+N*i+N-1];                          //felso <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i+N-1]=cube->colors[4*N*N+N*i+N-1];                    //hatso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i+N-1]=temp[i];                                        //also <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[3*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                                            //jobb CCW
				break;
			case 'L':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i];
				for(i=0;i<N;i++) cube->colors[N*N+N*i]=cube->colors[N*i];                                    //elso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i]=cube->colors[5*N*N+N*i];                                  //felso <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i]=cube->colors[4*N*N+N*i];                            //hatso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i]=temp[i];                                            //also <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[3*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                                            //bal CW
				break;
			case 'l':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i];
				for(i=0;i<N;i++) cube->colors[N*N+N*i]=cube->colors[4*N*N+N*i];                              //elso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i]=cube->colors[5*N*N+N*i];                            //also <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i]=cube->colors[N*i];                                  //hatso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i]=temp[i];                                                  //felso <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[2*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                                            //bal CCW
				break;
			case 'X':
				for(i=0;i<N*N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=cube->colors[4*N*N+i];                                //elso <-- also
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=cube->colors[5*N*N+i];                              //also <-- hatso
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=cube->colors[i];                                    //hatso <-- felso
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                                                  //felso <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[4*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                                            //jobb CW
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[2*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                                            //bal CCW
				break;
			case 'x':
				for(i=0;i<N*N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=cube->colors[i];                                      //elso <-- felso
				for(i=0;i<N*N;i++) cube->colors[i]=cube->colors[5*N*N+i];                                    //felso <-- hatso
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=cube->colors[4*N*N+i];                              //hatso <-- also
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                                            //also <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[3*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                                            //jobb CCW
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[3*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                                            //bal CW
				break;
			case 'Y':
				for(i=0;i<N*N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=cube->colors[3*N*N+i];                                //elso <-- jobb
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=cube->colors[6*N*N-i-1];                            //jobb <-- hatso
				for(i=0;i<N*N;i++) cube->colors[6*N*N-i-1]=cube->colors[2*N*N+i];                            //hatso <-- bal
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                                            //bal <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                                                  //felso CW
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[4*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                                            //also CCW
				break;
			case 'y':
				for(i=0;i<N*N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=cube->colors[2*N*N+i];                                //elso <-- bal
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=cube->colors[6*N*N-i-1];                            //bal <-- hatso
				for(i=0;i<N*N;i++) cube->colors[6*N*N-i-1]=cube->colors[3*N*N+i];                            //hatso <-- jobb
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                                            //jobb <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                                                  //felso CCW
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[5*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                                            //also CW
				break;
			case 'Z':
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N-(j+1)*N+i];
				for(i=0;i<N;i++) for(j=0;j<N;j++) cube->colors[i*N+j]=cube->colors[3*N*N-(j+1)*N+i];         //felso <-- bal
				for(i=0;i<N;i++) for(j=0;j<N;j++) cube->colors[2*N*N+i*N+j]=cube->colors[5*N*N-(j+1)*N+i];   //bal <-- also
				for(i=0;i<N;i++) for(j=0;j<N;j++) cube->colors[4*N*N+i*N+j]=cube->colors[4*N*N-(j+1)*N+i];   //also <-- jobb
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                                            //jobb <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[2*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=temp[i];                                              //elso CW
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[5*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=temp[i];                                            //hatso CCW
				break;
			case 'z':
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[(j+1)*N-i-1];
				for(i=0;i<N;i++) for(j=0;j<N;j++) cube->colors[i*N+j]=cube->colors[3*N*N+(j+1)*N-i-1];       //felso <-- jobb
				for(i=0;i<N;i++) for(j=0;j<N;j++) cube->colors[3*N*N+i*N+j]=cube->colors[4*N*N+(j+1)*N-i-1]; //jobb <-- also
				for(i=0;i<N;i++) for(j=0;j<N;j++) cube->colors[4*N*N+i*N+j]=cube->colors[2*N*N+(j+1)*N-i-1]; //also <-- bal
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                                            //bal <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=temp[i];                                              //elso CCW
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[6*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=temp[i];                                            //hatso CW
				break;
		}
		m++;
	}
}

void randomScramble(char *scrmbl, unsigned length){
	static const char opts[]="FfBbUuDdLlRrXxYyZz";
	static int first=1;
	unsigned i;
	if(first){
		srand(time(NULL));
		first=0;
	}
	for(i=0;i<length;i++) scrmbl[i]=opts[rand()%18];
	scrmbl[length]=0;
}

static int isCombinationOf(char a, char b, char c, char* str){
	if(str[0]==a && str[1]==b && str[2]==c) return 1;
	if(str[0]==a && str[1]==c && str[2]==b) return 1;
	if(str[0]==b && str[1]==a && str[2]==c) return 1;
	if(str[0]==b && str[1]==c && str[2]==a) return 1;
	if(str[0]==c && str[1]==a && str[2]==b) return 1;
	if(str[0]==c && str[1]==b && str[2]==a) return 1;
	return 0;
}

static void removeChar(char *str, char c){
	char *src, *dst;
	for(src=dst=str; *src; src++){
		*dst=*src;
		if(*dst!=c) dst++;
	}
	*dst=0;
}

unsigned solve2x2(const cube_t *cube, char **moves){
	int N=cube->size, i, j, topCase=0, btmCase=0, found;
	char colors[24], temp[50];
	cube_t c={2,colors};

	if(N!=2) return 0;
	for(i=0;i<24;i++) c.colors[i]=cube->colors[i];
	*moves=calloc(256,sizeof(char));
	temp[0]=0;

	/* a W-O-G sarkot a FLU helyre forgatjuk (igy vegig konkret szinekkel dolgozhatunk) */
	if(isCombinationOf(c.colors[3],c.colors[5],c.colors[12],"GOW"))        //FRU
		strcpy(temp,"z");
	else if(isCombinationOf(c.colors[6],c.colors[11],c.colors[16],"GOW"))  //FLD
		strcpy(temp,"X");
	else if(isCombinationOf(c.colors[7],c.colors[14],c.colors[17],"GOW"))  //FRD
		strcpy(temp,"YX");
	else if(isCombinationOf(c.colors[8],c.colors[0],c.colors[22],"GOW"))   //BLU
		strcpy(temp,"x");
	else if(isCombinationOf(c.colors[13],c.colors[1],c.colors[23],"GOW"))  //BRU
		strcpy(temp,"xY");
	else if(isCombinationOf(c.colors[10],c.colors[18],c.colors[20],"GOW")) //BLD
		strcpy(temp,"xx");
	else if(isCombinationOf(c.colors[15],c.colors[19],c.colors[21],"GOW")) //BRD
		strcpy(temp,"xxz");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[4]=='W')      //elso lapon van a feher
		strcpy(temp,"Xy");
	else if(c.colors[9]=='W') //balra nez a feher
		strcpy(temp,"ZY");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* ha van feher a felso sorban, beforgatjuk a helyere */
	if(c.colors[5]=='W') //FRU eleje
		strcpy(temp,"rDRdrDR");
	else if(c.colors[12]=='W') //FRU jobb
		strcpy(temp,"rdRDrdR");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[23]=='W') //BRU hatulja
		strcpy(temp,"bdBDbdB");
	else if(c.colors[13]=='W') //BRU jobb
		strcpy(temp,"bDBdbDB");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[22]=='W') //BLU hatulja
		strcpy(temp,"lDLdlDL");
	else if(c.colors[8]=='W') //BLU jobb
		strcpy(temp,"ldLDldL");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* az also sorbol felvisszuk a fehereket */
	if(c.colors[3]!='W'){  //FRU teteje nem feher
		while(c.colors[17]!='W' && c.colors[7]!='W' && c.colors[14]!='W'){ //alaforgatunk egy feheret
			strcat(*moves,"d");
			move("d",&c);
		}
		if(c.colors[17]=='W')      //FRD alja feher
			strcpy(temp,"rddRDrdR");
		else if(c.colors[7]=='W')  //FRD eleje feher
			strcpy(temp,"FDf");
		else if(c.colors[14]=='W') //FRD jobb oldala feher
			strcpy(temp,"rdR");
	}
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[1]!='W'){  //BRU teteje nem feher
		while(c.colors[19]!='W' && c.colors[21]!='W' && c.colors[15]!='W'){ //alaforgatunk egy feheret
			strcat(*moves,"d");
			move("d",&c);
		}
		if(c.colors[19]=='W')      //BRD alja feher
			strcpy(temp,"bddBDbdB");
		else if(c.colors[21]=='W') //BRD hatulja feher
			strcpy(temp,"bdB");
		else if(c.colors[15]=='W') //BRD jobb oldala feher
			strcpy(temp,"RDr");
	}
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[0]!='W'){  //BLU teteje nem feher
		while(c.colors[18]!='W' && c.colors[20]!='W' && c.colors[10]!='W'){ //alaforgatunk egy feheret
			strcat(*moves,"d");
			move("d",&c);
		}
		if(c.colors[18]=='W')      //BLD alja feher
			strcpy(temp,"lddLDldL");
		else if(c.colors[20]=='W') //BLD hatulja feher
			strcpy(temp,"BDb");
		else if(c.colors[10]=='W') //BLD bal oldala feher
			strcpy(temp,"ldL");
	}
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* also reteg orientalasa (OLL) */
	if(c.colors[16]!='Y' && c.colors[17]=='Y' && c.colors[18]!='Y' && c.colors[19]=='Y'){
		if(c.colors[10]=='Y')
			strcpy(temp,"BRDrdb");
		else
			strcpy(temp,"RDrdrBRb");
	}
	else if(c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[18]!='Y' && c.colors[19]!='Y'){
		if(c.colors[20]=='Y')
			strcpy(temp,"RFDfdr");
		else
			strcpy(temp,"FDfdfRFr");
	}
	else if(c.colors[16]=='Y' && c.colors[17]!='Y' && c.colors[18]=='Y' && c.colors[19]!='Y'){
		if(c.colors[14]=='Y')
			strcpy(temp,"FLDldf");
		else
			strcpy(temp,"LDldlFLf");
	}
	else if(c.colors[16]!='Y' && c.colors[17]!='Y' && c.colors[18]=='Y' && c.colors[19]=='Y'){
		if(c.colors[6]=='Y')
			strcpy(temp,"LBDbdl");
		else
			strcpy(temp,"BDbdbLBl");
	}
	else if(c.colors[16]=='Y' && c.colors[17]!='Y' && c.colors[18]!='Y' && c.colors[19]=='Y'){
		if(c.colors[7]=='Y')
			strcpy(temp,"FLdldLDlf");
		else
			strcpy(temp,"BRdrdRDrb");
	}
	else if(c.colors[16]!='Y' && c.colors[17]=='Y' && c.colors[18]=='Y' && c.colors[19]!='Y'){
		if(c.colors[15]=='Y')
			strcpy(temp,"RFdfdFDfr");
		else
			strcpy(temp,"dBRdrdRDrb");
	}
	else if(c.colors[16]!='Y' && c.colors[17]!='Y' && c.colors[18]=='Y' && c.colors[19]!='Y'){
		if(c.colors[6]=='Y')
			strcpy(temp,"RDrDRDDr");
		else
			strcpy(temp,"LDDldLdl");
	}
	else if(c.colors[16]!='Y' && c.colors[17]!='Y' && c.colors[18]!='Y' && c.colors[19]=='Y'){
		if(c.colors[10]=='Y')
			strcpy(temp,"FDfDFDDf");
		else
			strcpy(temp,"BDDbdBdb");
	}
	else if(c.colors[16]=='Y' && c.colors[17]!='Y' && c.colors[18]!='Y' && c.colors[19]!='Y'){
		if(c.colors[14]=='Y')
			strcpy(temp,"BDbDBDDb");
		else
			strcpy(temp,"FDDfdFdf");
	}
	else if(c.colors[16]!='Y' && c.colors[17]=='Y' && c.colors[18]!='Y' && c.colors[19]!='Y'){
		if(c.colors[21]=='Y')
			strcpy(temp,"LDlDLDDl");
		else
			strcpy(temp,"RDDrdRdr");
	}
	else if(c.colors[16]!='Y' && c.colors[17]!='Y' && c.colors[18]!='Y' && c.colors[19]!='Y'){
		if(c.colors[6]=='Y' && c.colors[7]=='Y' && c.colors[20]=='Y' && c.colors[21]=='Y')
			strcpy(temp,"RRDDRDDRR");
		else if(c.colors[10]=='Y' && c.colors[11]=='Y' && c.colors[14]=='Y' && c.colors[15]=='Y')
			strcpy(temp,"FFDDFDDFF");
		else if(c.colors[10]=='Y' && c.colors[11]=='Y' && c.colors[7]=='Y' && c.colors[21]=='Y')
			strcpy(temp,"BRDrdRDrdb");
		else if(c.colors[6]=='Y' && c.colors[7]=='Y' && c.colors[10]=='Y' && c.colors[15]=='Y')
			strcpy(temp,"LBDbdBDbdl");
		else if(c.colors[14]=='Y' && c.colors[15]=='Y' && c.colors[6]=='Y' && c.colors[20]=='Y')
			strcpy(temp,"FLDldLDldf");
		else if(c.colors[20]=='Y' && c.colors[21]=='Y' && c.colors[11]=='Y' && c.colors[14]=='Y')
			strcpy(temp,"RFDfdFDfdr");
	}
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* ugy forgatjuk az also sort, hogy az FLD elem a helyen legyen */
	while(c.colors[6]!='G'){
			strcat(*moves,"d");
			move("d",&c);
	}

	/* mindket reteg permutalasa (PBL) */
	if(c.colors[5]=='G' && c.colors[12]=='R' && c.colors[13]=='R' && c.colors[23]=='B' && c.colors[22]=='B' && c.colors[8]=='O')      //felso reteg OK
		topCase=1;
	else if(c.colors[5]=='G' && c.colors[12]=='R' && c.colors[13]=='B' && c.colors[23]=='O' && c.colors[22]=='R' && c.colors[8]=='B') //felso retegben BRU <--> BLU
		topCase=2;
	else if(c.colors[5]=='B' && c.colors[12]=='O' && c.colors[13]=='R' && c.colors[23]=='B' && c.colors[22]=='G' && c.colors[8]=='R') //felso retegben FRU <--> BLU
		topCase=3;
	else if(c.colors[5]=='R' && c.colors[12]=='B' && c.colors[13]=='G' && c.colors[23]=='R' && c.colors[22]=='B' && c.colors[8]=='O') //felso retegben FRU <--> BRU
		topCase=4;
	else if(c.colors[5]=='R' && c.colors[12]=='B' && c.colors[13]=='B' && c.colors[23]=='O' && c.colors[22]=='G' && c.colors[8]=='R') //felso retegben FRU --> BRU --> BLU --> FRU
		topCase=5;
	else if(c.colors[5]=='B' && c.colors[12]=='O' && c.colors[13]=='G' && c.colors[23]=='R' && c.colors[22]=='R' && c.colors[8]=='B') //felso retegben FRU --> BLU --> BRU --> FRU
		topCase=6;
	if(c.colors[7]=='G' && c.colors[14]=='R' && c.colors[15]=='R' && c.colors[21]=='B' && c.colors[20]=='B' && c.colors[10]=='O')      //also reteg OK
		btmCase=1;
	else if(c.colors[7]=='G' && c.colors[14]=='R' && c.colors[15]=='B' && c.colors[21]=='O' && c.colors[20]=='R' && c.colors[10]=='B') //also retegben BRD <--> BLD
		btmCase=2;
	else if(c.colors[7]=='B' && c.colors[14]=='O' && c.colors[15]=='R' && c.colors[21]=='B' && c.colors[20]=='G' && c.colors[10]=='R') //also retegben FRD <--> BLD
		btmCase=3;
	else if(c.colors[7]=='R' && c.colors[14]=='B' && c.colors[15]=='G' && c.colors[21]=='R' && c.colors[20]=='B' && c.colors[10]=='O') //also retegben FRD <--> BRD
		btmCase=4;
	else if(c.colors[7]=='R' && c.colors[14]=='B' && c.colors[15]=='B' && c.colors[21]=='O' && c.colors[20]=='G' && c.colors[10]=='R') //also retegben FRD --> BRD --> BLD --> FRD
		btmCase=5;
	else if(c.colors[7]=='B' && c.colors[14]=='O' && c.colors[15]=='G' && c.colors[21]=='R' && c.colors[20]=='R' && c.colors[10]=='B') //also retegben FRD --> BLD --> BRD --> FRD
		btmCase=6;
	switch(10*topCase+btmCase){
		case 12: strcpy(temp,"BDbdbLbbdbdBDbl"); break;   //alul hatul csere
		case 21: strcpy(temp,"BUbubRbbubuBUbr"); break;   //felul hatul csere
		case 22: strcpy(temp,"llulluuffuff"); break;      //mindket retegben hatul csere

		case 13: strcpy(temp,"RFdfdFDfrFDfdfRFr"); break; //alul keresztbe csere
		case 31: strcpy(temp,"FRuruRUrfRUrurFRf"); break; //felul keresztbe csere
		case 33: strcpy(temp,"llffll"); break;            //mindket retegben keresztbe csere

		case 14: strcpy(temp,"RDrdrBrrdrdRDrb"); break;   //alul jobb oldalon csere
		case 41: strcpy(temp,"RUrurFrruruRUrf"); break;   //felul jobb oldalon csere
		case 44: strcpy(temp,"bbubbuullull"); break;      //mindket retegben jobb oldalon csere

		case 15: strcpy(temp,"rrbbrfRbbrFr"); break;      //alul CW forgatas
		case 51: strcpy(temp,"RRBBRFrBBRfR"); break;      //felul CCW forgatas
		case 55: strcpy(temp,"ffUlluuffUff"); break;      //alul CW, felul CCW forgatas

		case 16: strcpy(temp,"RfRBBrFRBBRR"); break;      //alul CCW forgatas
		case 61: strcpy(temp,"rFrbbRfrbbrr"); break;      //felul CW forgatas
		case 66: strcpy(temp,"rrUffuurrUrr"); break;      //alul CCW, felul CW forgatas

		case 23: strcpy(temp,"dRuRffrUrD"); break;        //felul hatul csere, alul keresztbe csere
		case 32: strcpy(temp,"LdLfflDl"); break;          //felul keresztbe csere, alul hatul csere

		case 24: strcpy(temp,"Ubbubbuullullu"); break;    //felul hatul csere, alul jobb oldalon csere
		case 42: strcpy(temp,"dbbubbuullullD"); break;    //felul jobb oldalon csere, alul hatul csere

		case 25: strcpy(temp,"dllulluuffuffdd"); break;   //felul hatul csere, alul CW forgatas
		case 52: strcpy(temp,"UllulluuffuffUU"); break;   //alul hatul csere, felul CCW forgatas

		case 26: strcpy(temp,"ddllulluuffuffU"); break;   //felul hatul csere, alul CCW forgatas
		case 62: strcpy(temp,"udbbubbuullullu"); break;   //alul hatul csere, felul CW forgatas

		case 34: strcpy(temp,"DLdLfflDld"); break;        //felul keresztbe csere, alul jobb oldalon csere
		case 43: strcpy(temp,"udRuRffrUrDU"); break;      //alul keresztbe csere, felul jobb oldalon csere

		case 35: strcpy(temp,"dLdLfflDldd"); break;       //felul keresztbe csere, alul CW forgatas
		case 53: strcpy(temp,"BuBrrbUbu"); break;         //alul keresztbe csere, felul CCW forgatas

		case 36: strcpy(temp,"DDLdLFFlDlD"); break;       //felul keresztbe csere, alul CCW forgatas
		case 63: strcpy(temp,"UBuBRRbUb"); break;         //alul keresztbe csere, felul CW forgatas

		case 45: strcpy(temp,"ddbbubbuullulld"); break;   //felul jobb oldalon csere, alul CW forgatas
		case 54: strcpy(temp,"UUbbubbuullullU"); break;   //alul jobb oldalon csere, felul CCW forgatas

		case 46: strcpy(temp,"DbbubbuullullDD"); break;   //felul jobb oldalon csere, alul CCW forgatas
		case 64: strcpy(temp,"ubbubbuullulluu"); break;   //alul jobb oldalon csere, felul CW forgatas

		case 56: strcpy(temp,"dffuffuurrurrd"); break;    //mindket retegben CCW forgatas
		case 65: strcpy(temp,"UffuffuurrurrD"); break;    //mindket retegben CW forgatas
	}
	strcat(*moves,temp);

	/* forgatasok kiszurese (helyettuk inkabb transzformaljuk a permutaciot) es trivialis egyszerusitesek */
	do{
		found=0;
		for(i=0;i<(int)strlen(*moves)-1;i++){
			if(((*moves)[i]=='U' && (*moves)[i+1]=='d') || ((*moves)[i]=='d' && (*moves)[i+1]=='U') || (*moves)[i]=='Y'){
				found=1;
				if((*moves)[i]!='Y') (*moves)[i+1]=' ';
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'F': (*moves)[j]='R'; break;
						case 'f': (*moves)[j]='r'; break;
						case 'B': (*moves)[j]='L'; break;
						case 'b': (*moves)[j]='l'; break;
						case 'L': (*moves)[j]='F'; break;
						case 'l': (*moves)[j]='f'; break;
						case 'R': (*moves)[j]='B'; break;
						case 'r': (*moves)[j]='b'; break;
						case 'X': (*moves)[j]='z'; break;
						case 'x': (*moves)[j]='Z'; break;
						case 'Z': (*moves)[j]='X'; break;
						case 'z': (*moves)[j]='x'; break;
					}
				}
			}
			else if(((*moves)[i]=='u' && (*moves)[i+1]=='D') || ((*moves)[i]=='D' && (*moves)[i+1]=='u') || (*moves)[i]=='y'){
				found=1;
				if((*moves)[i]!='y') (*moves)[i+1]=' ';
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'F': (*moves)[j]='L'; break;
						case 'f': (*moves)[j]='l'; break;
						case 'B': (*moves)[j]='R'; break;
						case 'b': (*moves)[j]='r'; break;
						case 'L': (*moves)[j]='B'; break;
						case 'l': (*moves)[j]='b'; break;
						case 'R': (*moves)[j]='F'; break;
						case 'r': (*moves)[j]='f'; break;
						case 'X': (*moves)[j]='Z'; break;
						case 'x': (*moves)[j]='z'; break;
						case 'Z': (*moves)[j]='x'; break;
						case 'z': (*moves)[j]='X'; break;
					}
				}
			}
			else if(((*moves)[i]=='f' && (*moves)[i+1]=='B') || ((*moves)[i]=='B' && (*moves)[i+1]=='f') || (*moves)[i]=='z'){
				found=1;
				if((*moves)[i]!='z') (*moves)[i+1]=' ';
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='R'; break;
						case 'u': (*moves)[j]='r'; break;
						case 'D': (*moves)[j]='L'; break;
						case 'd': (*moves)[j]='l'; break;
						case 'L': (*moves)[j]='U'; break;
						case 'l': (*moves)[j]='u'; break;
						case 'R': (*moves)[j]='D'; break;
						case 'r': (*moves)[j]='d'; break;
						case 'X': (*moves)[j]='y'; break;
						case 'x': (*moves)[j]='Y'; break;
						case 'Y': (*moves)[j]='X'; break;
						case 'y': (*moves)[j]='x'; break;
					}
				}
			}
			else if(((*moves)[i]=='F' && (*moves)[i+1]=='b') || ((*moves)[i]=='b' && (*moves)[i+1]=='F') || (*moves)[i]=='Z'){
				found=1;
				if((*moves)[i]!='Z') (*moves)[i+1]=' ';
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='L'; break;
						case 'u': (*moves)[j]='l'; break;
						case 'D': (*moves)[j]='R'; break;
						case 'd': (*moves)[j]='r'; break;
						case 'L': (*moves)[j]='D'; break;
						case 'l': (*moves)[j]='d'; break;
						case 'R': (*moves)[j]='U'; break;
						case 'r': (*moves)[j]='u'; break;
						case 'X': (*moves)[j]='Y'; break;
						case 'x': (*moves)[j]='y'; break;
						case 'Y': (*moves)[j]='x'; break;
						case 'y': (*moves)[j]='X'; break;
					}
				}
			}
			else if(((*moves)[i]=='l' && (*moves)[i+1]=='R') || ((*moves)[i]=='R' && (*moves)[i+1]=='l') || (*moves)[i]=='X'){
				found=1;
				if((*moves)[i]!='X') (*moves)[i+1]=' ';
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='F'; break;
						case 'u': (*moves)[j]='f'; break;
						case 'D': (*moves)[j]='B'; break;
						case 'd': (*moves)[j]='b'; break;
						case 'F': (*moves)[j]='D'; break;
						case 'f': (*moves)[j]='d'; break;
						case 'B': (*moves)[j]='U'; break;
						case 'b': (*moves)[j]='u'; break;
						case 'Y': (*moves)[j]='Z'; break;
						case 'y': (*moves)[j]='z'; break;
						case 'Z': (*moves)[j]='y'; break;
						case 'z': (*moves)[j]='Y'; break;
					}
				}
			}
			else if(((*moves)[i]=='L' && (*moves)[i+1]=='r') || ((*moves)[i]=='r' && (*moves)[i+1]=='L') || (*moves)[i]=='x'){
				found=1;
				if((*moves)[i]!='x') (*moves)[i+1]=' ';
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='B'; break;
						case 'u': (*moves)[j]='b'; break;
						case 'D': (*moves)[j]='F'; break;
						case 'd': (*moves)[j]='f'; break;
						case 'F': (*moves)[j]='U'; break;
						case 'f': (*moves)[j]='u'; break;
						case 'B': (*moves)[j]='D'; break;
						case 'b': (*moves)[j]='d'; break;
						case 'Y': (*moves)[j]='z'; break;
						case 'y': (*moves)[j]='Z'; break;
						case 'Z': (*moves)[j]='Y'; break;
						case 'z': (*moves)[j]='y'; break;
					}
				}
			}
		}
		for(i=0;i<(int)strlen(*moves)-2;i++){ //tripla forgatas helyett inkabb masik irany
			if((*moves)[i]==(*moves)[i+1] && (*moves)[i+1]==(*moves)[i+2]){
				found=1;
				(*moves)[i]=((*moves)[i]>90)?((*moves)[i]-32):((*moves)[i]+32);
				(*moves)[i+1]=(*moves)[i+2]=' ';
				i+=2;
			}
		}
		for(i=0;i<(int)strlen(*moves)-1;i++){ //oda-vissza forgatasok kiszurese
			if(((*moves)[i]-(*moves)[i+1]==32) || ((*moves)[i]-(*moves)[i+1]==-32)){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				i+=1;
			}
		}
		if(found) removeChar(*moves,' ');
	}while(found);
	if((*moves)[strlen(*moves)-1]=='X' || (*moves)[strlen(*moves)-1]=='x' || (*moves)[strlen(*moves)-1]=='Y' || (*moves)[strlen(*moves)-1]=='y' ||(*moves)[strlen(*moves)-1]=='Z' || (*moves)[strlen(*moves)-1]=='z')
		(*moves)[strlen(*moves)-1]=0;

	return strlen(*moves);
}

unsigned solve3x3(const cube_t *cube, char **moves){
	int N=cube->size, i, j, edgeCase=0, cornerCase=0, found;
	char colors[54], temp[50], f, l;
	cube_t c={3,colors};

	if(N!=3) return 0;
	for(i=0;i<54;i++) c.colors[i]=cube->colors[i];
	*moves=calloc(256,sizeof(char));
	temp[0]=0;

	/* orientacio: F zold, U feher */
	if(c.colors[13]=='W')      //elol van a feher
		strcpy(temp,"X");
	else if(c.colors[31]=='W') //jobb oldalon van a feher
		strcpy(temp,"z");
	else if(c.colors[49]=='W') //hatul van a feher
		strcpy(temp,"x");
	else if(c.colors[22]=='W') //bal oldalon van a feher
		strcpy(temp,"Z");
	else if(c.colors[40]=='W') //alul van a feher
		strcpy(temp,"zz");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[31]=='G')      //jobb oldalon van a zold
		strcpy(temp,"Y");
	else if(c.colors[49]=='G') //hatul van a zold
		strcpy(temp,"yy");
	else if(c.colors[22]=='G') //bal oldalon van a zold
		strcpy(temp,"y");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* kirakjuk a feher keresztet */
	for(i=0;i<4;i++){
		switch(i){
			case 0: f='G'; break;
			case 1: f='R'; break;
			case 2: f='B'; break;
			case 3: f='O'; break;
		}
		if(c.colors[1]=='W' && c.colors[52]==f)
			strcpy(temp,"BBDDFF");
		else if(c.colors[1]==f && c.colors[52]=='W')
			strcpy(temp,"bRdffr");
		else if(c.colors[3]=='W' && c.colors[19]==f)
			strcpy(temp,"llDff");
		else if(c.colors[3]==f && c.colors[19]=='W')
			strcpy(temp,"LF");
		else if(c.colors[5]=='W' && c.colors[28]==f)
			strcpy(temp,"rrdff");
		else if(c.colors[5]==f && c.colors[28]=='W')
			strcpy(temp,"rf");
		else if(c.colors[7]==f && c.colors[10]=='W')
			strcpy(temp,"ffdlFL");
		else if(c.colors[12]=='W' && c.colors[23]==f)
			strcpy(temp,"LDlff");
		else if(c.colors[12]==f && c.colors[23]=='W')
			strcpy(temp,"F");
		else if(c.colors[14]=='W' && c.colors[30]==f)
			strcpy(temp,"rdRff");
		else if(c.colors[14]==f && c.colors[30]=='W')
			strcpy(temp,"f");
		else if(c.colors[16]=='W' && c.colors[37]==f)
			strcpy(temp,"dlFL");
		else if(c.colors[16]==f && c.colors[37]=='W')
			strcpy(temp,"ff");
		else if(c.colors[21]=='W' && c.colors[48]==f)
			strcpy(temp,"llFll");
		else if(c.colors[21]==f && c.colors[48]=='W')
			strcpy(temp,"lDLff");
		else if(c.colors[32]=='W' && c.colors[50]==f)
			strcpy(temp,"rrfrr");
		else if(c.colors[32]==f && c.colors[50]=='W')
			strcpy(temp,"Rdrff");
		else if(c.colors[25]=='W' && c.colors[39]==f)
			strcpy(temp,"lFL");
		else if(c.colors[25]==f && c.colors[39]=='W')
			strcpy(temp,"Dff");
		else if(c.colors[34]=='W' && c.colors[41]==f)
			strcpy(temp,"Rfr");
		else if(c.colors[34]==f && c.colors[41]=='W')
			strcpy(temp,"dff");
		else if(c.colors[43]=='W' && c.colors[46]==f)
			strcpy(temp,"ddff");
		else if(c.colors[43]==f && c.colors[46]=='W')
			strcpy(temp,"dRfr");
		strcat(temp,"Y");
		strcat(*moves,temp); move(temp,&c); temp[0]=0;
	}

	/* kirakjuk az elso ket reteget (F2L) */
	for(i=0;i<4;i++){
		switch(i){
			case 0: f='G'; l='O'; break;
			case 1: f='R'; l='G'; break;
			case 2: f='B'; l='R'; break;
			case 3: f='O'; l='B'; break;
		}
		temp[0]=f;
		temp[1]=l;
		temp[2]='W';
		while(isCombinationOf(c.colors[8],c.colors[11],c.colors[27],temp) || (c.colors[14]==f && c.colors[30]==l) || (c.colors[14]==l && c.colors[30]==f)){
			strcat(*moves,"rDR");
			move("rDR",&c);	
		}
		while(isCombinationOf(c.colors[2],c.colors[29],c.colors[53],temp) || (c.colors[50]==f && c.colors[32]==l) || (c.colors[50]==l && c.colors[32]==f)){
			strcat(*moves,"RDr");
			move("RDr",&c);	
		}
		while(isCombinationOf(c.colors[0],c.colors[18],c.colors[51],temp) || (c.colors[48]==f && c.colors[21]==l) || (c.colors[48]==l && c.colors[21]==f)){
			strcat(*moves,"lDL");
			move("lDL",&c);	
		}
		while(!isCombinationOf(c.colors[15],c.colors[26],c.colors[36],temp) && !isCombinationOf(c.colors[9],c.colors[20],c.colors[6],temp)){
			strcat(*moves,"d");
			move("d",&c);	
		}
		temp[0]=0;
		if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[43]==f && c.colors[46]==l)
			strcpy(temp,"LDl");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[16]==f && c.colors[37]==l)
			strcpy(temp,"dfDF");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[12]==f && c.colors[23]==l)
			strcpy(temp,"DfDFDfDDF");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[12]==l && c.colors[23]==f)
			strcpy(temp,"DfdFdLDl");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[39]==l && c.colors[25]==f)
			strcpy(temp,"LdlddfdF");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[43]==l && c.colors[46]==f)
			strcpy(temp,"DfddFDfddF");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[41]==l && c.colors[34]==f)
			strcpy(temp,"DfdFDfddF");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[25]==l && c.colors[39]==f)
			strcpy(temp,"dLdlDLDl");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[34]==l && c.colors[41]==f)
			strcpy(temp,"dLDlDLDl");
		else if(c.colors[26]=='W' && c.colors[15]==f && c.colors[36]==l && c.colors[16]==l && c.colors[37]==f)
			strcpy(temp,"DfddFdLDl");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[34]==f && c.colors[41]==l)
			strcpy(temp,"fdF");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[39]==f && c.colors[25]==l)
			strcpy(temp,"DLdl");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[12]==f && c.colors[23]==l)
			strcpy(temp,"dLdldLddl");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[12]==l && c.colors[23]==f)
			strcpy(temp,"dLDlDfdF");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[39]==l && c.colors[25]==f)
			strcpy(temp,"dLddlDfdF");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[43]==l && c.colors[46]==f)
			strcpy(temp,"DfdFdfdF");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[41]==f && c.colors[34]==l)
			strcpy(temp,"dLddldLddl");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[43]==f && c.colors[46]==l)
			strcpy(temp,"dLDldLddl");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[16]==f && c.colors[37]==l)
			strcpy(temp,"DfDFdfdF");
		else if(c.colors[26]==l && c.colors[15]=='W' && c.colors[36]==f && c.colors[16]==l && c.colors[37]==f)
			strcpy(temp,"fDFddLDl");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[23]==l && c.colors[12]==f)
			strcpy(temp,"LDldLDldLDl");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[23]==f && c.colors[12]==l)
			strcpy(temp,"LdlDfDF");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[37]==f && c.colors[16]==l)
			strcpy(temp,"LDlddLDldLDl");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[41]==f && c.colors[34]==l)
			strcpy(temp,"ddLDlDLdl");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[43]==f && c.colors[46]==l)
			strcpy(temp,"DLddlDLdl");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[39]==f && c.colors[25]==l)
			strcpy(temp,"LddldLDl");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[25]==f && c.colors[39]==l)
			strcpy(temp,"fdFDDfdFDfdF");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[46]==f && c.colors[43]==l)
			strcpy(temp,"ddfdFdfDF");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[34]==f && c.colors[41]==l)
			strcpy(temp,"dfddFdfDF");
		else if(c.colors[26]==f && c.colors[15]==l && c.colors[36]=='W' && c.colors[16]==f && c.colors[37]==l)
			strcpy(temp,"fddFDfdF");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[23]==f && c.colors[12]==l)
			strcpy(temp,"LdlDfddFDfDDF");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[16]==f && c.colors[37]==l)
			strcpy(temp,"DLdldfDF");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[25]==f && c.colors[39]==l)
			strcpy(temp,"DDLdldfDF");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[46]==f && c.colors[43]==l)
			strcpy(temp,"dLdldfDF");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[34]==f && c.colors[41]==l)
			strcpy(temp,"LdldfDF");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[39]==f && c.colors[25]==l)
			strcpy(temp,"dfDFDLdl");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[43]==f && c.colors[46]==l)
			strcpy(temp,"fDFDLdl");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[41]==f && c.colors[34]==l)
			strcpy(temp,"DfDFDLdl");
		else if(c.colors[9]==f && c.colors[20]==l && c.colors[6]=='W' && c.colors[37]==f && c.colors[16]==l)
			strcpy(temp,"ddfDFDLdl");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[12]==f && c.colors[23]==l)
			strcpy(temp,"LdlDLddlDLdl");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[23]==f && c.colors[12]==l)
			strcpy(temp,"LDldLdlDDfdF");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[12]==f && c.colors[23]==l)
			strcpy(temp,"LdldLDldLddl");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[23]==f && c.colors[12]==l)
			strcpy(temp,"LdlDfdFdfdF");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[16]==f && c.colors[37]==l)
			strcpy(temp,"fDFdfDF");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[25]==f && c.colors[39]==l)
			strcpy(temp,"DfDFdfDF");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[46]==f && c.colors[43]==l)
			strcpy(temp,"DDfDFdfDF");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[34]==f && c.colors[41]==l)
			strcpy(temp,"dfDFdfDF");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[25]==l && c.colors[39]==f)
			strcpy(temp,"LDldLDl");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[46]==l && c.colors[43]==f)
			strcpy(temp,"DLDldLDl");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[34]==l && c.colors[41]==f)
			strcpy(temp,"DDLDldLDl");
		else if(c.colors[9]==l && c.colors[20]=='W' && c.colors[6]==f && c.colors[16]==l && c.colors[37]==f)
			strcpy(temp,"dLDldLDl");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[39]==f && c.colors[25]==l)
			strcpy(temp,"LdlDLdl");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[43]==f && c.colors[46]==l)
			strcpy(temp,"DLdlDLdl");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[41]==f && c.colors[34]==l)
			strcpy(temp,"DDLdlDLdl");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[37]==f && c.colors[16]==l)
			strcpy(temp,"dLdlDLdl");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[39]==l && c.colors[25]==f)
			strcpy(temp,"DfdFDfdF");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[43]==l && c.colors[46]==f)
			strcpy(temp,"DDfdFDfdF");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[41]==l && c.colors[34]==f)
			strcpy(temp,"dfdFDfdF");
		else if(c.colors[9]=='W' && c.colors[20]==f && c.colors[6]==l && c.colors[37]==l && c.colors[16]==f)
			strcpy(temp,"fdFDfdF");
		strcat(temp,"Y");
		strcat(*moves,temp); move(temp,&c); temp[0]=0;
	}

	/* utolso reteg orientalasa (OLL) */
	found=0;
	if(c.colors[36]=='Y' && c.colors[37]=='Y' && c.colors[38]=='Y' && c.colors[39]=='Y' && c.colors[41]=='Y' && c.colors[42]=='Y' && c.colors[43]=='Y' && c.colors[44]=='Y')
		found=1;
	while(!found){
		found=1;
		if(c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"LDbLBLLdlFLf");
		else if(c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"lFLfddlFLffddF");
		else if(c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"fbbRbRFddfRbF");
		else if(c.colors[42]=='Y' && c.colors[46]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"lddlFLfdfdFdL");
		else if(c.colors[44]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"LDlDlFLfddlFLf");
		else if(c.colors[44]=='Y' && c.colors[42]=='Y' && c.colors[38]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"lRffLrddlRFLrddlRffLr");
		else if(c.colors[44]=='Y' && c.colors[42]=='Y' && c.colors[46]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"lddFLDldffddFL");
		else if(c.colors[38]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"FLDlDfddfRFr");
		else if(c.colors[43]=='Y' && c.colors[37]=='Y' && c.colors[47]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"ldfDfRFrFL");
		else if(c.colors[43]=='Y' && c.colors[37]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"LdbbUbddBubbDl");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"FDLdlDLdlf");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"rbRdlDLdlDLrBR");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[47]=='Y' && c.colors[24]=='Y' && c.colors[26]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"RdlDrDLDlDL");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[24]=='Y' && c.colors[26]=='Y' && c.colors[33]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"LDlDLdlDLddl");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[45]=='Y' && c.colors[17]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"rDLdRDl");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[24]=='Y' && c.colors[33]=='Y')
			strcpy(temp,"lddLDlDL");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[37]=='Y' && c.colors[45]=='Y' && c.colors[15]=='Y')
			strcpy(temp,"lfRFLfrF");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[15]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"llUlddLulddl");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[45]=='Y' && c.colors[33]=='Y')
			strcpy(temp,"lfrFLfRF");
		else if(c.colors[44]=='Y' && c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[38]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[25]=='Y')
			strcpy(temp,"lRfLrddlRfLr");
		else if(c.colors[44]=='Y' && c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"rLDldRlFLf");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[38]=='Y' && c.colors[47]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"RFlFLffr");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[36]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"FlfLDLdl");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[36]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"ldLFlfDFLf");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[38]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"dLddldLdllfdFDL");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"FLDldLDldf");
		else if(c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[47]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"RfrFddrrBRbR");
		else if(c.colors[43]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[45]=='Y' && c.colors[16]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"dlddLDlDllBDbdl");
		else if(c.colors[43]=='Y' && c.colors[42]=='Y' && c.colors[39]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"RfflfLfr");
		else if(c.colors[43]=='Y' && c.colors[42]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[47]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"lddLLblBlddL");
		else if(c.colors[43]=='Y' && c.colors[39]=='Y' && c.colors[47]=='Y' && c.colors[24]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"frdRDrdRDF");
		else if(c.colors[43]=='Y' && c.colors[39]=='Y' && c.colors[45]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"lFlfllddbLBl");
		else if(c.colors[43]=='Y' && c.colors[39]=='Y' && c.colors[47]=='Y' && c.colors[45]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"lFLfddllblBl");
		else if(c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[37]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[25]=='Y' && c.colors[15]=='Y' && c.colors[33]=='Y')
			strcpy(temp,"LDlbLBdblB");
		else if(c.colors[44]=='Y' && c.colors[41]=='Y' && c.colors[37]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"rbRdlDLrBR");
		else if(c.colors[41]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[17]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"ddRllfLflffLfLr");
		else if(c.colors[44]=='Y' && c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[37]=='Y' && c.colors[46]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[33]=='Y')
			strcpy(temp,"bLbllDLDldLbb");
		else if(c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[15]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"RdfddfDFdFddFdr");
		else if(c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[37]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[15]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"ddlrrFrFRffrFLr");
		else if(c.colors[44]=='Y' && c.colors[42]=='Y' && c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[46]=='Y' && c.colors[26]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"llDlbLdllDLBl");
		else if(c.colors[39]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"rbbLBlBR");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[38]=='Y' && c.colors[37]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"LDLblBdl");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[16]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"LDldblFLfB");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"lFLDlfLFdf");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"RfrdRFrfDF");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y')
			strcpy(temp,"rbRldLDrBR");
		else if(c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"LBlRDrdLbl");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[38]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"FDLdlf");
		else if(c.colors[43]=='Y' && c.colors[42]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y' && c.colors[34]=='Y')
			strcpy(temp,"ldFDLdlfL");
		else if(c.colors[44]=='Y' && c.colors[43]=='Y' && c.colors[41]=='Y' && c.colors[38]=='Y' && c.colors[45]=='Y' && c.colors[25]=='Y' && c.colors[15]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"RDfdrDRFr");
		else if(c.colors[43]=='Y' && c.colors[42]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"fdrDRF");
		else if(c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"FLDldf");
		else if(c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[16]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"LDldlFLf");
		else if(c.colors[42]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[37]=='Y' && c.colors[46]=='Y' && c.colors[15]=='Y' && c.colors[34]=='Y' && c.colors[35]=='Y')
			strcpy(temp,"RDrDRdrdrBRb");
		else if(c.colors[44]=='Y' && c.colors[41]=='Y' && c.colors[37]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[24]=='Y' && c.colors[25]=='Y' && c.colors[17]=='Y')
			strcpy(temp,"ldLdlDLDLblB");
		else if(c.colors[44]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[36]=='Y' && c.colors[46]=='Y' && c.colors[45]=='Y' && c.colors[16]=='Y' && c.colors[33]=='Y')
			strcpy(temp,"lFLDldfDL");
		else if(c.colors[42]=='Y' && c.colors[41]=='Y' && c.colors[39]=='Y' && c.colors[38]=='Y' && c.colors[47]=='Y' && c.colors[46]=='Y' && c.colors[26]=='Y' && c.colors[16]=='Y')
			strcpy(temp,"RfrdRDFdr");
		else{
			found=0;
			strcat(*moves,"Y");
			move("Y",&c);
		}
	}
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* orientacio: F zold, U sarga */
	if(c.colors[13]=='Y')      //elol van a sarga
		strcpy(temp,"X");
	else if(c.colors[31]=='Y') //jobb oldalon van a sarga
		strcpy(temp,"z");
	else if(c.colors[49]=='Y') //hatul van a sarga
		strcpy(temp,"x");
	else if(c.colors[22]=='Y') //bal oldalon van a sarga
		strcpy(temp,"Z");
	else if(c.colors[40]=='Y') //alul van a sarga
		strcpy(temp,"zz");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[31]=='G')      //jobb oldalon van a zold
		strcpy(temp,"Y");
	else if(c.colors[49]=='G') //hatul van a zold
		strcpy(temp,"yy");
	else if(c.colors[22]=='G') //bal oldalon van a zold
		strcpy(temp,"y");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;

	/* a zold-sarga elet a helyere forgatjuk */
	while(c.colors[10]!='G'){
		strcat(*moves,"u");
		move("u",&c);
	}

	/* utolso reteg permutalasa (PLL) */
	temp[0]=c.colors[52];
	temp[1]=c.colors[28];
	temp[2]=c.colors[19];
	temp[3]=0;
	if(strcmp(temp,"BOR")==0)
		edgeCase=1;
	else if(strcmp(temp,"ROB")==0)
		edgeCase=2;
	else if(strcmp(temp,"BRO")==0)
		edgeCase=3;
	else if(strcmp(temp,"ORB")==0)
		edgeCase=4;
	else if(strcmp(temp,"OBR")==0)
		edgeCase=5;
	else if(strcmp(temp,"RBO")==0)
		edgeCase=6;
	temp[0]=c.colors[9];
	temp[1]=c.colors[11];
	temp[2]=c.colors[18];
	temp[3]=c.colors[20];
	temp[4]=c.colors[27];
	temp[5]=c.colors[29];
	temp[6]=c.colors[51];
	temp[7]=c.colors[53];
	temp[8]=0;
	if(strcmp(temp,"ORBGGBOR")==0)
		cornerCase=1;
	else if(strcmp(temp,"GOORBBGR")==0)
		cornerCase=2;
	else if(strcmp(temp,"RROBGOGB")==0)
		cornerCase=3;
	else if(strcmp(temp,"RRBBGGOO")==0)
		cornerCase=4;
	else if(strcmp(temp,"BBGORGRO")==0)
		cornerCase=5;
	else if(strcmp(temp,"ROOBBRGG")==0)
		cornerCase=6;
	else if(strcmp(temp,"GBORROGB")==0)
		cornerCase=7;
	else if(strcmp(temp,"BGGOOBRR")==0)
		cornerCase=8;
	else if(strcmp(temp,"OORGBRBG")==0)
		cornerCase=9;
	else if(strcmp(temp,"BRROGGBO")==0)
		cornerCase=10;
	else if(strcmp(temp,"RGBBOROG")==0)
		cornerCase=11;
	else if(strcmp(temp,"OBBGRROG")==0)
		cornerCase=12;
	else if(strcmp(temp,"OBGGRORB")==0)
		cornerCase=13;
	else if(strcmp(temp,"GGBROBOR")==0)
		cornerCase=14;
	else if(strcmp(temp,"BGROORBG")==0)
		cornerCase=15;
	else if(strcmp(temp,"GORRBGBO")==0)
		cornerCase=16;
	else if(strcmp(temp,"OOGGBBRR")==0)
		cornerCase=17;
	else if(strcmp(temp,"BROOGBGR")==0)
		cornerCase=18;
	else if(strcmp(temp,"GBBRRGOO")==0)
		cornerCase=19;
	else if(strcmp(temp,"ORRGGOBB")==0)
		cornerCase=20;
	else if(strcmp(temp,"BBOORRGG")==0)
		cornerCase=21;
	else if(strcmp(temp,"RGGBOORB")==0)
		cornerCase=22;
	else if(strcmp(temp,"ROGBBGRO")==0)
		cornerCase=23;
	else if(strcmp(temp,"GGRROOBB")==0)
		cornerCase=24;
	temp[0]=0;
	switch(100*edgeCase+cornerCase){
		case 101: strcpy(temp,"BlbRBLbRRfLFRflF"); break;
		case 102: strcpy(temp,"BlBrrbLBrrbb"); break;
		case 103: strcpy(temp,"lBlffLblffll"); break;
		case 108: strcpy(temp,"LfLbblFLbbll"); break;
		case 109: strcpy(temp,"RbRffrBRffrr"); break;
		case 110: strcpy(temp,"fLfrrFlfrrff"); break;
		case 111: strcpy(temp,"bRbllBrbllbb"); break;
		case 113: strcpy(temp,"FrFllfRFllff"); break;
		case 119: strcpy(temp,"rFrbbRfrbbrr"); break;
		case 121: strcpy(temp,"RlRlDRlRlUURlRlDRlRlUU"); break;
		case 123: strcpy(temp,"RbrFRBrFFlBLFlbL"); break;
		case 204: strcpy(temp,"URuRURURururr"); break;
		case 205: strcpy(temp,"uluLffDrURuRdff"); break;
		case 206: strcpy(temp,"UllDfUfuFdllbUB"); break;
		case 207: strcpy(temp,"FRuruRUrfRUrurFRf"); break;
		case 212: strcpy(temp,"UBUbrrdFufUfDrr"); break;
		case 214: strcpy(temp,"rUluuRuruuRLu"); break;
		case 215: strcpy(temp,"bUbulbllulUlBLB"); break;
		case 216: strcpy(temp,"BuubuuBlbuBUBLbbU"); break;
		case 217: strcpy(temp,"ubbUBUbububUb"); break;
		case 218: strcpy(temp,"ubbdRuRUrDbbLul"); break;
		case 220: strcpy(temp,"luuLuulBLUlulbllu"); break;
		case 222: strcpy(temp,"LUlbLUlulBllulu"); break;
		case 304: strcpy(temp,"RlRlDRlRlUrLffRlRlbbrLu"); break;
		case 305: strcpy(temp,"uuFUfufLffufuFUfl"); break;
		case 306: strcpy(temp,"uuBUbubRbbubuBUbr"); break;
		case 307: strcpy(temp,"bUfuuBuFbUfuuBuFu"); break;
		case 312: strcpy(temp,"uubuubulbllulUlBLuB"); break;
		case 314: strcpy(temp,"luuluflffufUfLFuL"); break;
		case 315: strcpy(temp,"BuFuubUfBuFuubUfU"); break;
		case 316: strcpy(temp,"RUrurFrruruRUrf"); break;
		case 317: strcpy(temp,"urLrLDrLrLUrLffrLrLbbrLuu"); break;
		case 318: strcpy(temp,"uufuufurfrrurUrFRuF"); break;
		case 320: strcpy(temp,"ruurubrbbubUbRBuR"); break;
		case 322: strcpy(temp,"LUlulBlluluLUlb"); break;
		case 401: strcpy(temp,"UlUluflffufUfLFL"); break;
		case 402: strcpy(temp,"lldBuBUbDllFuf"); break;
		case 403: strcpy(temp,"UfuuFuufLFUfuflffu"); break;
		case 408: strcpy(temp,"fuFrrDbUBuBdrr"); break;
		case 409: strcpy(temp,"uuffDrUruRdfflUL"); break;
		case 410: strcpy(temp,"ULuuluuLfluLULFllU"); break;
		case 411: strcpy(temp,"UFUflFUfufLffufu"); break;
		case 413: strcpy(temp,"uuLUlbbdRurUrDbb"); break;
		case 419: strcpy(temp,"UbUfuuBubuuBFu"); break;
		case 421: strcpy(temp,"uuBuBUBUBububb"); break;
		case 423: strcpy(temp,"URBubuBUbrBUbubRBr"); break;
		case 424: strcpy(temp,"llULUlululUl"); break;
		case 504: strcpy(temp,"UFuFUFUFufuff"); break;
		case 505: strcpy(temp,"URUrffdLulUlDff"); break;
		case 506: strcpy(temp,"urrdFuFUfDrrBub"); break;
		case 507: strcpy(temp,"rUrubrbbubUbRBR"); break;
		case 512: strcpy(temp,"UbbDlUluLdbbrUR"); break;
		case 514: strcpy(temp,"BUbrBUbubRbbubu"); break;
		case 515: strcpy(temp,"LFufuFUflFUfufLFl"); break;
		case 516: strcpy(temp,"fUbuuFufuuFBu"); break;
		case 517: strcpy(temp,"urrURUrururUr"); break;
		case 518: strcpy(temp,"ubuBllDfUFuFdll"); break;
		case 520: strcpy(temp,"RuuruuRbruRURBrrU"); break;
		case 522: strcpy(temp,"buuBuubRBUbubrbbu"); break;
		case 601: strcpy(temp,"ufUfurfrrurUrFRF"); break;
		case 602: strcpy(temp,"ulUruuLuluuLRu"); break;
		case 603: strcpy(temp,"UUffdLuLUlDffRur"); break;
		case 608: strcpy(temp,"uRUrfRUrurFrruru"); break;
		case 609: strcpy(temp,"uFuufuuFrfuFUFRffU"); break;
		case 610: strcpy(temp,"uuruRbbDlULuLdbb"); break;
		case 611: strcpy(temp,"rrDbUbuBdrrfUF"); break;
		case 613: strcpy(temp,"uruuRuurFRUrurfrru"); break;
		case 619: strcpy(temp,"FUflldBubUbDll"); break;
		case 621: strcpy(temp,"uuffUFUfufufUf"); break;
		case 623: strcpy(temp,"uBLuluLUlbLUlulBLb"); break;
		case 624: strcpy(temp,"LuLULULulull"); break;
	}
	strcat(*moves,temp);

	/* forgatasok kiszurese (helyettuk inkabb transzformaljuk a permutaciot) es trivialis egyszerusitesek */
	do{
		found=0;
		for(i=0;i<(int)strlen(*moves);i++){
			if((*moves)[i]=='Y'){
				found=1;
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'F': (*moves)[j]='R'; break;
						case 'f': (*moves)[j]='r'; break;
						case 'B': (*moves)[j]='L'; break;
						case 'b': (*moves)[j]='l'; break;
						case 'L': (*moves)[j]='F'; break;
						case 'l': (*moves)[j]='f'; break;
						case 'R': (*moves)[j]='B'; break;
						case 'r': (*moves)[j]='b'; break;
						case 'X': (*moves)[j]='z'; break;
						case 'x': (*moves)[j]='Z'; break;
						case 'Z': (*moves)[j]='X'; break;
						case 'z': (*moves)[j]='x'; break;
					}
				}
			}
			else if((*moves)[i]=='y'){
				found=1;
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'F': (*moves)[j]='L'; break;
						case 'f': (*moves)[j]='l'; break;
						case 'B': (*moves)[j]='R'; break;
						case 'b': (*moves)[j]='r'; break;
						case 'L': (*moves)[j]='B'; break;
						case 'l': (*moves)[j]='b'; break;
						case 'R': (*moves)[j]='F'; break;
						case 'r': (*moves)[j]='f'; break;
						case 'X': (*moves)[j]='Z'; break;
						case 'x': (*moves)[j]='z'; break;
						case 'Z': (*moves)[j]='x'; break;
						case 'z': (*moves)[j]='X'; break;
					}
				}
			}
			else if((*moves)[i]=='z'){
				found=1;
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='R'; break;
						case 'u': (*moves)[j]='r'; break;
						case 'D': (*moves)[j]='L'; break;
						case 'd': (*moves)[j]='l'; break;
						case 'L': (*moves)[j]='U'; break;
						case 'l': (*moves)[j]='u'; break;
						case 'R': (*moves)[j]='D'; break;
						case 'r': (*moves)[j]='d'; break;
						case 'X': (*moves)[j]='y'; break;
						case 'x': (*moves)[j]='Y'; break;
						case 'Y': (*moves)[j]='X'; break;
						case 'y': (*moves)[j]='x'; break;
					}
				}
			}
			else if((*moves)[i]=='Z'){
				found=1;
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='L'; break;
						case 'u': (*moves)[j]='l'; break;
						case 'D': (*moves)[j]='R'; break;
						case 'd': (*moves)[j]='r'; break;
						case 'L': (*moves)[j]='D'; break;
						case 'l': (*moves)[j]='d'; break;
						case 'R': (*moves)[j]='U'; break;
						case 'r': (*moves)[j]='u'; break;
						case 'X': (*moves)[j]='Y'; break;
						case 'x': (*moves)[j]='y'; break;
						case 'Y': (*moves)[j]='x'; break;
						case 'y': (*moves)[j]='X'; break;
					}
				}
			}
			else if((*moves)[i]=='X'){
				found=1;
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='F'; break;
						case 'u': (*moves)[j]='f'; break;
						case 'D': (*moves)[j]='B'; break;
						case 'd': (*moves)[j]='b'; break;
						case 'F': (*moves)[j]='D'; break;
						case 'f': (*moves)[j]='d'; break;
						case 'B': (*moves)[j]='U'; break;
						case 'b': (*moves)[j]='u'; break;
						case 'Y': (*moves)[j]='Z'; break;
						case 'y': (*moves)[j]='z'; break;
						case 'Z': (*moves)[j]='y'; break;
						case 'z': (*moves)[j]='Y'; break;
					}
				}
			}
			else if((*moves)[i]=='x'){
				found=1;
				(*moves)[i]=' ';
				for(j=i+1;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='B'; break;
						case 'u': (*moves)[j]='b'; break;
						case 'D': (*moves)[j]='F'; break;
						case 'd': (*moves)[j]='f'; break;
						case 'F': (*moves)[j]='U'; break;
						case 'f': (*moves)[j]='u'; break;
						case 'B': (*moves)[j]='D'; break;
						case 'b': (*moves)[j]='d'; break;
						case 'Y': (*moves)[j]='z'; break;
						case 'y': (*moves)[j]='Z'; break;
						case 'Z': (*moves)[j]='Y'; break;
						case 'z': (*moves)[j]='y'; break;
					}
				}
			}
		}
		for(i=0;i<(int)strlen(*moves)-2;i++){ //tripla forgatas helyett inkabb masik irany
			if((*moves)[i]==(*moves)[i+1] && (*moves)[i+1]==(*moves)[i+2]){
				found=1;
				(*moves)[i]=((*moves)[i]>90)?((*moves)[i]-32):((*moves)[i]+32);
				(*moves)[i+1]=(*moves)[i+2]=' ';
				i+=2;
			}
		}
		for(i=0;i<(int)strlen(*moves)-1;i++){ //oda-vissza forgatasok kiszurese
			if(((*moves)[i]-(*moves)[i+1]==32) || ((*moves)[i]-(*moves)[i+1]==-32)){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				i+=1;
			}
		}
		if(found) removeChar(*moves,' ');
	}while(found);

	return strlen(*moves);
}
