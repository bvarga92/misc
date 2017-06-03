#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* faelem tipus */
typedef struct t{
    unsigned f; //gyakorisagok osszege
    char c; //tarolt karakter, ha levelelem
    struct t *left, *right;
} treenode;

/* sor tipus */
typedef struct q{
    treenode* node;
    struct q* next;
} queue;

unsigned frq[256]; //gyakorisagok vektora, karakterkoddal indexelve
queue* PQ; //prioritasos sor
unsigned n=0; //hany elem van a sorban

/* feltoltjuk a gyakorisagvektort */
void count(char* str){
    unsigned i;
    for(i=0;i<256;i++) frq[i]=0;
    i=0;
    while(str[i]) frq[str[i++]]++;
}

/* uj elem beszurasa a sorba, a legritkabb karakter a legmagasabb prioritasu */
void insert(treenode* newnode){
    queue *spot=PQ, *temp;
    temp=(queue*)malloc(sizeof(queue));
    temp->node=newnode;
    while((spot->next)&&(spot->next->node->f<=newnode->f)) spot=spot->next;
    temp->next=spot->next;
    spot->next=temp;
}

/* sor elso ket elemet osszevonjuk, az eredmenyt visszatesszuk a sorba */
void merge(){
    queue *temp1=PQ->next, *temp2=PQ->next->next;
    treenode* newnode;
    newnode=(treenode*)malloc(sizeof(treenode));
    PQ->next=PQ->next->next->next;
    newnode->f=temp1->node->f+temp2->node->f;
    newnode->c=0;
    if(temp1->node->f<temp2->node->f){
        newnode->left=temp1->node;
        newnode->right=temp2->node;
    }
    else{
        newnode->left=temp2->node;
        newnode->right=temp1->node;
    }
    insert(newnode);
}

/* a vektorbol felepitjuk a fat */
void buildtree(){
    unsigned i;
    treenode* newnode;
    for(i=0;i<256;i++) if(frq[i]){ //letrehozzuk a levelelemeket, es betesszuk a sorba
        newnode=(treenode*)malloc(sizeof(treenode));
        newnode->c=i;
        newnode->f=frq[i];
        newnode->left=newnode->right=NULL;
        insert(newnode);
        n++;
    }
    for(;n>1;n--) merge(); //amig egynel tobb elem van a sorban, kiveszunk kettot, es osszevonjuk
}

/* a kesz fa posztorder bejarasa alapjan meghatarozzuk a karakterek Huffman-kodjait */
void encode(treenode* r,char *str){
    char temp[2]="0";
    if(r->left){
        strcat(str,temp);
        encode(r->left,str);
        str[strlen(str)-1]=0;
    }
    if(r->right){
        temp[0]='1';
        strcat(str,temp);
        encode(r->right,str);
        str[strlen(str)-1]=0;
    }
    else
        printf("%c: %s\n",r->c,str);
}

int main(){
    char input[]="anyahajokabinajtonyitogato"; //ennek a karaktereit kodoljuk
    char str[40]="";
    PQ=(queue*)malloc(sizeof(queue));
    PQ->next=NULL;
    count(input);
    buildtree();
    encode(PQ->next->node,str);
    return 0;
}
