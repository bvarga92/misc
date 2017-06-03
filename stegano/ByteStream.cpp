#include "ByteStream.h"
#include <fstream>
#include <assert.h>

using namespace std;

bool ByteStream::load(char *filename){
	ifstream file(filename,ios::in | ios::binary);
	if(!file){
		size=0;
		buffer=NULL;
		return false;
	}
	file.seekg(0,ios::end);
	size=file.tellg();
	delete[] buffer;
	if(size){
		buffer=new unsigned char[size];
		file.seekg(0,ios::beg);
		file.read((char*)buffer,size);
	}
	else
		buffer=NULL;
	file.close();
	return true;
}

bool ByteStream::writeBuffer(char* outputname)const{
	ofstream output(outputname,ios::out | ios::binary);
	if(!output) return false;
	if(buffer) output.write((char*)buffer,size);
	output.close();
	return true;
}

void ByteStream::createBuffer(unsigned size){
	this->size=size;
	delete[] buffer;
	if(size){
		buffer=new unsigned char[size];
		for(unsigned i=0;i<size;i++) buffer[i]=0;
	}
	else
		buffer=NULL;
}

unsigned char& ByteStream::operator[](unsigned index){
	assert(index<size);
	return buffer[index];
}
