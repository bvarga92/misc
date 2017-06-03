#include <stdio.h>

/* sakktabla merete */
#define N 8
/* kiindulo mezo koordinatai */
#define STARTI 5
#define STARTJ 5
/* ide szeretnenk megerkezni */
#define DESTI 0
#define DESTJ 7

const int possibleJumps[8][8]={{1,2},{2,1},{-2,1},{-1,2},{-2,-1},{-1,-2},{1,-2},{2,-1}}; //egy huszar lehetseges lepesei

int solve(unsigned posi, unsigned posj, int board[N][N], unsigned count){
    unsigned q, nexti, nextj;
    if((posi==DESTI)&&(posj==DESTJ)) return 1; //keszen vagyunk, leall a rekurzio
    for(q=0;q<8;q++){
        nexti=posi+possibleJumps[q][0];
        nextj=posj+possibleJumps[q][1];
        /* ha ezzel a lepessel nem esunk le a sakktablarol, es meg nem jartunk ebben a mezoben, akkor vegrehajtjuk */
        if((nexti>=0)&&(nexti<N)&&(nextj>=0)&&(nextj<N)&&(board[nexti][nextj]==-1)){
            board[nexti][nextj]=count;
            if(solve(nexti,nextj,board,count+1)) //es rekurzivan megprobaljuk megoldani a maradekot
                return 1;
            else
                board[nexti][nextj]=-1; //ha nem sikerul, visszalepunk
        }
    }
    return 0;
}

/* N<=10 eseten mukodik szepen, utana kicsit szetcsuszik a haromjegyu szamok miatt */
void printBoard(int board[N][N]){
    int i, j, k;
    for(i=0;i<N;i++){
        printf("\n"); for(k=0;k<5*N+1;k++) printf("-"); printf("\n|");
        for (j=0;j<N;j++)
            if(board[i][j]==-1)
                printf("    |");
            else
                printf(" %2d |",board[i][j]);
    }
    printf("\n"); for(k=0;k<5*N+1;k++) printf("-"); printf("\n\n");
}

int main(){
    int board[N][N];
    unsigned i, j;
    for(i=0;i<N;i++) for(j=0;j<N;j++) board[i][j]=-1;
    board[STARTI][STARTJ]=0;
    if(solve(STARTI,STARTJ,board,1))
        printBoard(board);
    else
        printf("A megadott pontok kozott nem letezik ut!");
    return 0;
}
