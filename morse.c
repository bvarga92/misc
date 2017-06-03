#include <stdio.h>
#include <stdlib.h>

/* node struktura */
typedef struct f{
    char c;
    struct f *dot, *dash;
} node;

/* a dekodolo tomb a felepitendo fa preorder bejarasanak megfelelo sorrendben tartalmazza a karaktereket */
char t[]="* E I S H.V.U F.*.A R L.*.W P.J.T N D B.X.K C.Y.M G Z.Q.O."; //pont jelzi a levelelemeket

/* a dekodolo fa felepitese */
void initTree(node** p){
    static unsigned n=0;
    char temp[2];
    temp[0]=t[2*n]; temp[1]=t[2*n+1];
    n++;
    *p=(node*)malloc(sizeof(node));
    (*p)->c=temp[0];
    if(temp[1]!='.') initTree(&((*p)->dot));
    if(temp[1]!='.') initTree(&((*p)->dash));
}

/* egy karakter dekodolasa */
char decode(node* root, char *code, int len){
    unsigned i=0;
    node* p=root;
    while(i<len){
        if(code[i]=='.') p=p->dot;
        if(code[i]=='-') p=p->dash;
        i++;
    }
    return p->c;
}

int main(){
    node* root;
    char code[250], temp[4];
    unsigned i=0, len;
    initTree(&root);
    printf("Kulon karakterek kodjai koze szokoz kell!\nRovid: .  Hosszu: -\n\nKerem a Morse-kodot: ");
    gets(code);
    printf("\nVisszafejtve: ");
    while(code[i]!='\0'){
        len=0;
        while((code[i]!=' ')&&(code[i]!='\0')){
            temp[len]=code[i];
            i++;
            len++;
        }
        printf("%c",decode(root,temp,len));
        if(code[i]!='\0') i++;
    }
    printf("\n\n");
    return 0;
}
