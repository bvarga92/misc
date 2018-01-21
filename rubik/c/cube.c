#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
				for(i=0;i<N;i++) cube->colors[N*N-1-i]=cube->colors[2*N*N+N*i+N-1];       //felso <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+N*i+N-1]=cube->colors[4*N*N+i];       //bal <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N-i-1]=cube->colors[3*N*N+N*i];       //also <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i]=temp[i];                         //jobb <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[2*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=temp[i];                           //elso CW
				break;
			case 'f':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N-N+i];
				for(i=0;i<N;i++) cube->colors[N*N-N+i]=cube->colors[3*N*N+N*i];           //felso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i]=cube->colors[4*N*N+N-i-1];       //jobb <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+i]=cube->colors[2*N*N+N*i+N-1];       //also <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-i*N-1]=temp[i];                       //bal <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[N*N+i]=temp[i];                           //elso CCW
				break;
			case 'B':
				for(i=0;i<N;i++) temp[i]=cube->colors[i];
				for(i=0;i<N;i++) cube->colors[i]=cube->colors[3*N*N+N*i+N-1];             //felso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i+N-1]=cube->colors[5*N*N-i-1];     //jobb <-- also
				for(i=0;i<N;i++) cube->colors[5*N*N-N+i]=cube->colors[2*N*N+N*i];         //also <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+N*i]=temp[N-i-1];                     //bal <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[6*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=temp[i];                         //hatso CW
				break;
			case 'b':
				for(i=0;i<N;i++) temp[i]=cube->colors[i];
				for(i=0;i<N;i++) cube->colors[N-i-1]=cube->colors[2*N*N+N*i];             //felso <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-N*i-N]=cube->colors[5*N*N-i-1];       //bal <-- also
				for(i=0;i<N;i++) cube->colors[5*N*N-i-1]=cube->colors[3*N*N+N*i+N-1];     //also <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+N*i+N-1]=temp[i];                     //jobb <-- felso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[5*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[5*N*N+i]=temp[i];                         //hatso CCW
				break;
			case 'U':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N;i++) cube->colors[N*N+i]=cube->colors[3*N*N+i];               //elso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+i]=cube->colors[6*N*N-i-1];           //jobb <-- hatso
				for(i=0;i<N;i++) cube->colors[6*N*N-i-1]=cube->colors[2*N*N+i];           //hatso <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+i]=temp[i];                           //bal <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                               //felso CW
				break;
			case 'u':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+i];
				for(i=0;i<N;i++) cube->colors[N*N+i]=cube->colors[2*N*N+i];               //elso <-- bal
				for(i=0;i<N;i++) cube->colors[2*N*N+i]=cube->colors[6*N*N-i-1];           //bal <-- hatso
				for(i=0;i<N;i++) cube->colors[6*N*N-i-1]=cube->colors[3*N*N+i];           //hatso <-- jobb
				for(i=0;i<N;i++) cube->colors[3*N*N+i]=temp[i];                           //jobb <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[i]=temp[i];                               //felso CCW
				break;
			case 'D':
				for(i=0;i<N;i++) temp[i]=cube->colors[2*N*N-N+i];
				for(i=0;i<N;i++) cube->colors[2*N*N-N+i]=cube->colors[3*N*N-N+i];         //elso <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-i-1]=cube->colors[5*N*N+i];           //bal <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+i]=cube->colors[4*N*N-i-1];           //hatso <-- jobb
				for(i=0;i<N;i++) cube->colors[4*N*N-N+i]=temp[i];                         //jobb <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[5*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                         //also CW
				break;
			case 'd':
				for(i=0;i<N;i++) temp[i]=cube->colors[2*N*N-N+i];
				for(i=0;i<N;i++) cube->colors[2*N*N-N+i]=cube->colors[4*N*N-N+i];         //elso <-- jobb
				for(i=0;i<N;i++) cube->colors[4*N*N-i-1]=cube->colors[5*N*N+i];           //jobb <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+i]=cube->colors[3*N*N-i-1];           //hatso <-- bal
				for(i=0;i<N;i++) cube->colors[3*N*N-N+i]=temp[i];                         //bal <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[4*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[4*N*N+i]=temp[i];                         //also CCW
				break;
			case 'R':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i+N-1];
				for(i=0;i<N;i++) cube->colors[N*N+N*i+N-1]=cube->colors[4*N*N+N*i+N-1];   //elso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i+N-1]=cube->colors[5*N*N+N*i+N-1]; //also <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i+N-1]=cube->colors[N*i+N-1];       //hatso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i+N-1]=temp[i];                           //felso <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[4*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                         //jobb CW
				break;
			case 'r':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i+N-1];
				for(i=0;i<N;i++) cube->colors[N*N+N*i+N-1]=cube->colors[N*i+N-1];         //elso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i+N-1]=cube->colors[5*N*N+N*i+N-1];       //felso <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i+N-1]=cube->colors[4*N*N+N*i+N-1]; //hatso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i+N-1]=temp[i];                     //also <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[3*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[3*N*N+i]=temp[i];                         //jobb CCW
				break;
			case 'L':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i];
				for(i=0;i<N;i++) cube->colors[N*N+N*i]=cube->colors[N*i];                 //elso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i]=cube->colors[5*N*N+N*i];               //felso <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i]=cube->colors[4*N*N+N*i];         //hatso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i]=temp[i];                         //also <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[3*N*N-(j+1)*N+i];
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                         //bal CW
				break;
			case 'l':
				for(i=0;i<N;i++) temp[i]=cube->colors[N*N+N*i];
				for(i=0;i<N;i++) cube->colors[N*N+N*i]=cube->colors[4*N*N+N*i];           //elso <-- also
				for(i=0;i<N;i++) cube->colors[4*N*N+N*i]=cube->colors[5*N*N+N*i];         //also <-- hatso
				for(i=0;i<N;i++) cube->colors[5*N*N+N*i]=cube->colors[N*i];               //hatso <-- felso
				for(i=0;i<N;i++) cube->colors[N*i]=temp[i];                               //felso <-- elso
				for(i=0;i<N;i++) for(j=0;j<N;j++) temp[i*N+j]=cube->colors[2*N*N+(j+1)*N-i-1];
				for(i=0;i<N*N;i++) cube->colors[2*N*N+i]=temp[i];                         //bal CCW
				break;
		}
		m++;
	}
}

void randomScramble(char *scrmbl, unsigned length){
	static const char opts[]="FfBbUuDdLlRr";
	static int first=1;
	unsigned i;
	if(first){
		srand(time(NULL));
		first=0;
	}
	for(i=0;i<length;i++) scrmbl[i]=opts[rand()%12];
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
	int N=cube->size, i, j, topCase, btmCase, found;
	char colors[24], temp[50];
	cube_t c={2,colors};

	if(N!=2) return 0;
	for(i=0;i<24;i++) c.colors[i]=cube->colors[i];
	*moves=calloc(256,sizeof(char));
	temp[0]=0;

	/* a W-O-G sarkot a FLU helyre forgatjuk (igy vegig konkret szinekkel dolgozhatunk) */
	if(isCombinationOf(c.colors[3],c.colors[5],c.colors[12],"GOW"))        //FRU
		strcpy(temp,"fB");
	else if(isCombinationOf(c.colors[6],c.colors[11],c.colors[16],"GOW"))  //FLD
		strcpy(temp,"lR");
	else if(isCombinationOf(c.colors[7],c.colors[14],c.colors[17],"GOW"))  //FRD
		strcpy(temp,"UdlR");
	else if(isCombinationOf(c.colors[8],c.colors[0],c.colors[22],"GOW"))   //BLU
		strcpy(temp,"Lr");
	else if(isCombinationOf(c.colors[13],c.colors[1],c.colors[23],"GOW"))  //BRU
		strcpy(temp,"LrUd");
	else if(isCombinationOf(c.colors[10],c.colors[18],c.colors[20],"GOW")) //BLD
		strcpy(temp,"LLrr");
	else if(isCombinationOf(c.colors[15],c.colors[19],c.colors[21],"GOW")) //BRD
		strcpy(temp,"LLrrfB");
	strcat(*moves,temp); move(temp,&c); temp[0]=0;
	if(c.colors[4]=='W')      //elso lapon van a feher
		strcpy(temp,"RluD");
	else if(c.colors[9]=='W') //balra nez a feher
		strcpy(temp,"FbUd");
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
			if(((*moves)[i]=='U' && (*moves)[i+1]=='d') || ((*moves)[i]=='d' && (*moves)[i+1]=='U')){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				for(j=i+2;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'F': (*moves)[j]='R'; break;
						case 'f': (*moves)[j]='r'; break;
						case 'B': (*moves)[j]='L'; break;
						case 'b': (*moves)[j]='l'; break;
						case 'L': (*moves)[j]='F'; break;
						case 'l': (*moves)[j]='f'; break;
						case 'R': (*moves)[j]='B'; break;
						case 'r': (*moves)[j]='b'; break;
					}
				}
			}
			else if(((*moves)[i]=='u' && (*moves)[i+1]=='D') || ((*moves)[i]=='D' && (*moves)[i+1]=='u')){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				for(j=i+2;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'F': (*moves)[j]='L'; break;
						case 'f': (*moves)[j]='l'; break;
						case 'B': (*moves)[j]='R'; break;
						case 'b': (*moves)[j]='r'; break;
						case 'L': (*moves)[j]='B'; break;
						case 'l': (*moves)[j]='b'; break;
						case 'R': (*moves)[j]='F'; break;
						case 'r': (*moves)[j]='f'; break;
					}
				}
			}
			else if(((*moves)[i]=='f' && (*moves)[i+1]=='B') || ((*moves)[i]=='B' && (*moves)[i+1]=='f')){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				for(j=i+2;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='R'; break;
						case 'u': (*moves)[j]='r'; break;
						case 'D': (*moves)[j]='L'; break;
						case 'd': (*moves)[j]='l'; break;
						case 'L': (*moves)[j]='U'; break;
						case 'l': (*moves)[j]='u'; break;
						case 'R': (*moves)[j]='D'; break;
						case 'r': (*moves)[j]='d'; break;
					}
				}
			}
			else if(((*moves)[i]=='F' && (*moves)[i+1]=='b') || ((*moves)[i]=='b' && (*moves)[i+1]=='F')){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				for(j=i+2;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='L'; break;
						case 'u': (*moves)[j]='l'; break;
						case 'D': (*moves)[j]='R'; break;
						case 'd': (*moves)[j]='r'; break;
						case 'L': (*moves)[j]='D'; break;
						case 'l': (*moves)[j]='d'; break;
						case 'R': (*moves)[j]='U'; break;
						case 'r': (*moves)[j]='u'; break;
					}
				}
			}
			else if(((*moves)[i]=='l' && (*moves)[i+1]=='R') || ((*moves)[i]=='R' && (*moves)[i+1]=='l')){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				for(j=i+2;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='F'; break;
						case 'u': (*moves)[j]='f'; break;
						case 'D': (*moves)[j]='B'; break;
						case 'd': (*moves)[j]='b'; break;
						case 'F': (*moves)[j]='D'; break;
						case 'f': (*moves)[j]='d'; break;
						case 'B': (*moves)[j]='U'; break;
						case 'b': (*moves)[j]='u'; break;
					}
				}
			}
			else if(((*moves)[i]=='L' && (*moves)[i+1]=='r') || ((*moves)[i]=='r' && (*moves)[i+1]=='L')){
				found=1;
				(*moves)[i]=(*moves)[i+1]=' ';
				for(j=i+2;j<strlen(*moves);j++){
					switch((*moves)[j]){
						case 'U': (*moves)[j]='B'; break;
						case 'u': (*moves)[j]='b'; break;
						case 'D': (*moves)[j]='F'; break;
						case 'd': (*moves)[j]='f'; break;
						case 'F': (*moves)[j]='U'; break;
						case 'f': (*moves)[j]='u'; break;
						case 'B': (*moves)[j]='D'; break;
						case 'b': (*moves)[j]='d'; break;
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
