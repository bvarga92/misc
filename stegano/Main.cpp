#include <iostream>
#include "Stegano.h"

using namespace std;

enum mode {ENCODE, DECODE};

bool checkArgs(int argc, mode& M){
	if(argc==2) {M=DECODE; return true;}
	if(argc==3) {M=ENCODE; return true;}
	cerr<<"Invalid command line arguments! Arguments should be:"<<endl;
	cerr<<"\tstegano.exe CarrierImage.bmp TextToHide.txt   (FOR ENCODING)"<<endl;
	cerr<<"\tstegano.exe CarrierImage.bmp                  (FOR DECODING)"<<endl<<endl;
	return false;
}

bool open(Bitmap& image, ByteStream& text, char* iname, char* tname){
	if(!image.load(iname)){
		cerr<<"ERROR: Failed to open "<<iname<<"!"<<endl<<endl;
		return false;
	}
	if(tname)
		if(!text.load(tname)){
			cerr<<"ERROR: Failed to open "<<tname<<"!"<<endl<<endl;
			return false;
		}
	return true;
}

void waitForKey(){
	cout<<"Press RETURN to exit..."<<endl;
	cin.clear();
	cin.ignore(1,'\n');
}

int main(int argc, char **argv){
	mode M;
	/* ellenorizzuk, hogy helyes parametereket kaptunk-e */
	if(!checkArgs(argc,M)){
		waitForKey();
		return 0;
	}
	/* megprobaljuk megnyitni a fajlokat */
	Bitmap image;
	ByteStream text;
	if(M==ENCODE)
		if(!open(image,text,argv[1],argv[2])){
			waitForKey();
			return 0;
		}
	if(M==DECODE)
		if(!open(image,text,argv[1],NULL)){
			waitForKey();
			return 0;
		}
	/* most jon a lenyeg */
	Stegano steg(image,text);
	if(M==ENCODE){
		try{
			steg.hideText();
		}
		catch(const char* errorText){
			cerr<<errorText<<endl<<endl;
			waitForKey();
			return 0;
		}
		cout<<"Successfully concealed text in the input image.\nCheck output.bmp in the program folder."<<endl<<endl;
	}
	if(M==DECODE){
		try{
			steg.recoverText();
		}
		catch(const char* errorText){
			cerr<<errorText<<endl<<endl;
			waitForKey();
			return 0;
		}
		cout<<"Successfully recovered text from the image.\nCheck output.txt in the program folder."<<endl<<endl;
	}
	waitForKey();
	return 0;
}
