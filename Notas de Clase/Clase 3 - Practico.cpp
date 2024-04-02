//Recursion

#include <cstdlib>
#include <iostream>

using namespace std;

void impre(int v[],int n);
int suma(int v[], int n);
int mayor(int v[], int n);
int multi(int a, int b);

int main(int argc, char *argv[])
{   
    int v[6]={17,15,-8,30,5,-2};
    
	cout<<"impre vector"<<endl; impre(v,5);
    cout << "suma vec= " << suma(v,5) << endl;
    cout<<"impre vector"<<endl; impre(v,5); 
    cout << "el mayor = " << mayor(v,5) << endl;
    cout << "multiplicacion de 8x7= " << multi(8,7) << endl;
   
    return 0;
}

void impre(int v[],int n)
{   if(n==0)cout<<v[n]<<endl;
    else{ 
          //cout<<"estoy yendo";
          //cout<<v[n]<<endl;
          impre(v,n-1);
          //cout<<"estoy retornando"<<endl;
          cout<<v[n]<<endl;
          
          
    } 
}

int suma(int v[], int n)
{
   if (n == 0)
   {
       return v[n];
   } else {
       return v[n] + suma(v,n-1);
   }
}

int mayor(int v[], int n)
{
    if(n == 0)
    {
        return v[n];
    } else {
        int aux = mayor(v,n-1);
        if(v[n] > aux)
        {
            return v[n];
        } else {
            return aux;
        }
    }
}

int multi(int a, int b)
{
    if (b == 0 || a == 0)
    {
        return 0;
    } else {
        return a + multi(a,b-1);
    }
}