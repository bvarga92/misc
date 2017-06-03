#include "Bitmap.h"
#include <fstream>
#include <cstring>

using namespace std;

bool Bitmap::load(char *filename){
	if(!ByteStream::load(filename)){
		startpos=bitsperpixel=resolution=0;
		return false;
	}
	unsigned height, width;
	memcpy(&startpos,buffer+10,4); //bitterkep relativ kezdocime a 10. bajton
	memcpy(&bitsperpixel,buffer+28,1); //szinmelyseg a 28. bajton
	memcpy(&width,buffer+18,4); //szelesseg a 18. bajton
	memcpy(&height,buffer+22,4); //magassag a 22. bajton
	resolution=width*height;
	return true;
}

void Bitmap::printData(ostream& os)const{
	os<<"Size: "<<size<<" bytes"<<endl;
	os<<"Resolution: "<<resolution<<" pixels"<<endl;
	os<<"Color depth: "<<(int)bitsperpixel<<" bits/pixel"<<endl;
	os<<"Starting address of bitmap pixel array: "<<startpos<<endl<<endl;
}

void Bitmap::negative(char* outputname)const{
	if(!buffer) return;
	ofstream output(outputname,ios::out | ios::binary);
	if(!output) return;
	unsigned char *tempbuffer=new unsigned char[size];
	for(unsigned i=0;i<startpos;i++) tempbuffer[i]=buffer[i];
	for(unsigned i=startpos;i<size;i++) tempbuffer[i]=~buffer[i];
	output.write((char*)tempbuffer,size);
	delete[] tempbuffer;
	output.close();
}
