#include "Stegano.h"

void Stegano::hideText()const{
	const unsigned imsize=BMP.getSize();
	const unsigned txsize=TXT.getSize();
	unsigned pos=BMP.getStartPos();
	if((!imsize)||(!txsize)) throw "Unknown error encountered. (Empty input file?)";
	if(txsize>((BMP.getSize()-pos-32)/8)) throw "The image is not big enough to hide the text.";
	/* a 6.-9. bajtok szabadok, ide beijuk a STEG szot, ez alapjan tudjuk
	visszafejteskor detektalni, hogy a kep rejtett uzenetet tartalmaz */
	BMP[6]='S'; BMP[7]='T'; BMP[8]='E'; BMP[9]='G';	
	/* az elso 32 bajtra beirjuk az elrejtendo szoveg hosszat */
	for(int i=31;i>=0;i--,pos++) BMP[pos]=(BMP[pos]&0xFE)|((txsize>>i)&1);
	/* utana beirjuk az uzenetet */
	pos=BMP.getStartPos()+32;
	for(unsigned i=0;i<txsize;i++) //bajtok
		for(int j=7;j>=0;j--,pos++) //bitek
			BMP[pos]=(BMP[pos]&0xFE)|((TXT[i]>>j)&1);
	if(!BMP.writeBuffer("output.bmp")) throw "ERROR: Failed to create output.bmp!";
}

void Stegano::recoverText()const{
	if(!BMP.getSize()) throw "Unknown error encountered. (Empty input file?)";
	if((BMP[6]!='S')||(BMP[7]!='T')||(BMP[8]!='E')||(BMP[9]!='G')) throw "There is no hidden text in this image.";
	unsigned pos=BMP.getStartPos();
	/* eloszor kiolvassuk a meretet */
	unsigned length=0;
	for(unsigned i=0;i<32;i++) length=(length<<1) | (BMP[pos+i]&1);
	TXT.createBuffer(length);
	/* kiolvassuk a rejtett uzenetet */
	pos=BMP.getStartPos()+32;
	for(unsigned b=0;b<length;b++)
		for(unsigned i=0;i<8;i++,pos++)
		TXT[b]=((TXT[b]<<1) | (BMP[pos]&1));
	if(!TXT.writeBuffer("output.txt")) throw "ERROR: Failed to create output.txt!";
}
