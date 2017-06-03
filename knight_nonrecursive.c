#include <stdio.h>
#include <stdlib.h>

/* sakktabla merete */
#define N 8
/* kiindulo mezo koordinatai */
#define STARTI 5
#define STARTJ 5
/* ide szeretnenk megerkezni */
#define DESTI 0
#define DESTJ 7

typedef struct{
    int copy_of_v2, copy_of_v3;
    unsigned posi, posj; //az eddig megtett lepesek szama
    unsigned count; //aktualis pozicio es
    int board[N][N]; //a tabla
    int choices[8]; //ebbol a poziciobol milyen lepesek lehetsegesek (a possibleJumps tombben tartoltak kozul)
} model;

model m, *t;

const int possibleJumps[8][8]={{1,2},{2,1},{-2,1},{-1,2},{-2,-1},{-1,-2},{1,-2},{2,-1}}; //egy huszar lehetseges lepesei

int v0, //vezerlovaltozo
    v1, //korabbi dontesek szama
    v2, //valasztasi lehetosegek szama
    v3; //aktualis lehetoseg sorszama

/* a celt elertuk? */
int ft1(){
    return (m.posi==DESTI)&&(m.posj==DESTJ);
}

/* egyaltalan lehetseges meg a celt elerni? */
int ft2(){
    return 1; /* fa1 ugyis megmondja, hogy tudunk-e meg lepni */
}

/* elokeszites */
void pa0(){
    unsigned i, j, q, nexti, nextj, ch=0;
    for(i=0;i<N;i++) for(j=0;j<N;j++) m.board[i][j]=-1;
    m.board[STARTI][STARTJ]=0;
    m.posi=STARTI;
    m.posj=STARTJ;
    m.count=0;
    for(q=0;q<8;q++){
        nexti=m.posi+possibleJumps[q][0];
        nextj=m.posj+possibleJumps[q][1];
        if((nexti>=0)&&(nexti<N)&&(nextj>=0)&&(nextj<N)) m.choices[ch++]=q;
    }
    for(q=ch;q<8;q++) m.choices[q]=-1;
    t=(model*)calloc(N*N,sizeof(model)); //ha mindig dinamikusan foglalnank, lassabb lenne
}

/* dontesi lehetosegek szamba vetele */
int fa1(){
    unsigned q, nexti, nextj, ch=0;
    for(q=0;q<8;q++){
        nexti=m.posi+possibleJumps[q][0];
        nextj=m.posj+possibleJumps[q][1];
        if((nexti>=0)&&(nexti<N)&&(nextj>=0)&&(nextj<N)&&(m.board[nexti][nextj]==-1)) m.choices[ch++]=q;
    }
    for(q=ch;q<8;q++) m.choices[q]=-1;
    return ch;
}

/* dontesi lehetosegek rangsorolasa */
void pa2(){
    return; //nincs mi alapjan
}

/* visszaallitas */
void pa4(){
    m=t[v1];
    v2=m.copy_of_v2;
    v3=m.copy_of_v3;
}

/* mentes */
void pa6(){
    m.copy_of_v2=v2;
    m.copy_of_v3=v3;
    t[v1]=m;
}

/* ervenyre juttatas */
void pa7(){
    unsigned nexti,nextj;
    nexti=m.posi+possibleJumps[m.choices[v3]][0];
    nextj=m.posj+possibleJumps[m.choices[v3]][1];
    m.posi=nexti;
    m.posj=nextj;
    m.board[nexti][nextj]=++m.count;
}

/* megoldas kijelzese */
void pa8(){
    int i, j, k;
    for (i=0;i<N;i++){
        printf("\n"); for(k=0;k<5*N+1;k++) printf("-"); printf("\n|");
        for (j=0;j<N;j++)
            if(m.board[i][j]==-1)
                printf("    |");
            else
                printf(" %2d |",m.board[i][j]);
    }
    printf("\n"); for(k=0;k<5*N+1;k++) printf("-"); printf("\n\n");
}

int main(){
    pa0();
    v0=1;
    v1=0;
    while(v0)
        switch(v0){
            case 1:
                if(ft1()){ //ha keszen vagyunk, kiirjuk es kilepunk
                    pa8();
                    v0=0;
                }
                else
                    if(ft2()) //ha nem vagyunk keszen, de meg elerheto a megoldas...
                        if((v2=fa1())){ //...es hozhato dontes, akkor ervenyre juttatjuk
                            pa2();
                            v3=0;
                            v0=3;
                        }
                        else
                            v0=2;
                    else
                        v0=2;
                break;
            case 2: // ide akkor jutunk, ha nem tudtunk dontest hozni
                if(v1){ //ha volt korabbi dontes, akkor visszalepunk, kulonben nincs megoldas
                    v1--;
                    pa4();
                    if(v3<(v2-1)){
                        v3++;
                        v0=3;
                    }
                    else
                        v0=2;
                }
                else{
                    printf("A megadott pontok kozott nem letezik ut!\n");
                    v0=0;
                }
                break;
            case 3:
                pa6();
                pa7();
                v1++;
                v0=1;
    }
    free(t);
    return 0;
}
