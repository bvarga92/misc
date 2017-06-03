#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <math.h>

/* a tabla merete */
#define WIDTH 70
#define HEIGHT 20

/* bit 0: van-e itt elo sejt (1) vagy nincs (0), bit1: kovetkezo allapot */
unsigned char board[WIDTH][HEIGHT];

/* veletlenszeruen elhelyezi az elo sejteket */
void initCells(){
    unsigned x, y;
    for(y=0;y<HEIGHT;y++) for(x=0;x<WIDTH;x++) board[x][y]=(rand()%2)?0x03:0x00;
}

/* megszamolja az adott hely elo szomszedait (szeleken atlapolodik) */
unsigned countNeighbors(unsigned x, unsigned y){
    unsigned left=(x>0)?(x-1):(WIDTH-1);
    unsigned right=(x<(WIDTH-1))?(x+1):0;
    unsigned below=(y>0)?(y-1):(HEIGHT-1);
    unsigned above=(y<(HEIGHT-1))?(y+1):0;
    unsigned cntr=0;
    if(board[left][below]&0x01) cntr++;
    if(board[left][y]&0x01) cntr++;
    if(board[left][above]&0x01) cntr++;
    if(board[x][below]&0x01) cntr++;
    if(board[x][above]&0x01) cntr++;
    if(board[right][below]&0x01) cntr++;
    if(board[right][y]&0x01) cntr++;
    if(board[right][above]&0x01) cntr++;
    return cntr;
}

/* frissiti a tablat */
void updateBoard(){
    unsigned x, y, neighbors;
    for(y=0;y<HEIGHT;y++){
        for(x=0;x<WIDTH;x++){
            neighbors=countNeighbors(x,y);
            if((neighbors<2)||(neighbors>3))
                board[x][y]&=0xFD; //elszigetelodes, tulnepesedes --> elpusztul
            else if(neighbors==3)
                board[x][y]|=0x02; //uj sejt szuletik
        }
    }
    for(y=0;y<HEIGHT;y++) for(x=0;x<WIDTH;x++) board[x][y]=(board[x][y]&0x02)?0x03:0x00;
}

/* kirajzolja a tablat */
void drawBoard(){
    unsigned x, y;
    system("cls"); //csak Windows!
    for(y=0;y<HEIGHT;y++){
        for(x=0;x<WIDTH;x++) printf("%c",(board[x][y]&1)?'*':' ');
        printf("\n");
    }
}

int main(){
    initCells();
    while(1){
        drawBoard();
        Sleep(30);
        updateBoard();
    }
}
