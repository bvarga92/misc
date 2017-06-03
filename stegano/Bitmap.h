#ifndef BITMAP_H
#define BITMAP_H

	#include "ByteStream.h"
	#include <iostream>

	class Bitmap: public ByteStream{
	private:
		unsigned startpos; //a szininformaciok tarolasanak kezdete (hanyadik bajt), jellemzoen 54
		unsigned long resolution; //a kep pixeleinek szama
		unsigned char bitsperpixel; //szinmelyseg
	public:
		Bitmap():ByteStream(){startpos=resolution=bitsperpixel=0;} //default konstruktor
		unsigned getStartPos()const{return startpos;}
		unsigned long getResolution()const{return resolution;}
		unsigned char getBPP()const{return bitsperpixel;}
		bool load(char *filename); //megnyitja a fajlt, feltolti az adattagokat
		void printData(std::ostream& os)const; //kiirja az adatokat
		void negative(char* outputname)const; //invertalja a kep szineit
	};

#endif