#include <stdio.h>
#include <stdlib.h>

/* linearis kereses
   talalat eseten az elem cimet adja vissza
   eredmenytelen kereses eseten nullpointert */
int* searchLin(int* array, int n, int key){
    while(n)
        if(array[0]==key)
            return array;
        else
            array++, n--;
    return NULL;
}

/* linearis kereses rendezett tombre
   ha van talalat, akkor az elem indexet adja vissza
   ha nincs, akkor azt, hogy hol lenne a helye */
int searchLinSorted(int* array, int n, int key){
    int i;
    for(i=0;(i<n)&&(array[i]<key);i++) ;
    return i;
}

/* logaritmikus (binaris) kereses
   ha van talalat, akkor az elem indexet adja vissza
   ha nincs, akkor azt, hogy hol lenne a helye */
int searchLog(int* array, int n, int key){
    int i=0, j;
    if(array[--n]<key) return n+1;
    while(i<n){
        if(array[j=(i+n)/2]==key) return j;
        if(array[j]>key)
            n=j-1;
        else
            i=j+1;
    }
}

/* buborekrendezes */
void sortBubble(int *array, int n){
    int i, j, temp;
    for(i=n-1;i;i--)
        for(j=0;j<i;j++)
            if(array[j]>array[j+1]){
                temp=array[j+1];
                array[j+1]=array[j];
                array[j]=temp;
            }
}

/* javitott buborekrendezes */
void sortBubbleSmart(int *array, int n){
    int i, j, k, temp;
    for(i=n-1;i>0;i=k)
        for(j=0,k=-1;j<i;j++)
            if(array[j]>array[j+1]){
                temp=array[j+1];
                array[j+1]=array[j];
                array[k=j]=temp;
            }
}

/* shell algoritmus */
void sortShell(int *array, int n){
    int i, j, k, l, m, temp;
    for(m=1;2*m<n;m<<=1) ;
    for(m-=1;m;m>>=1)
        for(l=0;l<m;l++)
            for(i=n-1-(n-1-l)%m;i>l;i=k)
                for(j=l,k=-m;j<i;j+=m)
                    if(array[j]>array[j+m]){
                        k=j;
                        temp=array[j+m];
                        array[j+m]=array[j];
                        array[j]=temp;
                    }
}

/* rendezes kozvetlen kivalasztassal */
void sortSelection(int *array, int n){
    int i, j, min, s, x;
    for(i=0;i<n-1;){
        min=s=array[x=i];
        for(j=i+1;j<n;j++) if(array[j]<min) min=array[x=j];
        array[i++]=min, array[x]=s;
    }
}

/* rendezes kozvetlen beszurassal */
void sortInsertion(int *array, int n){
    int i, j, k, s, a, f;
    for(i=1;i<n;i++){
        s=array[i];
        for(a=0,f=i; a<f; array[k=(a+f)/2]<s?a=k+1:(f=k)) ; //a beszurando elem helye log. keresessel
        for(j=i;j>a;j--) array[j]=array[j-1];
        array[a]=s;
    }
}

/* kupacrendezes */
void sink(int *array, int i, int bttm){ //az atadott tomb i indexu elemet a helyere sullyeszti
    int done=0, max, temp;
    while((i*2<=bttm)&&(!done)){
        max=((i*2==bttm)||(array[i*2]>array[i*2+1]))?(i*2):(i*2+1);
        if(array[i]<array[max]){
            temp=array[i];
            array[i]=array[max];
            array[max]=temp;
            i=max;
        }
        else
            done=1;
    }
}
void sortHeap(int *array, int n){
    int i, temp;
    for(i=n/2;i>=0;i--) sink(array,i,n-1);
    for(i=n-1;i>=1;i--){
        temp=array[0];
        array[0]=array[i];
        array[i]=temp;
        sink(array,0,i-1);
    }
}

/* gyorsrendezes */
void quick_rec(int *array, int start, int end) {
    int temp;
    int i=start+1, j=end, k=array[start];
    if(start>=end) return;
    while(i<j){
        while((i<j)&&(array[j]>=k)) j--;
        while((i<j)&&(array[i]<=k)) i++;
        if(i<j){
            temp=array[j];
            array[j]=array[i];
            array[i]=temp;
        }
    }
    if(array[start]>array[i]) {
        temp=array[start];
        array[start]=array[i];
        array[i]=temp;
        quick_rec(array,start,i-1);
        quick_rec(array,i+1,end);
    }
    else
        quick_rec(array,start+1,end);
}
void sortQuick(int *array, int n){
    quick_rec(array,0,n-1);
}

int main(){
    void (*sortFunction)(int*, int)=sortQuick; //melyik rendezofuggvenyt szeretnenk kiprobalni
    int unsorted[13]={2,6,19,-8,1,12,7,42,13,27,5,9,0};
    int sorted[13]={-8,0,1,2,5,6,7,9,12,13,19,27,42};
    int bigarray[1024];
    int i, j;
    printf("Linearis kereses rendezetlen tombre: %d\n\n",*searchLin(unsorted,13,9));
    printf("Linearis kereses rendezett tombre: %d\n\n",searchLinSorted(sorted,13,12));
    printf("Logaritmikus kereses (csak rendezett tombre): %d\n\n",searchLog(sorted,13,7));
    printf("Rendezes:\n");
    srand(123);
    for(i=0;i<1024;i++) bigarray[i]=rand();
    sortFunction(bigarray,1024);
    for(i=0;i<1024;i+=8){
        for(j=i;j<i+8;j++) printf("%5d | ",bigarray[j]);
        printf("\n");
    }
    printf("\n\n");
    return 0;
}
