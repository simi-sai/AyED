#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <string>
#define MAXIMO 150

using namespace std;

template <class T> class Nodo {
public:
  T dato;
  Nodo *der, *izq;
};

template <class T> class Nodo2 {
private:
  T dato;
  Nodo2 *next;

public:
  Nodo2() { next = NULL; };
  Nodo2(T a) {
    dato = a;
    next = NULL;
  };
  void set_dato(T a) { dato = a; };
  void set_next(Nodo2 *n) { next = n; };
  T get_dato() { return dato; };
  Nodo2 *get_next() { return next; };
  bool es_vacio() { return next == NULL; }
};

//-------------------------------------------------------

template <class T> class Lista {
private:
  Nodo2<T> *czo;
  void addO(T d, Nodo2<T> *ant);
  void borrarD(T d, Nodo2<T> *ant);

public:
  Lista() { czo = new Nodo2<T>(); };
  Lista(Nodo2<T> *n) { czo = n; };
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
  }         // sumar nodos a la lista Ordenados de menor a MAYOR
  T last(); // retorna el dato del ultimo nodo
};

template <class T> T Lista<T>::last() {
  if (this->resto()->esvacia())
    return this->cabeza();
  else
    return this->resto()->last();
}

template <class T> void Lista<T>::add(T d) {
  Nodo2<T> *nuevo = new Nodo2<T>(d);
  nuevo->set_next(czo);
  czo = nuevo;
}

template <class T> bool Lista<T>::esvacia(void) { return czo->es_vacio(); }

template <class T> T Lista<T>::cabeza(void) {
  if (this->esvacia()) {
    cout << " Error, Cabeza de lista vacia";
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
    Nodo2<T> *tmp = czo;
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

template <class T> void Lista<T>::concat(Lista<T> *l1) { // le transfiere los datos de l1 a this
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

template <class T> void Lista<T>::tomar(int n) { // deja "vivos" los n primeros nodos y borra el resto
  if (this->size() > n) {
    this->borrar_last();
    this->tomar(n);
  }
}

template <class T> void Lista<T>::impre(void) {
  Nodo2<T> *aux;
  aux = czo;
  while (aux->get_next() != NULL) {
    cout << aux->get_dato() << endl;
    aux = aux->get_next();
  }
}

template <class T> void Lista<T>::addO(T d, Nodo2<T> *ant) {
  if (this->esvacia()) { // el primero
    this->add(d);
  } else {
    if (d < czo->get_dato()) {
      if (ant == NULL) { // al principio
        this->add(d);
      } else { // entre medio
        Nodo2<T> *nuevo = new Nodo2<T>(d);
        nuevo->set_next(ant->get_next());
        ant->set_next(nuevo);
      }
    } else {
      if ((czo->get_next())->get_next() == NULL) { // al final
        Nodo2<T> *nuevo = new Nodo2<T>(d);
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

template <class T> void Lista<T>::borrarD(T d, Nodo2<T> *ant) {
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

//-------------------------------------------------------

template <class T> class Cola : public Lista<T> {
public:
  Cola(void) { Lista<T>(); }
  //~Cola(void);
  T tope() { return this->last(); }
  bool colavacia(void) { return this->esvacia(); }
  void encolar(T a) { this->add(a); }
  void desencolar(void) { this->borrar_last(); }
  T ultimo(void) { return this->cabeza(); }
  string imprimir(string s) { return this->toPrint(s); }
  int sizeCola() {
    if (this->esvacia())
      return 0;
    return 1 + this->resto()->size();
  }
};

//-------------------------------------------------------

class Tiempo { // Puede ocurrir que al agregar forzosamente en main()
               // post/com/res no se guarde correctamente la hora.
private:
  time_t currentTime;
  tm *localTime;
  int anio;
  int mes;
  int dia;
  int hora;
  int min;
  int sec;
  double suma;

public:
  Tiempo() {
    currentTime = time(nullptr);
    localTime = localtime(&currentTime);
    anio = localTime->tm_year + 1900; // Years since 1900
    mes = localTime->tm_mon + 1;      // Months since January (0-11)
    dia = localTime->tm_mday;         // Day of the month (1-31)
    hora = localTime->tm_hour;
    min = localTime->tm_min;
    sec = localTime->tm_sec;
    suma = anio + mes + dia + (hora-3) * 3600 + min * 60 + sec;
  }
  int getAnio() { return anio; }
  int getMes() { return mes; }
  int getDia() { return dia; }
  int getHora() { return hora; }
  int getMin() { return min; }
  int getSec() { return sec; }
  double getSuma() { return suma; }
};

//-------------------------------------------------------

class Post {
private:
  int tipo; // Post > Comentario > Respuesta == 2 > 1 > 0 
  string titulo;
  string nombre;
  Tiempo t;
  string contenido;
  int rating;
  int idPost;
  int idComentario;
  int idRespuesta;
  int participaciones;

public:
  Post(string titulo, string nombre, string contenido) {
    this->titulo = titulo;
    this->nombre = nombre;
    this->contenido = contenido;
    this->idPost = 0;
    this->idComentario = 0;
    this->idRespuesta = 0;
    this->rating = 0;
    this->participaciones = 0;
    this->t = Tiempo();
  }
  Post() { ; }
  //~Post();
  string getTitulo() { return titulo; }
  string getNombre() { return nombre; }
  string getContenido() { return contenido; }
  int getTipo() { return tipo; }
  int getRating() { return rating; }
  int getIdPost() { return this->idPost; }
  int getIdRespuesta() { return this->idRespuesta; }
  int getIdComentario() { return this->idComentario; }
  int getParticipaciones() { return participaciones; }
  Tiempo getTiempo() { return t; }
  void setParticipaciones(int s) { participaciones += s; }
  void setTitulo(string s) { titulo = s; }
  void setContenido(string s) { contenido = s; }
  void setRating(int r) { rating = r; }
  void setTipo(int r) { tipo = r; }
  void setIdPost(int n) { this->idPost = n; }
  void setIdComentario(int n) { this->idComentario = n; }
  void setIdRespuesta(int n) { this->idRespuesta = n; }
};

//-------------------------------------------------------

class Arbol {
private:
  Nodo<Post> *raiz, *q;
  Cola<Post> colaaux;
  Cola<Post> colaFinal;
  int Promedio = 0;
  int MAXRating = 0;
  int idMaxRat = 0;
  int Veces = 0;
  string Participe;
  void ArbolBusq(Post x, Nodo<Post> *&nuevo);
  void show(Nodo<Post> *aux, int n);
  void borrar(Nodo<Post> *&p, int id);
  void listar(Nodo<Post> *&aux, int id, int tipo);
  void VotacionAux(Nodo<Post> *&aux, int post, int com, int voto);
  void Stats(Nodo<Post> *&aux, int post);
  bool EsVacio(Nodo<Post> *&aux) { return aux == NULL; }
  int part(Nodo<Post> *&aux, string nombre, int post);
  void colasTotales(Nodo<Post> *&aux);

public:
  Arbol() { raiz = NULL; };
  //~Arbol();
  void CreaArbolBus(Post x) { ArbolBusq(x, raiz); }
  void VerArbol() { show(raiz, 0); }
  void Borrar(int idp) { borrar(raiz, idp); }
  void ListarA(int idp, int tipo) { listar(raiz,idp,tipo); }
  void MostrarLista();
  void Votacion(int post, int com, int vot) { VotacionAux(raiz, post, com, vot); }
  void Estadisticas(int post) {
    this->Veces = 0;
    Stats(raiz, post);
  }
  bool arbol_vacio() { return EsVacio(raiz); }
  int MAXParticipe(string nombre, int i) { return part(raiz, nombre, i); }
  Cola<Post> cola_Final() {
    colasTotales(raiz);
    return colaFinal;
  }
};

// Metodo de muestra del arbol
void Arbol::show(Nodo<Post> *aux, int n) {
  if (!arbol_vacio()) {
    if (aux != NULL) {
      show(aux->der, n + 1);
      for (int i = 1; i <= n; i++)
        cout << "     ";
      if (aux->dato.getTipo() == 2)
        cout << aux->dato.getNombre() << "[P " << aux->dato.getIdPost()
             << "]   \n";
      else if (aux->dato.getTipo() == 1)
        cout << aux->dato.getNombre() << "[C " << aux->dato.getIdComentario()
             << "]  \n";
      else if (aux->dato.getTipo() == 0)
        cout << aux->dato.getNombre() << "[r]   \n";
      show(aux->izq, n + 1);
    }
  }
}

// Calcula la participacion de un usuario en el mismo post
int Arbol::part(Nodo<Post> *&aux, string nombre, int post) {
  if (aux->dato.getTipo() == 2) {
    if (aux->dato.getIdPost() != post) {
      return part(aux->der, nombre, post);
    } else {
      return part(aux->izq, nombre, post);
    }
  } else {
    if (aux->der != NULL) {
      if (aux->dato.getNombre() != nombre) {
        return part(aux->der, nombre, post);
      } else {
        return 1 + part(aux->der, nombre, post);
      }
    } else {
      if (aux->dato.getNombre() != nombre) {
        return 0;
      } else {
        return 1;
      }
    }
  }
}

// Metodo usado para generar el arbol
void Arbol::ArbolBusq(Post x, Nodo<Post> *&nuevo) {
  if (nuevo == NULL) {
    nuevo = new Nodo<Post>;
    nuevo->dato = x;
    nuevo->der = nuevo->izq = NULL;
  } else {
    // Comparar el tipo para determinar la prioridad
    if (x.getTipo() == 2) {
      ArbolBusq(x, nuevo->der);
    }

    if (x.getTipo() == 1) {
      if (nuevo->dato.getTipo() == 2) {
        if (x.getIdPost() == nuevo->dato.getIdPost()) {
          ArbolBusq(x, nuevo->izq);
        } else {
          if (nuevo->der == NULL && x.getIdPost() != nuevo->dato.getIdPost())
            cout << "\nNo existe el post al que desea comentar o fue eliminado"
                 << endl;
          else
            ArbolBusq(x, nuevo->der);
        }
      } else if (nuevo->dato.getTipo() == 1) {
        if (x.getIdComentario() != nuevo->dato.getIdComentario())
          ArbolBusq(x, nuevo->der);
      }
    }

    if (x.getTipo() == 0) {
      if (nuevo->dato.getTipo() == 2) {
        if (x.getIdPost() == nuevo->dato.getIdPost())
          ArbolBusq(x, nuevo->izq);
        else
          ArbolBusq(x, nuevo->der);
      } else if (nuevo->dato.getTipo() == 1) {
        if (x.getIdComentario() == nuevo->dato.getIdComentario())
          ArbolBusq(x, nuevo->izq);
        else if (nuevo->der == NULL &&
                 nuevo->dato.getIdComentario() != x.getIdComentario()) {
          cout << "\nNo se encuentra o no existe el comentario "
               << x.getIdComentario() << " en este Post" << endl;
        } else {
          ArbolBusq(x, nuevo->der);
        }
      } else if (nuevo->dato.getTipo() == 0) {
        if (x.getIdRespuesta() > nuevo->dato.getIdRespuesta())
          ArbolBusq(x, nuevo->der);
      }
    }
  }
}

// Metodo usado para borrar un "post" del arbol
void Arbol::borrar(Nodo<Post> *&aux, int idp) {
  bool proseguir = true;

  if (aux != NULL && proseguir) {
    q = aux;

    if (aux->dato.getTipo() == 2) {
      if (aux->dato.getIdPost() != idp && aux->der != NULL) {
        borrar(aux->der, idp);
      } else if (aux->dato.getIdPost() != idp && aux->der == NULL) {
        cout << "El post seleccionado no existe o no se encuentra" << endl;
      } else {
        if (aux->izq == NULL) {
          aux = aux->der;
          delete q;
        } else {
          borrar(aux->izq, idp);
        }
      }
      proseguir = false;
    } else if (aux->dato.getTipo() == 1) {
      if (aux->izq == NULL && aux->der == NULL) {
        aux = NULL;
        delete q;
      } else if (aux->izq == NULL) {
        aux = aux->der;
        delete q;
        borrar(aux, idp);
      } else {
        aux = aux->izq;
        delete q;
        borrar(aux, idp);
      }
    } else if (aux->dato.getTipo() == 0) {
      if (aux->der == NULL) {
        aux = NULL;
        delete q;
      } else {
        borrar(aux->der, idp);
      }
    }
  }

  if (proseguir == false) {
    q = aux;
    if (aux->dato.getTipo() == 2) {
      if (aux->dato.getIdPost() == idp) {
        aux = aux->der;
        delete q;
      }
    }
  }
}

// Metodo usado para hacer una cola con todos los comentarios de c/post
void Arbol::listar(Nodo<Post> *&aux, int idp,int tipo) {
  if (!arbol_vacio()) {
    if (aux->dato.getTipo() == 2) { // Si estoy recorriendo posts
      if (aux->dato.getIdPost() != idp && aux->der != NULL) {
        listar(aux->der, idp,tipo);
      } else if (aux->dato.getIdPost() != idp && aux->der == NULL) {
        cout << "El ID: " << idp << " no pertenece a ningun POST en el foro"
             << endl;
      } else {
        if(tipo == 0)
        colaaux.encolar(aux->dato);
        if (aux->izq != NULL)
          listar(aux->izq, idp,tipo);
        else
          cout << "\nEl post -" << aux->dato.getTitulo()
               << "- no posee comentarios al momento" << endl;
      }
    } else { // Si estoy recorriendo comentarios
      if (aux->der != NULL) {
        if(tipo == 0)
        colaaux.encolar(aux->dato);
        else
        colaFinal.encolar(aux->dato);
        listar(aux->der, idp,tipo);
      } else {
        if(tipo == 0)
        colaaux.encolar(aux->dato);
        else
        colaFinal.encolar(aux->dato);
      }
    }
  }
}

// Metodo para mostrar un Post con sus comentarios
void Arbol::MostrarLista() {
  Cola<Post> aux = colaaux;
  cout << "\n-------------------------------" << endl;
  while (!aux.colavacia()) {
    if (aux.tope().getTipo() == 2) {
      cout << "\nPost N°" << aux.tope().getIdPost()
           << "\n  Titulo: " << aux.tope().getTitulo()
           << "\n  Autor: " << aux.tope().getNombre()
           << "\n  Votos: " << aux.tope().getRating()
           << "\n  Contenido: " << aux.tope().getContenido()
           << "\n  Comentarios:" << endl;
    }
    if (aux.tope().getTipo() == 1) {
      cout << "\n    "
           << "Usuario: " << aux.tope().getNombre() << "\n        "
           << aux.tope().getContenido() << "\n        "
           << aux.tope().getTiempo().getHora() << ":"
           << aux.tope().getTiempo().getMin() << " - " << aux.tope().getRating()
           << " votos " << endl;
    }
    aux.desencolar();
  }
  cout << "\n-------------------------------" << endl;
}

// Este metodo genera una cola con todos los comentarios de todos los post
void Arbol::colasTotales(Nodo<Post> *&aux) {
  if (aux->der != NULL) {
    ListarA(aux->dato.getIdPost(),1);
    colasTotales(aux->der);
  } else {
    ListarA(aux->dato.getIdPost(),1);
  }
}

// Metodo para votar en un post o comentario
void Arbol::VotacionAux(Nodo<Post> *&nodo, int post, int com, int voto) {
  if (!arbol_vacio()) {
    if (nodo->dato.getTipo() == 2) {
      if (post != nodo->dato.getIdPost() && nodo->der != NULL) {
        VotacionAux(nodo->der, post, com, voto);
      } else if (post != nodo->dato.getIdPost() && nodo->der == NULL) {
        cout << "\nNo se encontro el post al que desea Votar" << endl;
      } else {
        if (com == 0) { // esto es en caso de que quiera votar un post
          if (voto == 1)
            nodo->dato.setRating(nodo->dato.getRating() + 1);
          else
            nodo->dato.setRating(nodo->dato.getRating() - 1);
        } else { // en caso de que quiera votar un comentario
          if (nodo->izq != NULL)
            VotacionAux(nodo->izq, post, com, voto);
          else
            cout << "\n El post que selecciono no tiene comentarios" << endl;
        }
      }
    } else if (nodo->dato.getTipo() == 1) {
      if (com != nodo->dato.getIdComentario() && nodo->der != NULL) {
        VotacionAux(nodo->der, post, com, voto);
      } else if (com != nodo->dato.getIdComentario() && nodo->der == NULL) {
        cout << "\nNo se encontro el comentario al que desea votar" << endl;
      } else {
        if (voto == 1)
          nodo->dato.setRating(nodo->dato.getRating() + 1);
        else
          nodo->dato.setRating(nodo->dato.getRating() - 1);
      }
    } else { // hipotetico caso de que algo haya salido mal y se haya metido a
             // una respuesta
      cout << "Oops, algo salio mal" << endl;
    }
  } else {
    cout << "\nTodavia no hay posts" << endl;
  }
}

// Metodo para calcular y mostrar las estadisticas de un post
void Arbol::Stats(Nodo<Post> *&aux, int post) {
  if (!arbol_vacio()) {
    if (aux->dato.getTipo() == 2) {
      if (aux->dato.getIdPost() != post && aux->der != NULL) {
        Stats(aux->der, post);
      } else if (aux->dato.getIdPost() != post && aux->der == NULL) {
        cout << "No se encontro el post que pidio" << endl;
      } else {
        if (aux->izq != NULL) {
          Promedio += aux->dato.getRating(); // sumo la votacion del Post
          Stats(aux->izq, post);
        } else {
          cout << "El post no tiene comentarios" << endl;
        }
      }
    } else {
      if (aux->der != NULL) {
        Promedio += aux->dato.getRating();
        if (MAXRating < aux->dato.getRating()) {
          MAXRating = aux->dato.getRating();
          idMaxRat = aux->dato.getIdComentario();
        }
        int MAX = MAXParticipe(aux->dato.getNombre(), post);
        if (Veces < MAX) {
          Veces = MAX;
          Participe = aux->dato.getNombre();
        }
        Stats(aux->der, post);
      } else {
        Promedio += aux->dato.getRating();
        if (MAXRating < aux->dato.getRating()) {
          MAXRating = aux->dato.getRating();
          idMaxRat = aux->dato.getIdComentario();
        }
        int MAX = MAXParticipe(aux->dato.getNombre(), aux->dato.getIdPost());
        if (Veces < MAX) {
          Veces = MAX;
          Participe = aux->dato.getNombre();
        }
          cout << "\n-------------------------------" << endl;
        
        if (idMaxRat != 0) {
          cout << "\nEl comentario con mejor votacion es el " << idMaxRat
               << " con " << MAXRating << " votos." << endl;
        } else {
          cout << "\nTodos los comentarios tienen el mismo rating" << endl;
        }
        cout << "\nLa cantidad total de votos es: " << Promedio << endl;
        if (Veces > 1) {
          cout << "\nEl usuario que mas veces participo es " << Participe
               << "\ncon un total de " << Veces
               << " comentarios en el mismo post" << endl;
        } else {
          cout << "\nNo hubo usuarios con mas de 1 participacion en este post"
               << endl;
        }
        cout << "\n-------------------------------" << endl;
      }
    }
  }
}

//-------------------------------------------------------

class GestionPost {
private:
  Arbol arbol_post;
  int idPost;
  int idComentario;
  int idRespuesta;
  Post arreglo[MAXIMO];
  void ordenaQS(Post v[], int primero, int ultimo);

public:
  GestionPost() {
    this->idPost = 0;
    this->idComentario = 0;
    this->idRespuesta = 0;
  }
  void agregarPost(string titulo, string nombre, string contenido);
  void agregarComentario(int idPost, string nombre, string contenido);
  void agregarRespuesta(int idComent, int idp, string n, string c);
  Arbol GetArbol() { return arbol_post; }
  void Menu();
  bool arbolVacio() { return arbol_post.arbol_vacio(); }
  void MostrarPosts() { arbol_post.VerArbol(); }
  void BorrarPost(int idp) { arbol_post.Borrar(idp); }
  void ListarComentarios(int idp) { arbol_post.ListarA(idp,0); }
  void Votar();
  void VotarAux(int post, int com, int voto) {
    arbol_post.Votacion(post, com, voto);
  }
  void EstadisticasPost(int post) { arbol_post.Estadisticas(post); }
  void MostrarLista() { arbol_post.MostrarLista(); }
  void ColaFinal();
  void ImprimirOrdenado(int n) {
    for (int i = 0; i < n; i++) {
      cout << "\nNOMBRE ORDENADO: " << arreglo[i].getNombre()
           << " FECHA ORDENADA: " << arreglo[i].getTiempo().getSuma() << "\n\n";
    }
  }
  void Participaciones(string user);
  void AbrirPost() { arbol_post.MostrarLista(); }
  void Ordenador();
};

// Metodo para mostrar la participacion en distintos post de un usuario
void GestionPost::Participaciones(string user) {
      cout << "\nUsuario: " << user
           << "\nParticipaciones en los diferentes post: \n";
  for (int i = 0; i < MAXIMO; i++) {
    if (arreglo[i].getNombre() == user) {
      cout << "  Post n°: " << arreglo[i].getIdPost()
           << "\n   Contenido: " << arreglo[i].getContenido() 
           << "\n  " << arreglo[i].getTiempo().getHora() << ":"
           << arreglo[i].getTiempo().getMin() << ":" 
           << arreglo[i].getTiempo().getSec() << " - "
           << arreglo[i].getTiempo().getDia() << "/"
           << arreglo[i].getTiempo().getMes() << endl;
    }
  }
}

// Este metodo se encarga de llamar al metodo Quick Sort con la Cola de todos
// los comentarios
void GestionPost::ColaFinal() {

  Cola<Post> aux = this->arbol_post.cola_Final();
  int size = aux.sizeCola();
  int i = 0;

  while (!aux.colavacia()) {
    arreglo[i] = aux.tope();
    cout << "\nUsuario: " << arreglo[i].getNombre()
         << " hizo un comentario en el post N°" << arreglo[i].getIdPost()
         << "\nFecha (desordenada): " << arreglo[i].getTiempo().getDia() << "/"
         << arreglo[i].getTiempo().getMes() << "/"
         << arreglo[i].getTiempo().getAnio() << "\n"
         << "Horario: " << arreglo[i].getTiempo().getHora() << ":"
         << arreglo[i].getTiempo().getMin() << ":"
         << arreglo[i].getTiempo().getSec() << endl;
    aux.desencolar();
    i++;
  }

  this->ordenaQS(arreglo, 0, size - 1);

  for (int i = 0; i < size; i++) {
    cout << "\nUsuario: " << arreglo[i].getNombre()
         << " hizo un comentario en el post n°:" << arreglo[i].getIdPost()
         << "\nFecha (ordenada): " << arreglo[i].getTiempo().getDia() << "/"
         << arreglo[i].getTiempo().getMes() << "/"
         << arreglo[i].getTiempo().getAnio() << "\n"
         << "Horario: " << arreglo[i].getTiempo().getHora() << ":"
         << arreglo[i].getTiempo().getMin() << ":"
         << arreglo[i].getTiempo().getSec() << endl;
  }
}

// Version sin cout del metodo ColaFinal()
void GestionPost::Ordenador() {

  Cola<Post> aux = this->arbol_post.cola_Final();
  int size = aux.sizeCola();
  int i = 0;

  while (!aux.colavacia()) {
    arreglo[i] = aux.tope();
    aux.desencolar();
    i++;
  }

  this->ordenaQS(arreglo, 0, size - 1);
}

// Metodo Quick Sort visto en clase
void GestionPost::ordenaQS(Post v[], int primero, int ultimo) {
  int i, j, k;
  Post pivot, aux;

  if (ultimo > primero) {
    pivot = v[ultimo];
    // printf("\n -> %d  %d <-%4i",primero,ultimo,pivot);
    i = primero - 1;
    j = ultimo;
    for (;;) {
      while (v[++i].getTiempo().getSuma() < pivot.getTiempo().getSuma())
        ;
      while (v[--j].getTiempo().getSuma() > pivot.getTiempo().getSuma())
        ;
      if (i >= j)
        break;
      aux = v[i];
      v[i] = v[j];
      v[j] = aux;
    } // fin for
    aux = v[i];
    v[i] = v[ultimo];
    v[ultimo] = aux;
    // for(k=0;k<10;k++)printf("\n a[%d]=%d",k,v[k]);
    // printf("\n ------------------------------------");
    ordenaQS(v, primero, i - 1);
    ordenaQS(v, i + 1, ultimo);
    // printf("\nRETORNO -> %d  %d <-",primero,ultimo);
  } // fin if
}

// Metodo de interfaz de usuario para Votar
void GestionPost::Votar() {
  int post = 0, com = 0, aux = 0, vot = 0;
  cout
      << "\nQue desea votar? \n[Presione 0 para un Post o 1 para un Comentario]"
      << endl;
  cin >> aux;
  // cin.ignore();
  cout << "De que post desea votar?" << endl;
  cin >> post;
  if (aux == 1) {
    cout << "Que Comentario desea votar del post " << post << "?" << endl;
    cin >> com;
  }
  cout << "¿Desea votar negativa o positivamente? \n[1 es positivo y 0 es "
          "negativo]\n";
  cin >> vot;
  this->VotarAux(post, com, vot);
}

// Metodo de interfaz de usuario para Postear/Comentar/Responder
void GestionPost::Menu() {
  int proseguir = 2;
  int opcion;
  int idp, idc;
  string titulo, nombre, contenido;

  if (arbolVacio()) {
    proseguir = 0;
    cout << "-" << setw(37) << setfill('-')  << "-" << endl;
    cout << "\nNO HAY POST's SUBIDOS HASTA EL MOMENTO\n"  << endl;
    cout << "-" << setw(37) << setfill('-')  << "-" << endl;
    cout << "¿DESEA AGREGAR UN POST NUEVO?" << endl;
    cout << "ESCRIBA '1' EN CASO DE SI: ";
    cin >> proseguir;
  }

  if (proseguir == 1) {
    while (proseguir == 1) {
      cout << endl;
      MostrarPosts();
      cout << "\n----- Red Social REDDIT-LIKE -----\n";
      cout << "1. Agregar un nuevo post\n";
      cout << "2. Agregar un nuevo comentario\n";
      cout << "3. Agregar una respuesta a un comentario\n";
      cout << "4. Votar en un Post/Comentario\n";
      cout << "5. Mostrar estadisticas de un Post\n";
      cout << "6. Borrar un post\n";
      cout << "7. Buscar comentarios de un Usuario\n";
      cout << "8. Mostrar todos los comentarios en orden\n";
      cout << "9. Abrir Post\n";
      cout << "0. Salir\n" << endl;
      cout << "Ingrese su opción: ";
      cin >> opcion;
      cout << endl;

      if (arbolVacio() && opcion == 1 || !arbolVacio()) {
        if (opcion < 0 || opcion > 9) {
          cout << "INGRESE UNA OPCION VALIDA [Entre 0 y 9] y vuelva a "
                  "intentarlo\n\n";
          continue;
        }
        if (opcion == 1) {

          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "TITULO: ";
          getline(cin, titulo);

          cout << "NOMBRE: ";
          getline(cin, nombre);

          cout << "CONTENIDO: ";
          getline(cin, contenido);

          agregarPost(titulo, nombre, contenido);
          continue;

        } else if (opcion == 2) {
          int aux = 0;

          cout << "INGRESE EL NUMERO DEL POST A COMENTAR: ";
          cin >> aux;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "NOMBRE: ";
          getline(cin, nombre);

          cout << "CONTENIDO: ";
          getline(cin, contenido);

          agregarComentario(aux, nombre, contenido);
          continue;

        } else if (opcion == 3) {
          int idp, idc = 0;

          cout << "INGRESE EL NUMERO DEL POST: " << endl;
          cin >> idp;
          cin.ignore();
          cout << "INGRESE EL NUMERO DE COMENTARIO A RESPONDER: " << endl;
          cin >> idc;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "NOMBRE: ";
          getline(cin, nombre);

          cout << "CONTENIDO: ";
          getline(cin, contenido);

          agregarRespuesta(idc, idp, nombre, contenido);
          continue;

        } else if (opcion == 4) {
          Votar();
          continue;

        } else if (opcion == 5) {
          int aux = 0;
          cout << "\nIngrese el numero del post que desea analizar" << endl;

          cin >> aux;
          EstadisticasPost(aux);
          continue;

        } else if (opcion == 6) {
          int aux2 = 0;
          cout << "\nIngrese el numero del post que desea borrar" << endl;
          cin >> aux2;

          BorrarPost(aux2);
          continue;

        } else if (opcion == 7) {
          string s;
          cout << "\nIngrese el USUARIO del cual desea ver sus comentarios"
               << endl;

          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          getline(cin, s);

          Ordenador();
          Participaciones(s);
          continue;

        } else if (opcion == 8) {
          ColaFinal();
          continue;
          
        } else if (opcion == 9) {
          int aux3;
          cout << "\nIngrese el Post que desea abrir" << endl;
          cin >> aux3;
          ListarComentarios(aux3);
          AbrirPost();
          continue;

        } else if (opcion == 0) {
          proseguir = 0;
          break;
        }
      } else if (opcion == 0) {
        proseguir = 0;
        break;
      } else {
        cout << "\n -- " << "Primero agregue un Post" << " -- " << endl;
        continue;
      }
    }
  }
}

// Metodo individual para crear Post
void GestionPost::agregarPost(string titulo, string nombre, string contenido) {
  Post post_nuevo = Post(titulo, nombre, contenido);
  this->idPost++;
  post_nuevo.setIdPost(idPost);
  post_nuevo.setIdComentario(0);
  post_nuevo.setIdRespuesta(0);
  post_nuevo.setTipo(2);
  arbol_post.CreaArbolBus(post_nuevo);
}

// Metodo individual para comentar posts
void GestionPost::agregarComentario(int idp, string nombre, string contenido) {
  Post post_nuevo = Post(" ", nombre, contenido);
  this->idComentario++;
  post_nuevo.setIdComentario(idComentario);
  post_nuevo.setIdPost(idp);
  post_nuevo.setTipo(1);
  arbol_post.CreaArbolBus(post_nuevo);
}

// Metodo individual para responder comentarios
void GestionPost::agregarRespuesta(int idc, int idp, string nombre, string contenido) {
  Post post_nuevo = Post(" ", nombre, contenido);
  this->idRespuesta++;
  post_nuevo.setIdRespuesta(idRespuesta);
  post_nuevo.setIdComentario(idc);
  post_nuevo.setIdPost(idp);
  post_nuevo.setTipo(0);
  arbol_post.CreaArbolBus(post_nuevo);
}

//-------------------------------------------------------

int main() {
  
  GestionPost *gestionPost = new GestionPost();
  gestionPost->Menu();
  
  return 0;
}