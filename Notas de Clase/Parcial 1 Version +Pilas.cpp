#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

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

public:
  Cajon(int id, string tipoF, int cant) {
    this->id = id;
    tipo_fruta = tipoF;
    cantidad = 0;
  }
  int getId() { return id; };
  void setId(int s) { id = s; };
  string getTipoFruta() { return tipo_fruta; };
  int getCantidad() { return cantidad; };
  void setCantidad(int c) { cantidad = c; };
  bool estaCompleto() { return cantidad == 20; };
  bool estavacio() { return cantidad == 0; };

  bool sePuedeAgregar(int c) {
    return (cantidad + c > 0 && cantidad + c < 20) ? true : false;
  }
};

class Seccion {
private:
  Pila<Cajon *> cajonesApilados[3];
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
  //void sacarFruta(int c);
  void imprimirPila();
  string getTipo() { return tipo_fruta; };
  int getCantCajones() { return cantidadCajones; };
  Pila<Cajon *> getPilaCajones() { return this->cajonesApilados[pilaId]; };
  void setCantFruta(int ct) { cantidadFruta = ct; }
  int getCantFruta();
};

int Seccion::getCantFruta() {
  int cantCajones;
  int cantTope;

  if (this->getCantCajones() != 0) {
    cantCajones = this->getCantCajones() - 1;
    cantTope = this->cajonesApilados[pilaId].tope()->getCantidad();
  } else {
    cantCajones = 0;
    cantTope = 0;
  }

  return (cantCajones * 20) + cantTope;
}

void Seccion::agregarFruta(int c) {
  int Max = (pilaId+1)*200;
  if (this->getCantFruta() + c <= Max) {
    if (cajonesApilados[pilaId].pilavacia() || cajonesApilados[pilaId].tope()->estaCompleto()) {
      // si la pila está vacía o el último cajón está completo, agrega un nuevo
      // cajón a la pila
      if (cantidadCajones < 30) {
        Cajon *nuevoCajon = new Cajon(cantidadCajones + 1, tipo_fruta, 0);
        cajonesApilados[pilaId].apilar(nuevoCajon);
        cantidadCajones++;
      }
    }
    // agrega la fruta al cajón actual
    int cantidadFaltante = 20 - cajonesApilados[pilaId].tope()->getCantidad();
    if (c > cantidadFaltante) {
      cajonesApilados[pilaId].tope()->setCantidad(20);
      agregarFruta(c - cantidadFaltante);
    } else {
      cajonesApilados[pilaId].tope()->setCantidad(
          cajonesApilados[pilaId].tope()->getCantidad() + c);
      cantidadFruta += c;
    }
  } else {
    int aux = cajonesApilados[pilaId].tope()->getCantidad();
    cajonesApilados[pilaId].tope()->setCantidad(20);
    pilaId++;
    this->agregarFruta(c-(20-aux));
  }
}

/*
void Seccion::sacarFruta(int cant) {
  if (cajonesApilados[pilaId].pilavacia()) {

    this->setCantFruta(0);
    cout << "\nNO HAY MAS FRUTA PA\n";
  } else {

    if (cant >= 20) {
      if (this->cajonesApilados[pilaId].tope()->getCantidad() == 20) {
        this->cajonesApilados[pilaId].desapilar();
        this->cantidadCajones--;
        sacarFruta(cant - 20);
      } else {

        int cantCj = this->cajonesApilados.tope()->getCantidad();
        this->cajonesApilados.desapilar();
        this->cantidadCajones--;
        sacarFruta(cant - cantCj);
      }
    } else {
      if (cant < this->cajonesApilados.tope()->getCantidad()) {
        int cantCj = this->cajonesApilados.tope()->getCantidad();
        this->cajonesApilados.tope()->setCantidad(cantCj - cant);
      } else {
        int cantCj = this->cajonesApilados.tope()->getCantidad();
        this->cajonesApilados.desapilar();
        this->cantidadCajones--;
        sacarFruta(cant - cantCj);
      }
    }
  }
}*/
/*
void Seccion::imprimirPila() {

  int cajones = this->getCantCajones();
  Pila<Cajon *> pilaAux = this->getPilaCajones();

  while (!pilaAux.pilavacia()) {
    Cajon *cj1 = pilaAux.tope();
    cout << "CAJON ID: " << cj1->getId()
         << "FRUTA TOTAL (EN KG): " << cj1->getCantidad() << endl;
    pilaAux.desapilar();
  }
}*/

/*
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

int Deposito::getCantDulce() { return this->getSeccion(0)->getCantFruta(); }

int Deposito::getCantAcida() { return sectores[1]->getCantFruta(); }

int Deposito::getCantNeutra() { return this->getSeccion(2)->getCantFruta(); }

Seccion *Deposito ::getSeccion(int i) { return this->sectores[i]; }

void Deposito ::agregarSeccion(Seccion *c) {
  string dulce("Dulce");
  string acida("Acida");
  string neutra("Neutra");
  int cmp1 = c->getTipo().compare(dulce);
  int cmp2 = c->getTipo().compare(acida);
  int cmp3 = c->getTipo().compare(neutra);

  if (cmp1 == 0) {
    this->sectores[0] = c;
  } else if (cmp2 == 0) {
    this->sectores[1] = c;
  } else if (cmp3 == 0) {
    this->sectores[2] = c;
  } else {
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
  GestionPedidos(Deposito *s) { this->stockDisponible = s; };
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

  Cola<Pedidos *> getPedidosMin() { return pedidosMinorista; };
  void entregarPedidosNormales(Cola<Pedidos *> aux, int n);
  void entregarPedidosPendientes(Cola<Pedidos *> aux, int n);
  void ventaPedido(Pedidos *pedido);
};

void GestionPedidos::stockActual(){
    int cant_dulce = this->stockDisponible->getCantDulce();
    int cant_acida = this->stockDisponible->getCantAcida();
    int cant_neutra = this->stockDisponible->getCantNeutra();
    cout << "STOCK -------------------\n"<<
    "CANTIDAD FRUTA DULCE (KG) = "<< cant_dulce << endl;
    "CANTIDAD FRUTA ACIDA (KG) = "<< cant_acida << endl;
    "CANTIDAD FRUTA NEUTRA (KG) = "<< cant_neutra;
}*/
/*
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
    cout << "\nPEDIDOS EN ESPERA: \nHay " << this->pedidosEsperaMay.sizeCola()
         << " pedidos en espera tipo Mayorista" << endl;
  } else {
    cout << "No hay pedidos en espera de Tipo Mayorista" << endl;
  }
  if (!this->pedidosEsperaMin.colavacia()) {
    cout << "\nPEDIDOS EN ESPERA: \nHay " << this->pedidosEsperaMin.sizeCola()
         << " pedidos en espera tipo Minorista" << endl;
  } else {
    cout << "No hay pedidos en espera de Tipo Minorista" << endl;
  }
}

void GestionPedidos::imprimirPedidos() {
  Cola<Pedidos *> aux;
  while (!pedidosMinorista.colavacia()) {
    string nombreCliente = pedidosMinorista.tope()->getNombreCliente();
    string tipoCliente = pedidosMinorista.tope()->getTipoCliente();
    int cantidad_fruta = pedidosMinorista.tope()->getCantidadPedido();
    string tipo_fruta = pedidosMinorista.tope()->getTipoFruta();
    cout << "\nNOMBRE CLIENTE: " << nombreCliente
         << "\nTIPO CLIENTE: " << tipoCliente << "\nCANTIDAD " << tipoCliente
         << " DE FRUTA " << tipo_fruta << ": " << cantidad_fruta << endl;
    aux.encolar(pedidosMinorista.tope());
    pedidosMinorista.desencolar();
  }
  pedidosMinorista = aux;

  Cola<Pedidos *> aux2;

  while (!pedidosMayorista.colavacia()) {
    string nombreCliente = pedidosMayorista.tope()->getNombreCliente();
    string tipoCliente = pedidosMayorista.tope()->getTipoCliente();
    int cantidad_fruta = pedidosMayorista.tope()->getCantidadPedido();
    string tipo_fruta = pedidosMayorista.tope()->getTipoFruta();
    cout << "\nNOMBRE CLIENTE: " << nombreCliente
         << "\nTIPO CLIENTE: " << tipoCliente << "\nCANTIDAD " << tipoCliente
         << " DE FRUTA " << tipo_fruta << ": " << cantidad_fruta << endl;
    aux2.encolar(pedidosMayorista.tope());
    pedidosMayorista.desencolar();
  }
  pedidosMayorista = aux2;
}*/
/*
void GestionPedidos::stockActual() {
  cout << "\n--------------------------------------------";
  cout << "\nCANTIDAD DE FRUTA DULCE (EN KG): "
       << this->stockDisponible->getCantDulce();
  cout << "\nCANTIDAD DE FRUTA ACIDA (EN KG): "
       << this->stockDisponible->getCantAcida();
  cout << "\nCANTIDAD DE FRUTA NEUTRA (EN KG): "
       << this->stockDisponible->getCantNeutra();
  cout << "\n--------------------------------------------" << endl;
}*/

int main() {

  Seccion *seccion_dulce = new Seccion("Dulce");
  Seccion *seccion_acida = new Seccion("Acida");
  Seccion *seccion_neutra = new Seccion("Neutra");

  seccion_dulce->agregarFruta(80);
  seccion_acida->agregarFruta(100);
  seccion_neutra->agregarFruta(120);

  cout << "\n--------------------------------------------";
  cout << "\nCANTIDAD DE FRUTA DULCE (EN KG): "
       << seccion_dulce->getCantFruta();
  cout << "\nCANTIDAD DE FRUTA ACIDA (EN KG): "
       << seccion_acida->getCantFruta();
  cout << "\nCANTIDAD DE FRUTA NEUTRA (EN KG): "
       << seccion_neutra->getCantFruta();
  cout << "\n--------------------------------------------" << endl;
  /*
  pedidos->registrarPedido("Rodrigo", "Minorista", "Acida", 50);
  pedidos->registrarPedido("Emiliano", "Mayorista", "Dulce", 2);
  pedidos->registrarPedido("Jose", "Mayorista", "Acida", 3);
  pedidos->registrarPedido("Simon", "Minorista", "Dulce", 60);
  pedidos->registrarPedido("Anibal", "Minorista", "Neutra", 80);
  */
  // CANT DULCE = 80 KG - 60  = 20
  // CANT ACIDA = 100KG - 50 = 50
  // CANT NEUTRA = 120 KG - 80 = 40

  
/*
pedidos->entregarPedido(0);
  pedidos->ImpreEstado();
  pedidos->stockActual();

  seccion_dulce->agregarFruta(30); // DULCE = 50 KG
  seccion_acida->agregarFruta(10); // ACIDA = 55 KG

  pedidos->imprimirPedidos();
  pedidos->entregarPedido(0);
  pedidos->stockActual();

  pedidos->entregarPedido(1);
  pedidos->ImpreEstado();

  cout << "4--------------------------------------------" << endl;
  cout << "\nCANT INICIAL DE FRUTA DULCE: " << deposito->getCantDulce();
  cout << "\nCANT INICIAL DE FRUTA ACIDA: " << deposito->getCantAcida();
  cout << "\nCANT INICIAL DE FRUTA NEUTRA: " << deposito->getCantNeutra();
  cout << "\n--------------------------------------------" << endl;
*/
  return 0;
}