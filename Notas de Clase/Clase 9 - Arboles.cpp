
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class nodo {
public:
    T info;
    nodo *der, *izq;
};

template <class T> class arbol {
private:
    nodo<T>* raiz, * q;
    void ArbolBusq(T x, nodo<T>*& nuevo);
    void rid(nodo<T>* aux);
    void ird(nodo<T>* aux);
    void idr(nodo<T>* aux);
    void show(nodo<T>* aux, int n);
    bool Esta2(nodo<T>* aux, int x);
    void MostrarHojas2(nodo<T>* aux);
    T Menor2(nodo<T>* aux);
    T Mayor2(nodo<T>* aux);

public:
    arbol() { raiz = NULL; };
    ~arbol() {};
    void CreaArbolBus(T x);
    void RID() { rid(raiz); }
    void IRD() { ird(raiz); }
    void IDR() { idr(raiz); }
    void VerArbol() { show(raiz, 0); }
    bool Esta(int x);
    void MostrarHojas();
    T Menor();
    T Mayor();

};


template <class T> void arbol<T>::CreaArbolBus(T x)
{
    ArbolBusq(x, raiz);
}
template <class T> void arbol<T>::ArbolBusq(T x, nodo<T>*& nuevo)
{
    if (nuevo == NULL) {
        nuevo = new nodo<T>;
        nuevo->info = x; nuevo->der = nuevo->izq = NULL;
    }
    if (x > nuevo->info) ArbolBusq(x, nuevo->der);
    if (x < nuevo->info) ArbolBusq(x, nuevo->izq);
}
template <class T> void arbol<T>::ird(nodo<T>* aux)
{
    if (aux != NULL) {
        ird(aux->izq);
        cout << "\n" << aux->info;
        ird(aux->der);
    }
}
template <class T> void arbol<T>::rid(nodo<T>* aux)
{
    if (aux != NULL) {
        cout << "\n" << aux->info;
        rid(aux->izq);
        rid(aux->der);
    }
}
template <class T> void arbol<T>::idr(nodo<T>* aux)
{
    if (aux != NULL) {
        idr(aux->izq);
        idr(aux->der);
        cout << "\n" << aux->info;
    }
}
template <class T> void arbol<T>::show(nodo<T>* aux, int n)
{
    int i;
    if (aux != NULL) {                      //OjO este es un recorrido dri
        show(aux->der, n + 1);
        for (i = 1; i <= n; i++) cout << "     ";
        cout << aux->info << "\n";
        show(aux->izq, n + 1);
    }
}
//-------------------------------------------------------
int main(int argc, char* argv[])
{
    int i,x;
    arbol<int> A;
    int vec[10] = { 50,12,18,240,222,45,410,325,38,95 };
    //int vec[10]={50,120,180,240,252,450,460,475,488,595};
    for (i = 0; i < 10; i++) {
        A.CreaArbolBus(vec[i]);
        //T.VerArbol();
        //system("PAUSE");
    }

    A.VerArbol();
    
    cout << "\n IRD--------------------------------";
    A.IRD();
    cout << "\n RID--------------------------------";
    A.RID();
    cout<<"\n IDR--------------------------------";
    A.IDR();
   

    cout << "\n Mostrar Hojas ----------";
    A.MostrarHojas();
/*
    cout << "\n El menor del arbol= " << A.Menor();
*/
    if (A.Esta(95))cout << "\n\n El dato 95 esta";
    else cout << "\n\n El dato 95 NO esta";
    if (A.Esta(240))cout << "\n\n El dato 240 esta";
    else cout << "\n\n El dato 240 NO esta";
    cout << "El menor es " << A.Menor() << endl;
    cout << "El mayor es " << A.Mayor() << endl;
/*
       for(i=0;i<5;i++){
         cout<<"\n -------------------------------- Ing dato a borrar= "; cin>>x;
         A.Borrar(x);
         A.VerArbol();

       }
    cout << endl << endl;
    */
   system("PAUSE");
    return EXIT_SUCCESS;
}

/*
Realizar los siguientes metodos de la clase arbol
void MostrarHojas() //muestra todas las hojas del arbol
bool Esta(x) //retorna true si x esta en el arbol
T Menor() // retorna el menor valor del arbol
T Mayor() // retorna el mayor valor del arbol
void Borrar(x) // elimina el nodo que contiene el dato x

*/

template <class T> bool arbol<T> :: Esta(int x) {
    if(Esta2(raiz, x)) return true;
    else return false;
}

template <class T> bool arbol<T> :: Esta2(nodo<T>* aux, int x)
{
    if (aux != NULL) {
        if(aux->info == x){
            return true;
        }
        return (Esta2(aux->izq,x) || Esta2(aux->der,x));
    }
    return false;
}

template <class T> void arbol<T> :: MostrarHojas(){
    MostrarHojas2(raiz);
}

template <class T> void arbol<T> :: MostrarHojas2(nodo<T>* aux){

    if(aux->der != NULL){
        MostrarHojas2(aux->der);
    }
    if(aux->izq != NULL){
        MostrarHojas2(aux->izq);
    }
    if(aux->der == NULL && aux->izq == NULL)
    cout << "\n" << aux->info << endl;
}

template <class T> T arbol<T> :: Menor(){
    return Menor2(raiz);
}

template <class T> T arbol<T> :: Menor2(nodo<T>* aux){
    if(aux->izq != NULL){
        return Menor2(aux->izq);
    }
    return aux->info;
}

template <class T> T arbol<T> :: Mayor(){
    return Mayor2(raiz);
}

template <class T> T arbol<T> :: Mayor2(nodo<T>* aux){
    if(aux->der != NULL){
        return Mayor2(aux->der);
    }
    return aux->info;
}
