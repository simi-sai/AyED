// metodo de ordenamiento Quick Sort y Merge Sort
// comparando m�todos
// N=5000 elementos
//        Insercion  Seleccion  Burbuja  Shell    QS     MS   Heap
//Compara    6M       12M        12M       96K   53K    55K   107K
//Movimie    6M       50K        18M      140K   46K   123K    72K

#include <cstdlib>
#include <iostream>
#define MAX 5000
 
using namespace std;

void ordenaQS(int v[], int primero, int ultimo);
int ordenaMS(int a[], int low, int high);
int merge(int a[], int low, int high, int mid);
void impre(int v[], int n);
int cc,cm;

int main(int argc, char *argv[])
{   //int A[10]={30,45,130,70,100,150,30,140,18,110};
    //int A[10]={30,45,130,170,200,15,30,40,81,110};
    int A[MAX];
    for(int i=0;i<MAX;i++){
                    A[i]=int(rand());
 }
    cc=cm=0;
    ordenaQS(A,0,MAX-1);
    //ordenaMS(A,0,MAX);
    cout<<"\n -----------------------------";
    //impre(A,MAX);
    cout<<"comparaciones= "<<cc<<" movimientos= "<<cm<<endl;
    cout<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

void ordenaQS(int v[], int primero, int ultimo)
{ int i,j,k,pivot,aux;
      if(ultimo>primero){
             pivot=v[ultimo];cm++;
             //printf("\n -> %d  %d <-%4i",primero,ultimo,pivot);
             i=primero-1; j=ultimo;      
             for(;;){
                     while(v[++i]<pivot)cc++;
                     while(v[ --j ] >pivot)cc++;
                     if(i>=j)break;
                     aux=v[i];v[i]=v[j];v[j]=aux; cm=cm+3;     
             }// fin for
             aux=v[i];v[i]=v[ultimo];v[ultimo]=aux;cm=cm+3;
             //for(k=0;k<10;k++)printf("\n a[%d]=%d",k,v[k]);
             //printf("\n ------------------------------------");
             ordenaQS(v,primero,i-1);
             ordenaQS(v,i+1,ultimo);
             //printf("\nRETORNO -> %d  %d <-",primero,ultimo);
      } //fin if 
}// fin ordena

int ordenaMS(int a[], int low, int high)
{   int mid;
    if(low<high){
                 mid=(low+high)/2;
                 //cout<<"\n llamo a ordenaMS(1) con low= "<<low<<" mid= "<<mid<<endl;
                 ordenaMS(a,low,mid);
                 //cout<<"\n llamo a ordenaMS(2) con mid+1= "<<mid+1<<" high= "<<high<<endl;
                 ordenaMS(a,mid+1,high);
                 merge(a,low,high,mid);
    }
    return(0);
}

int merge(int a[], int low, int high, int mid)
{   int i, j, k, c[MAX];
    //cout<<"\n Estoy en merge() con low= "<<low<<" high= "<<high<<" mid= "<<mid<<endl;
    //system("PAUSE");
    i=low; j=mid+1; k=low;
    
    while((i<=mid)&&(j<=high)){
         cc++;cm++;                      
         if(a[i]<a[j]){
                
                c[k]=a[i];
                k++; i++;
         }
         else{  
                c[k]=a[j];
                k++; j++;
         }
    }
    while(i<=mid){ c[k]=a[i]; k++; i++; cm++; }
    while(j<=high){c[k]=a[j]; k++; j++; cm++;}
    for(i=low;i<k;i++) {a[i]=c[i];cm++;}
    //impre(a,MAX);
} 

void impre(int v[], int n)
{  
     for(int i=0;i<n;i++) cout<<endl<<v[i];
}