#ifndef _BYTESTREAM_H_
#define _BYTESTREAM_H_

	class ByteStream{
	protected:
		unsigned char *buffer; //ide olvassuk be a fajlt, itt dolgozunk
		unsigned size; //az allomany merete bajtokban
	public:
		ByteStream(){size=0; buffer=0;}
		virtual ~ByteStream(){delete[] buffer;}
		virtual bool load(char *filename); //megnyitja a fajlt, feltolti a buffert
		bool writeBuffer(char* outputname)const; //a buffer tartalmat kiirja egy fajlba
		void createBuffer(unsigned size); //lefoglalja a megadott meretu buffert es kinullazza
		void clearBuffer(){delete[] buffer; buffer=0;}
		unsigned getSize()const{return size;}
		unsigned char& operator[](unsigned index); //a buffer bajtjaira lehet hivatkozni
	};

#endif
