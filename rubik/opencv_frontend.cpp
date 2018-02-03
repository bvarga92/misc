#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
extern "C"{
	#include "cube.h"
}

using namespace cv;
using namespace std;

VideoCapture vid;
char colors[]="......................................................";

char colorToChar(int r, int g, int b, int h, int s, int v){
	if(h>=0 && h<=50 && s>=60 && s<=255 && v>=60 && v<=255)
		return 'Y';
	if(h>=75 && h<=130 && s>=35 && s<=255 && v>=0 && v<=255 && r<150)
		return (g>b)?'G':'B';
	if(h>=140 && h<=255 && s>=0 && s<=255 && v>=50 && v<=255){
		double dO2=(253.48-r)*(253.48-r)+(64.98-g)*(64.98-g)+(108.55-b)*(108.55-b);
		double dR2=(197.09-r)*(197.09-r)+(63.04-g)*(63.04-g)+(95.20-b)*(95.20-b);
		return (dO2<dR2 && g>55)?'O':'R';
	}
	return 'W';
}

void getFace(VideoCapture vid, const char *title, char *face){
	namedWindow(title,WINDOW_AUTOSIZE);
	moveWindow(title,550,200);
	Mat m1, m2;
	while(waitKey(10)!=13){ //enter: fenykepez
		vid>>m1;
		flip(m1,m2,1);		
		resize(m2,m2,Size(400,300));
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				rectangle(m2,Point(110+i*80,60+j*80),Point(130+i*80,80+j*80),Scalar(0,0,0),1,8);
		imshow(title,m2);
	}
	destroyWindow(title);
	bilateralFilter(m2,m1,9,75,75);
	cvtColor(m1,m2,CV_BGR2HSV);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			int r=0, g=0, b=0, h=0, s=0, v=0;
			int x=110+j*80, y=60+i*80;
			for(int k=1;k<20;k++){
				for(int l=1;l<20;l++){
					Vec3b vec;
					vec=m2.at<Vec3b>(y+l,x+k);
					h+=vec(0);
					s+=vec(1);
					v+=vec(2);
					vec=m1.at<Vec3b>(y+l,x+k);
					r+=vec(2);
					g+=vec(1);
					b+=vec(0);
				}
			}
			h=round(h/361.0);
			s=round(s/361.0);
			v=round(v/361.0);
			r=round(r/361.0);
			g=round(g/361.0);
			b=round(b/361.0);
			face[3*i+(2-j)]=colorToChar(r,g,b,h,s,v);
			//cout<<r<<" "<<g<<" "<<b<<endl;
		}
	}
}

Scalar charToBGR(char c){
	Scalar color;
	switch(c){
		case 'W': color=Scalar(255,255,255); break;
		case 'G': color=Scalar(0,255,0);     break;
		case 'O': color=Scalar(0,128,255);   break;
		case 'R': color=Scalar(0,0,255);     break;
		case 'Y': color=Scalar(0,255,255);   break;
		case 'B': color=Scalar(255,0,0);     break;
		default:  color=Scalar(120,120,120); break;
	}
	return color;
}

void drawCube(const char *colors){
	Mat cube=Mat::zeros(600,450,CV_8UC3);
	for(int i=0;i<9;i++){
		rectangle(cube,Point(150+50*(i%3),50*(i/3)),Point(200+50*(i%3),50+50*(i/3)),charToBGR(colors[i]),-1,8);
		rectangle(cube,Point(150+50*(i%3),50*(i/3)),Point(200+50*(i%3),50+50*(i/3)),Scalar(0,0,0),1,8);
		rectangle(cube,Point(150+50*(i%3),150+50*(i/3)),Point(200+50*(i%3),200+50*(i/3)),charToBGR(colors[9+i]),-1,8);
		rectangle(cube,Point(150+50*(i%3),150+50*(i/3)),Point(200+50*(i%3),200+50*(i/3)),Scalar(0,0,0),1,8);
		rectangle(cube,Point(50*(i%3),150+50*(i/3)),Point(50+50*(i%3),200+50*(i/3)),charToBGR(colors[18+i]),-1,8);
		rectangle(cube,Point(50*(i%3),150+50*(i/3)),Point(50+50*(i%3),200+50*(i/3)),Scalar(0,0,0),1,8);
		rectangle(cube,Point(300+50*(i%3),150+50*(i/3)),Point(350+50*(i%3),200+50*(i/3)),charToBGR(colors[27+i]),-1,8);
		rectangle(cube,Point(300+50*(i%3),150+50*(i/3)),Point(350+50*(i%3),200+50*(i/3)),Scalar(0,0,0),1,8);
		rectangle(cube,Point(150+50*(i%3),300+50*(i/3)),Point(200+50*(i%3),350+50*(i/3)),charToBGR(colors[36+i]),-1,8);
		rectangle(cube,Point(150+50*(i%3),300+50*(i/3)),Point(200+50*(i%3),350+50*(i/3)),Scalar(0,0,0),1,8);
		rectangle(cube,Point(150+50*(i%3),450+50*(i/3)),Point(200+50*(i%3),500+50*(i/3)),charToBGR(colors[45+i]),-1,8);
		rectangle(cube,Point(150+50*(i%3),450+50*(i/3)),Point(200+50*(i%3),500+50*(i/3)),Scalar(0,0,0),1,8);
	}
	imshow("Cube",cube);
}

void mouseCallback(int evnt, int x, int y, int flags, void *userdata){
	if(evnt!=CV_EVENT_LBUTTONDOWN) return;
	if(x>150 && x<300 && y>0 && y<150)
		getFace(vid,"Top",colors);
	else if(x>0 && x<150 && y>150 && y<300)
		getFace(vid,"Left",colors+18);
	else if(x>150 && x<300 && y>150 && y<300)
		getFace(vid,"Front",colors+9);
	else if(x>300 && x<450 && y>150 && y<300)
		getFace(vid,"Right",colors+27);
	else if(x>150 && x<300 && y>300 && y<450)
		getFace(vid,"Bottom",colors+36);
	else if(x>150 && x<300 && y>450 && y<600)
		getFace(vid,"Back",colors+45);
	drawCube(colors);
}

int main(){
	vid=VideoCapture(0);
	if(!vid.isOpened()){
		cout<<"Unable to connect to camera."<<endl;
		return 1;
	}
	namedWindow("Cube");
	moveWindow("Cube",0,100);
	setMouseCallback("Cube",mouseCallback,colors);
	drawCube(colors);
	cube_t cube={3,colors};
	char *solution=nullptr;
	while(true){
		int key=waitKey(0);
		if(key==27)  //esc: kilep
			break;
		if(key==115){ //s: megold (TODO: sanity check)
			unsigned len=solve3x3(&cube,&solution);
			string str;
			str="Solution in ";+"a";
			str+=to_string(len);
			str+=" steps";
			MessageBoxA(nullptr,solution,str.c_str(),MB_OK);
		}
	}
	free(solution);
	return 0;
}
