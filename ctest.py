from decimal import *
import random
import subprocess
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# PARAMETEREK ########################################################################

numTestCases=5000 # ennyi mintat generalunk
mode=3            # veletlen (0), negativ (1), kis negativ (2), egesz kis negativ (3)
compileCode=True  # forditsunk ujra?
                  # ez maga a program
c_code=r'''
/* 50.46 fixpontos --> double konverzio */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE *fileIn, *fileOutR, *fileOutW;
    uint32_t h32, m32, l32, h32_, m32_, l32_, lines=0, i;
    double outputR, outputW;
    fileIn=fopen("input.txt","r");
    fileOutR=fopen("outputRight.txt","w");
    fileOutW=fopen("outputWrong.txt","w");
    while(!feof(fileIn)) if(fgetc(fileIn)=='\n') lines++;
    fseek(fileIn,0,SEEK_SET);
    for(i=0;i<lines;i++){
        fscanf(fileIn,"%x %x %x\n",&h32,&m32,&l32);
            if(h32&(1<<31)){
            h32_=~h32;
            m32_=~m32;
            l32_=~l32;
            if(l32_==0xFFFFFFFF){
                l32_=0;
                if(m32_==0xFFFFFFFF){
                    m32_=0;
                    h32_+=1;
                }
                else
                    m32_+=1;
            }
            else
                l32_+=1;
            outputR=-(h32_*pow(2,18)+m32_*pow(2,-14)+l32_*pow(2,-46)); //helyes 2-es komplemens kepzes
            outputW=-((~h32)*pow(2,18)+(~m32)*pow(2,-14)+(~l32)*pow(2,-46)); //itt elmarad a +1
        }
        else{
            outputR=outputW=h32*pow(2,18)+m32*pow(2,-14)+l32*pow(2,-46);
        }
        fprintf(fileOutR,"%.50f\n",outputR);
        fprintf(fileOutW,"%.50f\n",outputW);
    }
    fclose(fileIn);
    fclose(fileOutR);
    fclose(fileOutW);
    return 0;
}
'''

# TESZTESETEK GENERALASA #############################################################

powers=['-562949953421312','281474976710656','140737488355328','70368744177664','35184372088832','17592186044416',
        '8796093022208','4398046511104','2199023255552','1099511627776','549755813888','274877906944','137438953472',
        '68719476736','34359738368','17179869184','8589934592','4294967296','2147483648','1073741824','536870912',
        '268435456','134217728','67108864','33554432','16777216','8388608','4194304','2097152','1048576','524288',
        '262144','131072','65536','32768','16384','8192','4096','2048','1024','512','256','128','64','32','16','8',
        '4','2','1','0.5','0.25','0.125','0.0625','0.03125','0.015625','0.0078125','0.00390625','0.001953125',
        '0.0009765625','0.00048828125','0.000244140625','0.0001220703125','0.00006103515625','0.000030517578125',
        '0.0000152587890625','0.00000762939453125','0.000003814697265625','0.0000019073486328125','0.00000095367431640625',
        '0.000000476837158203125','0.0000002384185791015625','0.00000011920928955078125','0.000000059604644775390625',
        '0.0000000298023223876953125','0.00000001490116119384765625','0.000000007450580596923828125',
        '0.0000000037252902984619140625','0.00000000186264514923095703125','0.000000000931322574615478515625',
        '0.0000000004656612873077392578125','0.00000000023283064365386962890625','0.000000000116415321826934814453125',
        '0.0000000000582076609134674072265625','0.00000000002910383045673370361328125','0.000000000014551915228366851806640625',
        '0.0000000000072759576141834259033203125','0.00000000000363797880709171295166015625',
        '0.000000000001818989403545856475830078125','0.0000000000009094947017729282379150390625',
        '0.00000000000045474735088646411895751953125','0.000000000000227373675443232059478759765625',
        '0.0000000000001136868377216160297393798828125','0.00000000000005684341886080801486968994140625',
        '0.000000000000028421709430404007434844970703125','0.0000000000000142108547152020037174224853515625']
getcontext().prec=100
powers=[Decimal(p) for p in powers]

def testGenerator(mode):
    while True:
        if   mode==0: # veletlen ertekek a teljes tartomanyban
            numHex='0x'+''.join(random.choices('0123456789ABCDEF',k=8))+' ' \
                   '0x'+''.join(random.choices('0123456789ABCDEF',k=8))+' ' \
                   '0x'+''.join(random.choices('0123456789ABCDEF',k=8))
        elif mode==1: # veletlen negativ ertekek
            numHex='0x'+random.choice('89ABCDEF')+''.join(random.choices('0123456789ABCDEF',k=7))+' ' \
                   '0x'+''.join(random.choices('0123456789ABCDEF',k=8))+' ' \
                   '0x'+''.join(random.choices('0123456789ABCDEF',k=8))
        elif mode==2: # -256-nal nem kisebb negativ ertekek
            numHex='0xFFFFFFFF 0xFF'+''.join(random.choice('CDEF'))+ \
                   ''.join(random.choices('0123456789ABCDEF',k=2))+ \
                   ''.join(random.choices('0123456789ABCDEF',k=3))+ \
                    ' 0x'+''.join(random.choices('0123456789ABCDEF',k=8))
        elif mode==3: # egesz kis abszolut erteku negativ ertekek
            numHex='0xFFFFFFFF 0xFFFFFFFF 0xFFFFFF'+''.join(random.choices('0123456789ABCDEF',k=2))
        else:
            raise Exception('Invalid mode.')
        numBin=format(int(numHex[2:10]+numHex[13:21]+numHex[24:32],16),'0>96b')
        numVal=sum([powers[i] for i,b in enumerate(numBin) if b=='1'])
        yield numHex,numVal

print('Generating input files...')
with open('input.txt','w') as fin, open('reference.txt','w') as fref:
    myGenerator=testGenerator(mode)
    for _ in range(numTestCases):
        numHex,numVal=next(myGenerator)
        fin.write(numHex+'\n')
        fref.write(str(numVal)+'\n')
    fin.close()
    fref.close()

# C PROGRAM FORDITASA ES FUTTATASA ###################################################

if compileCode:
    print('Compiling C code...')
    with open('fmttest.c','w') as f:
        f.write(c_code)
        f.close()
    subprocess.call(['gcc','fmttest.c','-o','fmttest','-lm'])
    subprocess.call(['chmod','777','fmttest'])
print('Running C program...')
subprocess.call('./fmttest')

# KIMENET OSSZEVETESE A REFERENCIAVAL ################################################

print('Comparing outputs...')
ref=[]
errR=[]
errW=[]
with open('reference.txt','r') as fref, open('outputRight.txt','r') as foutR, open('outputWrong.txt','r') as foutW:
    for numRef,numOutR,numOutW in zip(fref,foutR,foutW):
        ref.append(Decimal(numRef))
        errR.append(Decimal(numOutR)-Decimal(numRef))
        errW.append(Decimal(numOutW)-Decimal(numRef))
    fref.close()
    foutR.close()
    foutW.close()
fig=plt.figure(figsize=[10,5])
plt.plot(np.asarray(ref,dtype='double'),np.asarray(errR,dtype='double'),'go')
plt.plot(np.asarray(ref,dtype='double'),np.asarray(errW,dtype='double'),'ro')
plt.grid()
plt.title('Absolute error with right (green) and wrong (red) conversion method')
fig.savefig('error1.png',bbox_inches='tight')
fig=plt.figure(figsize=[10,5])
plt.plot(np.asarray(ref,dtype='double'),np.asarray(errR,dtype='double')/np.asarray(ref,dtype='double'),'go')
plt.plot(np.asarray(ref,dtype='double'),np.asarray(errW,dtype='double')/np.asarray(ref,dtype='double'),'ro')
plt.grid()
plt.title('Relative error with right (green) and wrong (red) conversion method')
fig.savefig('error2.png',bbox_inches='tight')
print('Test successfully completed.')