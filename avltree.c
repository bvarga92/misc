#include <stdio.h>
#include <stdlib.h>

/* elemtipusok */
typedef struct node{
    int data;
    struct node *l, *r;
} node;
typedef struct avlNode{
    int data;
    int height; // a csomopont szintje (leghosszabb aganak elemszama)
    struct avlNode *l, *r;
} avlNode;

/* beszuras sima faba */
void insert(node** tree, int d){
    if(!(*tree)){
        node *newnode=(node*)malloc(sizeof(node));
        newnode->data=d;
        newnode->r=newnode->l=NULL;
        *tree=newnode;
    }
    else if(d<(*tree)->data)
        insert(&((*tree)->l),d);
    else if(d>(*tree)->data)
        insert(&((*tree)->r),d);
}

/* forgato segedfuggvenyek az AVL-fa kiegyensulyozasahoz */
int getHeight(avlNode* n){
    return n?(n->height):(-1);
}
void RL1(avlNode** n){
    avlNode* temp=NULL;
    temp=(*n)->l;
    (*n)->l=temp->r;
    temp->r=*n;
    (*n)->height=(getHeight((*n)->l)>getHeight((*n)->r)) ? (getHeight((*n)->l)+1) : (getHeight((*n)->r)+1);
    temp->height=(getHeight(temp->l)>getHeight(*n))      ? (getHeight(temp->l)+1) : (getHeight(*n)+1);
    *n=temp;
}
void RR1(avlNode** n){
    avlNode* temp;
    temp=(*n)->r;
    (*n)->r=temp->l;
    temp->l=*n;
    (*n)->height=(getHeight((*n)->l)>getHeight((*n)->r)) ? (getHeight((*n)->l)+1) : (getHeight((*n)->r)+1);
    temp->height=(getHeight(temp->r)>getHeight(*n))      ? (getHeight(temp->r)+1) : (getHeight(*n)+1);
    *n=temp;
}
void RL2(avlNode** n){
    RR1(&((*n)->l));
    RL1(n);
}
void RR2(avlNode** n){
    RL1(&((*n)->r));
    RR1(n);
}

/* beszuras AVL-faba */
void insertAVL(avlNode** tree, int d){
    if(!(*tree)){
        avlNode *newnode=(avlNode*)malloc(sizeof(avlNode));
        newnode->data=d;
        newnode->r=newnode->l=NULL;
        newnode->height=0;
        *tree=newnode;
    }
    else if(d<(*tree)->data){
        insertAVL(&((*tree)->l),d);
        if(getHeight((*tree)->l)-getHeight((*tree)->r)==2)
            if(d<(*tree)->l->data)
                RL1(tree);
            else
                RL2(tree);
    }
    else if(d>(*tree)->data){
        insertAVL(&((*tree)->r),d);
        if(getHeight((*tree)->r)-getHeight((*tree)->l)==2)
            if(d>(*tree)->r->data)
                RR1(tree);
            else
                RR2(tree);
    }
    (*tree)->height=(getHeight((*tree)->l)>getHeight((*tree)->r)) ? (getHeight((*tree)->l)+1) : (getHeight((*tree)->r)+1);
}

/* faelemek preorder kiiratasa */
void print(node* tree){
    if(tree){
        printf(" %2d (balra: ",tree->data);
        if(tree->l) printf("%2d jobbra: ",tree->l->data); else printf("-- jobbra: ");
        if(tree->r) printf("%2d)\n",tree->r->data); else printf("--)\n");
        print(tree->l);
        print(tree->r);
    }
}
void printAVL(avlNode* tree){
    if(tree){
        printf(" %2d (balra: ",tree->data);
        if(tree->l) printf("%2d jobbra: ",tree->l->data); else printf("-- jobbra: ");
        if(tree->r) printf("%2d)\n",tree->r->data); else printf("--)\n");
        printAVL(tree->l);
        printAVL(tree->r);
    }
}

/* memoria felszabaditasa (posztorder bejaras) */
void cleanup(node* tree){
    if(tree){
        cleanup(tree->l);
        cleanup(tree->r);
        free(tree);
    }
}
void cleanupAVL(avlNode* tree){
    if(tree){
        cleanupAVL(tree->l);
        cleanupAVL(tree->r);
        free(tree);
    }
}

int main(){
    const int testData[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    node *tree=NULL;
    avlNode *avlTree=NULL;
    unsigned i;
    for(i=0;i<20;i++){
        insert(&tree,testData[i]);
        insertAVL(&avlTree,testData[i]);
    }
    printf("Sima fa bejarasa:\n-----------------\n"); print(tree); printf("\n\n");
    printf("AVL-fa bejarasa:\n----------------\n"); printAVL(avlTree); printf("\n\n");
    cleanup(tree);
    cleanupAVL(avlTree);
    return 0;
}
