#ifndef _STEGANO_H_
#define _STEGANE_H_

	#include "Bitmap.h"

	class Stegano{
	private:
		Bitmap& BMP;
		ByteStream& TXT;
	public:
		Stegano(Bitmap& b, ByteStream& t):BMP(b),TXT(t){} //konstruktor
		void hideText()const; //elrejti a szoveget a kepben
		void recoverText()const; //visszaallitja a kepben elrejtett szoveget
	};

#endif