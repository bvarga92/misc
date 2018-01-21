#include <stdio.h>
#include <stdlib.h>
#include "cube.h"

#define L 20

int main(){
	unsigned len;
	char colors[]="WWWWGGGGOOOORRRRYYYYBBBB", *solution, scrmbl[L+1];
	cube_t cube={2,colors};

	printf("Eredeti kocka:\n\n");
	draw(&cube);

	randomScramble(scrmbl,L);
	move(scrmbl,&cube);
	printf("\n\nKeveres %u lepesben: %s\nKevert kocka:\n\n",L,scrmbl);
	draw(&cube);

	len=solve2x2(&cube,&solution);
	move(solution,&cube);
	printf("\n\nMegoldas %u lepesben: %s\nKirakott kocka:\n\n",len,solution);
	draw(&cube);

	free(solution);
	return 0;
}
