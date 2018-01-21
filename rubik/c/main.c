#include <stdio.h>
#include <stdlib.h>
#include "cube.h"

int main(){
	unsigned len;
	char *solution, colors[]="WWWWGGGGOOOORRRRYYYYBBBB";
	cube_t cube={2,colors};	
	printf("Eredeti kocka:\n\n");
	draw(&cube);
	move("FuLUFuRbluRdBf",&cube);
	printf("\n\nKevert kocka:\n\n");
	draw(&cube);
	len=solve2x2(&cube,&solution);
	move(solution,&cube);
	printf("\n\nMegoldas %u lepesben: %s\n\nKirakott kocka:\n\n",len,solution);
	draw(&cube);
	free(solution);
	return 0;
}
