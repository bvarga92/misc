#include <stdio.h>

#define W 1366
#define H 768

unsigned char mandelbrot(double px, double py){
	unsigned char i=0;
	double x=px, y=py, t;
	while((i<255)&&(x*x+y*y<4.0)){
		t=x;
		x=x*x-y*y+px;
		y=2*t*y+py;
		i++;
	}
	return i;
}

int main(){
	int x, y;
	double cx=0, cy=0, zoom=0.5; //kozeppont, zoom
	unsigned char pixel;
	FILE *f;
	if(!(f=fopen("mandelbrot.ppm","wt"))) return 1;
	fprintf(f,"P6\n%i %i\n255\n",W,H);
	for(y=0;y<H;y++)
		for(x=0;x<W;x++){
			pixel=mandelbrot((2*x/(double)W-1)/zoom+cx,(2*y/(double)W-H/(double)W)/zoom+cy);
			putc(255*(pixel>>5)/7,f);
			putc(255*((pixel>>2)&7)/7,f);
			putc(255*(pixel&3)/3,f);
		}
	fclose(f);
	return 0;
}
