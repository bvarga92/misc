#include <stdio.h>
#include <math.h>

#define N 8 //a sakktabla merete

unsigned q[N]; //az i-edik elem megadja, hogy az i-edik sor hanyadik oszlopaban van a vezer

/* a sakktabla kirajzolasa */
void printBoard(){
    unsigned i, j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++) if(q[i]==j) printf("Q "); else printf(". ");
        printf("\n");
    }
}

/* ellenorzi, hogy az adott mezore szabad-e meg vezert tenni */
unsigned check(unsigned row, unsigned col) {
    unsigned i;
    for(i=0;i<row;i++) if((abs(i-row)==abs(q[i]-col))||(i==row)||(q[i]==col)) return 0;
    return 1;
}

/* rekurziv backtrack algoritmus */
unsigned backtrack(unsigned row) {
    unsigned col=0, success=0;
    if(row==N) return 1;
    while((col<N)&&(!success))
        if(!check(row,col))
            col++;
        else{
            q[row]=col;
            success=backtrack(row+1);
            if(!success) col++;
        }
    return success;
}

int main(){
    backtrack(0);
    printBoard();
    return 0;
}
