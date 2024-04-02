#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private:
    Nodo<T>* czo;
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    //~Lista(void);
    void add(T d);
    bool esvacia(void);
    T cabeza(void);
    Lista* resto(void);
    string toPrint(string p);
    T suma(T i);
    int size(); // cantidad de nodos de la lista
    void borrar(void); //borra la cabeza
    void borrar_last(); //borra el ultimo
    void concat(Lista* l1); // le transfiere los datos de l1 a this
    Lista* copy(void); // hace una copia de la lista
    void tomar(int n); //deja "vivos" los n primeros nodos y borra el resto
    void impre(void); //imprime de manera no recursiva (iterativa)
    void addOrdenado(T d); //agrega valores de manera ordenada
};

template <class T>
void Lista<T>::add(T d)
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
T Lista<T>::cabeza(void)
{
    if (esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}

template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}

template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia()) 
    {
        return p;
    } else {
        //std::ostringstream stm;
        ostringstream stm;            //es un buffer (????)
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}

template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
}

// cantidad de nodos de la lista
template <class T> int Lista<T> :: size() //cantidad de nodos de la lista
{
    if (this->esvacia()) { return 0; } 
    else { return 1 + this->resto()->size(); }
}

//borra la cabeza
template <class T> void Lista <T> :: borrar(void)
{
    if (!this->esvacia())
    {
        Nodo<T>* temp = czo;
        czo = czo->get_next();
        delete temp;
    }
}

//borra el ultimo
template <class T> void Lista<T> :: borrar_last(void)
{
    if(!this->esvacia())
    {
        if((czo->get_next())->get_next() == NULL)
        {
            delete czo->get_next();
            czo->set_next(NULL);
        } else {
            this->resto()->borrar_last();
        }
    }
}

// le transfiere los datos de l1 a this
template <class T> void Lista<T> :: concat(Lista<T>* l1)
{
    if(!l1->esvacia())
    {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

// hace una copia de la lista
template <class T> Lista<T>* Lista<T> :: copy(void)
{
    Lista<T>* aux = new Lista<T>();
    aux->concat(this);
    return aux;
}

//deja "vivos" los n primeros nodos y borra el resto
template <class T> void Lista<T> :: tomar(int n)
{
    if(this->size() > n)
    {
        this->borrar_last();
        this->tomar(n);
    }
}

//imprime de manera no recursiva (iterativa)
template <class T> void Lista<T> :: impre(void)
{
    Nodo<T>* aux = czo;

    while(aux->get_next() != NULL)
    {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

//suma nodos ordenados de menor a mayor
template <class T> void Lista<T> :: addOrdenado(T d)
{
    if(!this->esvacia())
    {
        if(this->cabeza() > d)
        {
            this->add(d);
        } else {
            this->resto()->addOrdenado(d);
        }
    }
}

int main()
{
    Lista<string>* l = new Lista<string>();
    Lista<int>* r = new Lista<int>();
    Lista<string>* l2 = new Lista<string>();
    l->add(" 11x");
    l->add(" 22y");
    l->add(" 33z");
    r->add(100);
    r->add(22);
    l2->add(" 44");
    l2->add(" 55");
    cout << "l= "<<l->toPrint("fin") << endl;
    cout << "r= " << r->toPrint("fin") << endl;
    cout << "suma:" << r->suma(0) << endl;
    cout << "Tamaño: " << l->size() << endl;
    cout << "Tamaño: " << r->size() << endl;
    cout << "Tamaño: " << l2->size() << endl;
    l->borrar();
    cout << "l= "<<l->toPrint("fin") << endl;
    l->borrar_last();
    l->concat(l2);
    cout << l->toPrint("fin");
    cout << "copia de l: " << l->copy()->toPrint("fin") << endl;
    cout << "copia de l2: " << l2->copy()->toPrint("fin") << endl;
    cout << "copia de r: " << r->copy()->toPrint("fin") << endl;
    l->tomar(3);
    cout << "sobreviviendo el n valor: " << l->toPrint("fin") << endl;
    l->impre();
    l2->impre();
    r->addOrdenado(4);
    r->addOrdenado(44);
    cout << "addord: " << r->toPrint("fin") << endl;
    r->addOrdenado(55);
    cout << "addord: " << r->toPrint("fin") << endl;
    system("PAUSE");
    return EXIT_SUCCESS;

}