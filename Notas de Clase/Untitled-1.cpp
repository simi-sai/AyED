#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

#define MAX 10

using namespace std;

template <class T> class Nodo {
private:
  T dato;
  Nodo *next;

public:
  Nodo() { next = NULL; };
  Nodo(T a) {
    dato = a;
    next = NULL;
  };
  void set_dato(T a) { dato = a; };
  void set_next(Nodo *n) { next = n; };
  T get_dato() { return dato; };
  Nodo *get_next() { return next; };
  bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private:
  Nodo<T> *czo;
  void addO(T d, Nodo<T> *ant);
  void borrarD(T d, Nodo<T> *ant);

public:
  Lista() { czo = new Nodo<T>(); };
  Lista(Nodo<T> *n) { czo = n; };
  //~Lista(void);
  void add(T d); // sumar nodos a la lista
  bool esvacia(void);
  T cabeza(void);     // retorna el dato del primer nodo
  Lista *resto(void); // retorna el puntero al "resto" de la lista
                      // resto= lo que queda de la lista sin la cabeza
  string toPrint(string p);
  void impre(void);
  T suma(T i);
  int size();
  bool esta(T d);                            // detecta si d esta en la lista
  void borrarDato(T d) { borrarD(d, NULL); } // borra el nodo que contiene d
  void borrar(void);                         // borra la cabeza
  void borrar_last();                        // borra el ultimo
  void concat(Lista<T> *l1); // le transfiere los datos de l1 a this
  Lista<T> *copy(void);      // hace una copia de la lista
  void tomar(int n); // deja "vivos" los n primeros nodos y borra el resto
  void addOrdenado(T d) {
    addO(d, NULL);
  };        // sumar nodos a la lista Ordenados de menor a MAYOR
  T last(); // retorna el dato del ultimo nodo
};
template <class T> T Lista<T>::last() {
  if (!this->esvacia()) {
    if (this->resto()->esvacia())
      return this->cabeza();
    return this->resto()->last();
  }
  return 0;
}

template <class T>
void Lista<T>::add(T d) // 100
{
  Nodo<T> *nuevo = new Nodo<T>(d);
  nuevo->set_next(czo);
  czo = nuevo;
}
template <class T> bool Lista<T>::esvacia(void) { return czo->es_vacio(); }
template <class T> T Lista<T>::cabeza(void) {
  if (this->esvacia()) {
    cout << " Error, Cabeza de lista vacia";
    return 0;
  }
  return czo->get_dato();
}

template <class T> Lista<T> *Lista<T>::resto(void) {
  Lista *l = new Lista(czo->get_next());
  return (l);
}

template <class T> string Lista<T>::toPrint(string p) {
  if (this->esvacia()) {
    return p;
  } else {
    // std::ostringstream stm;
    ostringstream stm;
    stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
    // cout<<endl<<" stm.str()= "<<stm.str()<<endl;
    return stm.str();
  }
}

template <class T> T Lista<T>::suma(T i) { // cout<<" i al entrar= "<<i<<endl;
  if (this->esvacia()) {
    return i;
  } else {

    // cout<<"this->cabeza()= "<<this->cabeza()<<endl;
    return this->resto()->suma(i + this->cabeza());
  }
}

template <class T> int Lista<T>::size() {
  if (this->esvacia())
    return 0;
  return 1 + this->resto()->size();
}

template <class T> void Lista<T>::borrar(void) { // borra el nodo cabeza
  if (!this->esvacia()) {
    Nodo<T> *tmp = czo;
    czo = czo->get_next();
    delete tmp;
  }
}

template <class T> void Lista<T>::borrar_last() { // borra el ultimo nodo
  if (!this->esvacia()) {
    if ((czo->get_next())->get_next() == NULL) {
      delete czo->get_next();
      czo->set_next(NULL);
    } else
      this->resto()->borrar_last();
  }
}

template <class T>
void Lista<T>::concat(Lista<T> *l1) { // le transfiere los datos de l1 a this
  if (!(l1->esvacia())) {
    this->concat(l1->resto());
    this->add(l1->cabeza());
  }
}

template <class T> Lista<T> *Lista<T>::copy(void) {
  Lista<T> *aux = new Lista();
  aux->concat(this);
  return aux;
}

template <class T>
void Lista<T>::tomar(
    int n) { // deja "vivos" los n primeros nodos y borra el resto
  if (this->size() > n) {
    this->borrar_last();
    this->tomar(n);
  }
}

template <class T> void Lista<T>::impre(void) {
  Nodo<T> *aux;
  aux = czo;
  while (aux->get_next() != NULL) {
    cout << aux->get_dato() << endl;
    aux = aux->get_next();
  }
}

template <class T> void Lista<T>::addO(T d, Nodo<T> *ant) {
  if (this->esvacia()) { // el primero
    this->add(d);
  } else {
    if (d < czo->get_dato()) {
      if (ant == NULL) { // al principio
        this->add(d);
      } else { // entre medio
        Nodo<T> *nuevo = new Nodo<T>(d);
        nuevo->set_next(ant->get_next());
        ant->set_next(nuevo);
      }
    } else {
      if ((czo->get_next())->get_next() == NULL) { // al final
        Nodo<T> *nuevo = new Nodo<T>(d);
        nuevo->set_next(czo->get_next());
        czo->set_next(nuevo);

      } else
        this->resto()->addO(d, czo);
    }
  }
}

template <class T> bool Lista<T>::esta(T d) { // busca d en la lista
  if (this->esvacia())
    return false;
  if (this->cabeza() == d)
    return true;

  return this->resto()->esta(d);
}

template <class T> void Lista<T>::borrarD(T d, Nodo<T> *ant) {
  if (!this->esvacia()) {
    if (d == this->cabeza()) {
      if (ant == NULL) { // al principio
        this->borrar();
      } else { // entre medio
        ant->set_next(czo->get_next());
        delete czo;
      }
    } else
      this->resto()->borrarD(d, czo);
  }
}

template <class T> class Pila : public Lista<T> {
public:
  Pila() { Lista<T>(); };
  void apilar(T d) { this->add(d); };
  T tope(void) { return this->cabeza(); };
  void desapilar(void) { this->borrar(); };
  bool pilavacia() { return this->esvacia(); };
};

template <class T> class Cola : public Lista<T> {
public:
  Cola(void) { Lista<T>(); };
  //~Cola(void);
  T tope() { return this->last(); };
  bool colavacia(void) { return this->esvacia(); };
  void encolar(T a) { this->add(a); };
  void desencolar(void) { this->borrar_last(); };
  T ultimo(void) { return this->cabeza(); };
  string imprimir(string s) { return this->toPrint(s); };
  int sizeCola() {
    if (this->esvacia())
      return 0;
    return 1 + this->resto()->size();
  }
};
//---------------------------------------------

class Cajon {
private:
  int id;
  string tipo_fruta;
  int cantidad;
  int exceso;

public:
  Cajon(int id, string tipoF, int cant) {
    this->id = id;
    tipo_fruta = tipoF;
    cantidad = 0;
    exceso = 0;
  }
  int getExceso() { return exceso; };
  void setExceso(int s) { exceso = s; }
  int getId() { return id; };
  void setId(int s) { id = s; }
  string getTipoFruta() { return tipo_fruta; }
  int getCantidad() { return cantidad; }
  void setCantidad(int c) { cantidad = c; }
  bool estaCompleto() { return cantidad == 20.0; }
  bool estavacio() { return cantidad == 0; };

  bool sePuedeAgregar(int c) {
    return (cantidad + c > 0 && cantidad + c <= 20) ? true : false;
  }

  void agregarFruta(int c) {
    int aux = this->getCantidad() + c;
    if (estaCompleto()) {
      this->setCantidad(20);
      this->exceso += c;
    } else if (sePuedeAgregar(c)) {
      this->setCantidad(getCantidad() + c);
      this->exceso += 0;
    } else {
      this->setCantidad(20);
      (aux - 20 >= 0) ? (this->exceso += aux - 20) : (this->exceso += 0);
    }
  }
};

class Seccion {
private:
  Pila<Cajon *> cajonesApilados[10];
  string tipo_fruta;
  int cantidadCajones;
  int cantidadFruta;
  int pilaId;

public:
  Seccion(string t) {
    this->tipo_fruta = t;
    this->cantidadCajones = 0;
    this->cantidadFruta = 0;
    this->pilaId = 0;
  }
  void agregarFruta(int c);
  void sacarFruta(int c);
  void imprimirPila(int);
  string getTipo() { return tipo_fruta; };
  int getCantCajones() { return cantidadCajones; };
  int getPilaId() { return pilaId; };
  Pila<Cajon *> getPilaCajones(int n) { return this->cajonesApilados[n]; };
  void setCantFruta(int ct) { cantidadFruta = ct; }
  int getCantFruta();
};


int Seccion::getCantFruta(){
  int cajones = 0;
  int tope = 0;

  if (this->getCantCajones() != 0){
    cajones = this->getCantCajones() - 1;
    tope = this->cajonesApilados[pilaId].tope()->getCantidad();
  }

  return (20*cajones) + tope;
}

void Seccion::agregarFruta(int c) {
  int frutasRestantes = c;
  int Max = (pilaId + 1) * 200;
  while (frutasRestantes > 0 && cantidadFruta <= Max) {
    if (cajonesApilados[pilaId].pilavacia() ||
        cajonesApilados[pilaId].tope()->estaCompleto()) {

      Cajon *nuevoCajon = new Cajon(cantidadCajones + 1, tipo_fruta, 0);
      cajonesApilados[pilaId].apilar(nuevoCajon);
      cantidadCajones++;
    } else {
    int frutasFaltantes = 20 - cajonesApilados[pilaId].tope()->getCantidad();
    if (frutasFaltantes >= frutasRestantes) {  //15 y tengo 5
      cajonesApilados[pilaId].tope()->agregarFruta(frutasRestantes);
      cantidadFruta += frutasRestantes;
      frutasRestantes = 0; 
    } else {
      cajonesApilados[pilaId].tope()->agregarFruta(frutasFaltantes);
      cantidadFruta += frutasFaltantes;
      frutasRestantes -= frutasFaltantes;
      }
    }
  }
  if(cantidadFruta >= Max && pilaId <= 9)
  {
    pilaId++;
    this->agregarFruta(c-Max);
  }
}


void Seccion::sacarFruta(int cant) {
  if (cajonesApilados[pilaId].pilavacia()) {
    if (pilaId >= 0){
    pilaId--;
    sacarFruta(cant);
    }else{
    cout << "\n NO HAY MAS FRUTA CRACK";
    }
  } else {

    if (cant >= 20) {
      if (this->cajonesApilados[pilaId].tope()->getCantidad() == 20) {
        this->cajonesApilados[pilaId].desapilar();
        this->cantidadCajones--;
        //this->cantidadFruta -= 20;
        sacarFruta(cant - 20);
      } else {
        int cantCj = this->cajonesApilados[pilaId].tope()->getCantidad();
        this->cajonesApilados[pilaId].desapilar();
        this->cantidadCajones--;
        //this->cantidadFruta -= 20;
        sacarFruta(cant - cantCj);
      }
    } else {
      if (cant < this->cajonesApilados[pilaId].tope()->getCantidad()) {
        int cantCj = this->cajonesApilados[pilaId].tope()->getCantidad();
        this->cajonesApilados[pilaId].tope()->setCantidad(cantCj - cant);
        //this->cantidadFruta -= cant;
        
      } else {
        int cantCj = this->cajonesApilados[pilaId].tope()->getCantidad();
        this->cajonesApilados[pilaId].desapilar();
        this->cantidadCajones--;
        //this->cantidadFruta -= cant - cantCj;
        sacarFruta(cant - cantCj);
      }
    }
  }
}

void Seccion::imprimirPila(int n) {
  
if (n >= 0) {
  Pila<Cajon *> pilaAux = this->getPilaCajones(n);

    while (!pilaAux.pilavacia()) {
      Cajon *cj1 = pilaAux.tope();
      cout << "\nCAJON ID: " << cj1->getId()
           << "  FRUTA TOTAL (EN KG): " << cj1->getCantidad() << endl;
      pilaAux.desapilar();
    }
      n--;
      this->imprimirPila(n);
  }
}

class Deposito { // Deposito == Stock
private:
  Seccion *sectores[3];
  int cant_dulce;
  int cant_acida;
  int cant_neutra;

public:
  Deposito() {
    sectores[0] = NULL;
    sectores[1] = NULL;
    sectores[2] = NULL;
    this->cant_dulce = 0;
    this->cant_acida = 0;
    this->cant_neutra = 0;
  };
  void agregarSeccion(Seccion *c);
  Seccion *getSeccion(int);
  int getCantDulce();
  int getCantAcida();
  int getCantNeutra();
  void setCantDulce(int d) { cant_dulce = d; }
  void setCantAcida(int a) { cant_acida = a; }
  void setCantNeutra(int n) { cant_neutra = n; }
};

int Deposito::getCantDulce() { int n = this->getSeccion(0)->getCantFruta(); 
                               this->cant_dulce = n;
                               return cant_dulce;
}

int Deposito::getCantAcida() { int n = this->getSeccion(1)->getCantFruta();
                               this->cant_acida = n;
                               return cant_acida;}

int Deposito::getCantNeutra() { int n = this->getSeccion(2)->getCantFruta(); 
                                this->cant_neutra = n;
                                return cant_neutra;}

Seccion *Deposito ::getSeccion(int i) { return this->sectores[i]; }

void Deposito ::agregarSeccion(Seccion *c) {
  
  if (c->getTipo() == "Dulce") {
    this->sectores[0] = c;
  } else if (c->getTipo() == "Acida") {
    this->sectores[1] = c;
  } else {
    this->sectores[2] = c;
  }
}

class Pedidos {

private:
  string nombre_cliente;
  string tipo_cliente;
  string tipo_fruta;
  int cant_fruta;

public:
  Pedidos(string nombreC, string tipoC, string tipoF, int cant) {
    this->nombre_cliente = nombreC;
    this->tipo_cliente = tipoC;
    this->tipo_fruta = tipoF;
    this->cant_fruta = cant;
  }

  string getNombreCliente() { return nombre_cliente; };
  string getTipoCliente() { return tipo_cliente; };
  string getTipoFruta() { return tipo_fruta; };
  int getCantidadPedido() { return cant_fruta; };
};

class GestionPedidos {
private:
  Cola<Pedidos *> pedidosMayorista;
  Cola<Pedidos *> pedidosMinorista;
  Cola<Pedidos *> pedidosEsperaMay;
  Cola<Pedidos *> pedidosEsperaMin;
  Deposito *stockDisponible;
  int prioridad; // Num 0 = Mayorista>Minorista -- Num1 = Minorista>Mayorista
public:
  GestionPedidos(Deposito* s) { this->stockDisponible = s; };
  void registrarPedido(string, string, string, int);
  void imprimirPedidos();
  void setPrioridad(int p) { prioridad = p; };
  int getPrioridad() { return prioridad; };
  void ventaMayorista(Pedidos *);
  void ventaMinorista(Pedidos *);
  // void entregarPedido();
  bool esPosible(Pedidos *pedido);
  void stockActual();
  void actualizarStock();
  void entregarPedido(int n);
  void ImpreEstado();
  void entregarPedidosNormales(Cola<Pedidos *> aux, int n);
  void entregarPedidosPendientes(Cola<Pedidos *> aux, int n);
  void ventaPedido(Pedidos *pedido);
};


void GestionPedidos::stockActual(){
    int dulce =  this->stockDisponible->getCantDulce();
    int acida = this->stockDisponible->getCantAcida();
    int neutra = this->stockDisponible->getCantNeutra();
    cout << "STOCK -------------------\n" << endl;
    cout << "CANTIDAD FRUTA DULCE (KG) = " << dulce << endl;
    cout << "CANTIDAD FRUTA ACIDA (KG) = " << acida << endl;
    cout << "CANTIDAD FRUTA NEUTRA (KG) = "<< neutra << endl;
  
}

bool GestionPedidos::esPosible(Pedidos *pedido) {
  int cantPedido = 0;

  if (pedido->getTipoCliente() == "Minorista") {
    cantPedido = pedido->getCantidadPedido();
  } else {
    cantPedido = (pedido->getCantidadPedido()) * 20;
  }

  if (pedido->getTipoFruta() == "Dulce" &&
      cantPedido <= this->stockDisponible->getCantDulce()) {
    return true;
  } else if (pedido->getTipoFruta() == "Acida" &&
             cantPedido <= this->stockDisponible->getCantAcida()) {
    return true;
  } else if (pedido->getTipoFruta() == "Neutra" &&
             cantPedido <= this->stockDisponible->getCantNeutra()) {
    return true;
  } else {
    return false;
  }
}

void GestionPedidos::registrarPedido(string nombre, string tipo, string tipoF,
                                     int cant) {

  Pedidos *pedidoAux = new Pedidos(nombre, tipo, tipoF, cant);
  string min("Minorista");
  int test = min.compare(tipo);
  switch (test) {
  case 0:
    pedidosMinorista.encolar(pedidoAux);
    break;
  default:
    pedidosMayorista.encolar(pedidoAux);
    break;
  }
}

void GestionPedidos::imprimirPedidos() {
  Cola<Pedidos *> colaPedidos = this->pedidosMinorista;
  while (!colaPedidos.colavacia()) {
    string nombreCliente = colaPedidos.tope()->getNombreCliente();
    string tipoCliente = colaPedidos.tope()->getTipoCliente();
    cout << "\nNOMBRE CLIENTE: " << nombreCliente
         << "\nTIPO CLIENTE: " << tipoCliente;
    colaPedidos.desencolar();
  }
  colaPedidos = this->pedidosMayorista;
  while (!colaPedidos.colavacia()) {
    string nombreCliente = colaPedidos.tope()->getNombreCliente();
    string tipoCliente = colaPedidos.tope()->getTipoCliente();
    cout << "\nNOMBRE CLIENTE: " << nombreCliente
         << "\nTIPO CLIENTE: " << tipoCliente;
    colaPedidos.desencolar();
  }
}

void GestionPedidos::ventaPedido(Pedidos *pedido) {
  int cantPedido;
  string tipo = pedido->getTipoFruta();
  string tipoC = pedido->getTipoCliente();
  string dulce("Dulce");
  string acida("Acida");
  string neutra("Neutra");

  if (tipoC == "Minorista") {
    cantPedido = pedido->getCantidadPedido();
  } else {
    cantPedido = (pedido->getCantidadPedido()) * 20;
  }

  if (tipo == dulce) {
    this->stockDisponible->getSeccion(0)->sacarFruta(cantPedido);
  } else if (tipo == acida) {
    this->stockDisponible->getSeccion(1)->sacarFruta(cantPedido);
  } else if (tipo == neutra) {
    this->stockDisponible->getSeccion(2)->sacarFruta(cantPedido);
  } else {
  }
}

void GestionPedidos ::entregarPedido(int n) {
  if (n == 0) { // priridad minorista>mayorista
    entregarPedidosPendientes(pedidosEsperaMin, 0);
    entregarPedidosPendientes(pedidosEsperaMay, 1);
    entregarPedidosNormales(pedidosMinorista, 0);
    entregarPedidosNormales(pedidosMayorista, 1);

  } else if (n == 1) {
    entregarPedidosPendientes(pedidosEsperaMay, 1);
    entregarPedidosPendientes(pedidosEsperaMin, 0);
    entregarPedidosNormales(pedidosMayorista, 1);
    entregarPedidosNormales(pedidosMinorista, 0);
  }
}

void GestionPedidos ::entregarPedidosPendientes(Cola<Pedidos *> aux, int n) {
  if (!aux.colavacia()) {
    if (esPosible(aux.tope())) {
      ventaPedido(aux.tope());
      aux.desencolar();
      entregarPedidosPendientes(aux, n);
    }
  }
}

void GestionPedidos ::entregarPedidosNormales(Cola<Pedidos *> aux, int n) {
  if (!aux.colavacia()) {
    if (esPosible(aux.tope())) {
      ventaPedido(aux.tope());
      aux.desencolar();
      entregarPedidosNormales(aux, n);
    } else {
      if (n == 0) {
        pedidosEsperaMin.encolar(aux.tope());
        aux.desencolar();
        entregarPedidosNormales(aux, n);
      } else {
        pedidosEsperaMay.encolar(aux.tope());
        aux.desencolar();
        entregarPedidosNormales(aux, n);
      }
    }
  }
}

void GestionPedidos::ImpreEstado() {
  if (!this->pedidosEsperaMay.colavacia()) {
    cout << "\nHay " << pedidosEsperaMay.sizeCola()
         << " pedidos en espera tipo Mayorista" << endl;
  } else {
    cout << "No hay pedidos en espera de Tipo Mayorista" << endl;
  }
  if (!this->pedidosEsperaMin.colavacia()) {
    cout << "\nHay " << this->pedidosEsperaMin.sizeCola()
         << " pedidos en espera tipo Minorista" << endl;
  } else {
    cout << "No hay pedidos en espera de Tipo Minorista" << endl;
  }
  cout << "\n Hay " << pedidosMayorista.sizeCola() << " pedidos Mayoristas"
       << endl;
  cout << "\n Hay " << pedidosMinorista.sizeCola() << " pedidos Minoristas"
       << endl;
}

int main() {

  Seccion *seccion_dulce = new Seccion("Dulce");
  Seccion *seccion_acida = new Seccion("Acida");
  Seccion *seccion_neutra = new Seccion("Neutra");

  Deposito *deposito = new Deposito();
  GestionPedidos *pedidos = new GestionPedidos(deposito);
  
  deposito->agregarSeccion(seccion_dulce);
  deposito->agregarSeccion(seccion_acida);
  deposito->agregarSeccion(seccion_neutra);
  
  seccion_dulce->agregarFruta(200);
  seccion_acida->agregarFruta(150);
  seccion_neutra->agregarFruta(110);
  

  pedidos->registrarPedido("Rodrigo", "Minorista", "Acida", 50); // 
  pedidos->registrarPedido("Emiliano", "Mayorista", "Dulce", 4);
  pedidos->registrarPedido("Jose", "Mayorista", "Acida", 3);
  pedidos->registrarPedido("Simon", "Minorista", "Dulce", 60); //  
  pedidos->registrarPedido("Anibal", "Minorista", "Neutra", 80); //

  cout << "1--------------------------------------------" << endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce();
  cout << "\nCANT INICIAL DE FRUTA ACIDA: " << deposito->getCantAcida();
  cout << "\nCANT INICIAL DE FRUTA NEUTRA: " << deposito->getCantNeutra();
  cout << "\n--------------------------------------------" << endl;

  // CANT DULCE = 140 = 60
  // CANT ACIDA = 100 = 40
  // CANT NEUTRA = 30 = 30
  pedidos->ImpreEstado();
  pedidos->entregarPedido(0);
  pedidos->ImpreEstado();
  
  cout << "2--------------------------------------------" << endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce();
  cout << "\nCANT INICIAL DE FRUTA ACIDA: " << deposito->getCantAcida();
  cout << "\nCANT INICIAL DE FRUTA NEUTRA: " << deposito->getCantNeutra();
  cout << "\n--------------------------------------------" << endl;

  /*
  pedidos->entregarPedido(1);
  pedidos->ImpreEstado();
  // CANT ACIDA = 55 KG
  // CANT DULCE = 10
  cout << "3--------------------------------------------" << endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce();
  cout << "\nCANT INICIAL DE FRUTA ACIDA: " << deposito->getCantAcida();
  cout << "\nCANT INICIAL DE FRUTA NEUTRA: " << deposito->getCantNeutra();
  cout << "\n--------------------------------------------" << endl;

  // seccion_acida->agregarFruta(10); // ACIDA = 5;
  pedidos->entregarPedido(1);
  pedidos->ImpreEstado();

  cout << "4--------------------------------------------" << endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce();
  cout << "\nCANT INICIAL DE FRUTA ACIDA: " << deposito->getCantAcida();
  cout << "\nCANT INICIAL DE FRUTA NEUTRA: " << deposito->getCantNeutra();
  cout << "\n--------------------------------------------" << endl;
  /*
  cout << "--------------------------------------------"<< endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce();
  cout << "\nCANT INICIAL DE FRUTA ACIDA: " << deposito->getCantAcida();
  cout << "\n--------------------------------------------"<< endl;

  seccion_dulce->agregarFruta(50); // DULCE = 90;
  seccion_acida->agregarFruta(50); // ACIDA = 100;


  pedidos->entregarPedido(0);
  pedidos->ImpreEstado();

  cout << "--------------------------------------------"<< endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce(); //
  DULCE = 30 cout << "\nCANT INICIAL DE FRUTA ACIDA: " <<
  deposito->getCantAcida(); // ACIDA = 40; cout <<
  "\n--------------------------------------------"<< endl;

  /*pedidos->entregarPedido();

  cout << "\nCANTI ACTUAL DE FRUTA DULCE: "<< deposito->getCantDulce(); //
  CANT_DULCE = 40 con 60 en espera cout << "\nCANTI ACTUAL DE FRUTA ACIDA: "<<
  deposito->getCantAcida(); // CANT_ACIDA = 50 con 60 en espera

  seccion_acida->agregarFruta(80);
  cout << "\nCANTI ACTUAL DE FRUTA ACIDA: "<< deposito->getCantAcida(); //
  CANT_ACIDA = 50 con 60 en espera pedidos->entregarPedido();

  cout << "\nCANTI ACTUAL DE FRUTA DULCE: "<< deposito->getCantDulce(); //
  CANT_DULCE = 40 con 60 en espera cout << "\nCANTI ACTUAL DE FRUTA ACIDA: "<<
  deposito->getCantAcida(); // CANT_ACIDA = 70 sin kg en espera
  */

  return 0;
}