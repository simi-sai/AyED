#include <cstdlib>
#include <iostream>

using namespace std;
//void swap(int,int);
void swap(int *a, int *b);
//void swap(int &a, int &b);
int main(int argc, char *argv[])
{   int x,y;
    int *px,*py;
    x=55; y=-22;
    /*cout<<"\n x="<<x;
    cout<<"\n y="<<y;
    cout<<"\n tamanio entero= "<<sizeof(int);
    px=&x; py=&y;
    cout<<"\n px="<<px;
    cout<<"\n py="<<py;
    cout<<"\n *px="<<*px;
    cout<<"\n *py="<<*py;
    *px=7; cout<<"\n *px="<<*px<<"  x="<<x;
    
    py=px; cout<<"\n *py="<<*py<<"  y="<<y;*/
    
    cout<<endl<<"----------------------";
    cout<<"\n x="<<x<<"  y="<<y;
    swap(x,y);
    cout<<"\n x="<<x<<"  y="<<y;
     cout<<endl<<"----------------------";
    /*
     int v[5]={23,1,-8,14,7};
     px=&v[0];   py=v;       //equivale a decir lo mismo
     cout<<"\n *px="<<*px<<"  *py="<<*py;
     cout<<"\n  px="<<px<<"  py="<<py;
    /*
     for(int i=0;i<5;i++){
         cout<<endl<<px[i]<<"  "<<*(px+i)
             <<"  "<<*(v+i)<<"  "<<*py++;
     }
     cout<<endl<<"px= "<<px;
     cout<<endl<<"v= "<<v;
     cout<<endl<<"py= "<<py;
     */
    
         
    cout<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}


void swap(int a, int b)
{ int c;
  cout<<"\n a="<<a<<"  b="<<b;
  c=a; a=b; b=c;
  cout<<"\n a="<<a<<"  b="<<b;   
     
}
void swap(int *a, int *b)
{ int c;
  cout<<"\n a="<<*a<<"  b="<<*b;
  c=*a; *a=*b; *b=c;
  cout<<"\n a="<<*a<<"  b="<<*b; 
  cout << "funciona"<< endl;  
     
}

void swap(int &a, int &b)
{int c;
  cout<<"\n a="<<a<<"  b="<<b;
  c=a; a=b; b=c;
  cout<<"\n a="<<a<<"  b="<<b;   
}

  
