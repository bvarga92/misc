#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define N 5 //tabla merete


void initMaze(int maze[N][N]){
    int i, j;
    srand(time(0));
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            maze[i][j] = rand()%2;
}


void printMaze(int maze[N][N]){
    int i, j;
    printf("|");
    for(j=0; j<N*4-1; j++) printf("-");
    printf("|\n");
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("| %c ", maze[i][j]==1 ? '1' : ' ');
        }
        printf("|\n|");
        for(j=0; j<N*4-1; j++) printf("-");
        printf("|\n");
    }
    
}


int solveMaze(int maze[N][N], int solution[N][N], int row, int col){
    if(row == N-1 && maze[row][col] == 1){ //elertuk az utolso sort, keszen vagyunk
        solution[row][col] = 1;
        return 1;
    }
    if(row >= 0 && row < N && col >= 0 && col < N && maze[row][col] == 1 && solution[row][col] != 1){
        solution[row][col] = 1;
        if(solveMaze(maze, solution, row+1, col)) return 1; //megprobaljuk lefele
        if(solveMaze(maze, solution, row, col-1)) return 1; //megprobaljuk balra
        if(solveMaze(maze, solution, row, col+1)) return 1; //megprobaljuk jobbra        
        solution[row][col] = 0; //egyik lepes sem vezetett megoldasra
    }
    return 0; 
}


int main(){
    int maze[N][N], solution[N][N], i, j, startCol, solutionFound=0;
    initMaze(maze);
    for(startCol=0; startCol<N; startCol++){
        for(i=0; i<N; i++) for(j=0; j<N; j++) solution[i][j] = 0;
        if(maze[0][startCol] == 1 && solveMaze(maze, solution, 0, startCol)){
            solutionFound = 1;
            break;
        }
    }
    printf("Labirintus:\n\n");
    printMaze(maze);
    if(solutionFound){
        printf("\nEgy lehetseges megoldas:\n\n");
        printMaze(solution);
    }
    else{
        printf("\nNincs megoldas.\n\n");
    }
    return 0;
}