//  Pila con Lista.cpp  
//

#include <cstdlib>
#include <iostream>
#include <sstream>
#define MAX 100 
using namespace std;

template <class T> class Pila{   //: public Lista<T> está heredando todo lo publico de
      private:
         T d[MAX];
         int p;
      public:
             Pila(){ p = -1; };
             void apilar(T x){ d[++p] = x; };
             T tope(void){ return d[p]; };
             void desapilar(void){ p--; };
             bool pilavacia(){ return p <= -1; };
};                  


int main()
{
    Pila<string> *p= new Pila<string>();
  p->apilar("10");  p->apilar("11");
  p->apilar("12");  p->apilar("13");
  if (!p->pilavacia()) cout<<p->tope()<<endl;
  if (!p->pilavacia())p->desapilar();
  if (!p->pilavacia())cout<<p->tope()<<endl;
  if (!p->pilavacia())p->desapilar();
  if (!p->pilavacia())cout<<p->tope()<<endl;
  
// ingresar una cadena que contendra ([{ y )]}
// el programa debera determinar si el "balance" de los ([{ es correcto
// errores posibles
// hay mas ((( que )) o [[[ que ] o { que }}}
// que no se corresponda un cerrado con el ultimo abierto {  ]

/*
  string cadena;
  cout<<endl<<"Ingrese cadena= "; cin>>cadena;
  int error=0;
  for(int i=0;(i<cadena.length());i++){
          cout<<cadena.at(i)<<endl;
  
  
  }
*/



    cout << endl << endl;
    system("PAUSE");
    return EXIT_SUCCESS;

}
