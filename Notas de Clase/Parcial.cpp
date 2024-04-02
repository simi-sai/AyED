#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

template <class T> class Nodo {
public:
  T dato;
  Nodo *der, *izq;
};

//-------------------------------------------------------

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
  void addOrdenado(T d) { addO(d, NULL);}        // sumar nodos a la lista Ordenados de menor a MAYOR
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

class Post {
private:
  int tipo; /// Post > Comentario > Respuesta == 2 > 1 > 0 > -1
  string titulo;
  string nombre;
  long int fecha; // int para usar el algoritmo de ordenamiento
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
  };
  Post() { ; }
  //~Post();
  string getTitulo() { return titulo; }
  string getNombre() { return nombre; }
  string getContenido() { return contenido; }
  int getTipo() { return tipo; }
  long int getFecha() { return fecha; }
  int getRating() { return rating; }
  int getIdPost() { return this->idPost; }
  int getIdRespuesta() { return this->idRespuesta; }
  int getIdComentario() { return this->idComentario; }
  int getParticipaciones(){return participaciones;}
  void setParticipaciones(int s){participaciones+=s;}
  void setTitulo(string s) { titulo = s; }
  void setFecha(long int n) { fecha = n; }
  void setContenido(string s) { contenido = s; }
  void setRating(int r) { rating = r; }
  void setTipo(int r) { tipo = r; }
  void setIdPost(int n) { this->idPost = n; }
  void setIdComentario(int n) { this->idComentario = n; }
  void setIdRespuesta(int n) { this->idRespuesta = n; }
};

class Arbol {
private:
  Nodo<Post> *raiz, *q;
  Cola<Post> colaaux;
  int Promedio = 0;
  //string participe;
  int MAXRating = 0;
  int idMaxRat = 0;
  int Veces = 0;
  string Participe = NULL;
  void ArbolBusq(Post x, Nodo<Post> *&nuevo);
  void show(Nodo<Post> *aux, int n);
  void borrar(Nodo<Post> *&p, int id);
  int participar(Nodo<Post> *&aux, Post &p);
  void listar(Nodo<Post> *&aux, int id); //met priv para encolar comentarios de un post
  void VotacionAux(Nodo<Post> *&aux, int post, int com, int voto);
  void Stats(Nodo<Post> *&aux, int post);
  bool EsVacio(Nodo<Post> *&aux) {return aux == NULL;}
  int part(Nodo<Post> *&aux,string nombre,int post);  //intento participacion

public:
  Arbol() { raiz = NULL; };
  ~Arbol(){};
  void CreaArbolBus(Post x) { ArbolBusq(x, raiz); }
  void VerArbol() { show(raiz, 0); }
  void Borrar(int idp) { borrar(raiz, idp);}
  void ListarA(int idp){listar(raiz,idp);}
  void MostrarLista();
  int EncontrarID(int id);
  void Votacion(int post, int com, int vot){VotacionAux(raiz,post,com,vot);}
  void Estadisticas(int post){Stats(raiz,post);}
  int Participaciones(Post p){return participar(raiz,p);}
  bool arbol_vacio(){return EsVacio(raiz);}
  int MAXParticipe(string nombre,int i){return part(raiz,nombre,i);}
};

void Arbol::show(Nodo<Post> *aux, int n) {
  int id;

  if (aux != NULL) { // OjO este es un recorrido dri
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

int Arbol::part(Nodo<Post> *&aux,string nombre, int post){
  if(aux->dato.getTipo() != 2){
    if(aux->dato.getIdPost() != post){
      return part(aux->der,nombre,post);
    } else {
      return part(aux->izq,nombre,post);
    }
  } else {
    if(aux->der != NULL){
      if(aux->dato.getNombre() != nombre){
        return part(aux->der,nombre,post);
      } else {
        return 1 + part(aux->der,nombre,post);
      }
    } else {
      if(aux->dato.getNombre() != nombre){
        return 0;
      } else {
        return 1;
      }
    }
  }
}

void Arbol::ArbolBusq(Post x, Nodo<Post> *&nuevo) {
  if (nuevo == NULL) {
    nuevo = new Nodo<Post>;
    nuevo->dato = x;
    nuevo->der = nuevo->izq = NULL;
    Participaciones(nuevo->dato);
  } else {
    // Comparar el tipo para determinar la prioridad
    if (x.getTipo() == 2) {
      ArbolBusq(x, nuevo->der);
    }

    if (x.getTipo() == 1) {
      if (nuevo->dato.getTipo() == 2) {
        if (x.getIdPost() == nuevo->dato.getIdPost())
          ArbolBusq(x, nuevo->izq);
        else
          ArbolBusq(x, nuevo->der);
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
        else {
          ArbolBusq(x, nuevo->der);
        }
      } else if (nuevo->dato.getTipo() == 0) {
        if (x.getIdRespuesta() > nuevo->dato.getIdRespuesta())
          ArbolBusq(x, nuevo->der);
      }
    }
  }
}

void Arbol::borrar(Nodo<Post> *&aux, int idp) {
  bool proseguir = true;

  if (aux != NULL && proseguir) {
    q = aux;

    if (aux->dato.getTipo() == 2) {
      if (aux->dato.getIdPost() != idp) {
        borrar(aux->der, idp);
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

void Arbol::listar(Nodo<Post> *&aux, int idp) {
  if(!arbol_vacio()){
    if(aux->dato.getTipo() == 2){    //Si estoy recorriendo posts
      if(aux->dato.getIdPost() != idp && aux->der != NULL){
        listar(aux->der,idp);
      } else if(aux->dato.getIdPost() != idp && aux->der == NULL){
        cout << "El ID: " << idp << " no pertenece a ningun POST en el foro" << endl;
      } else {
        colaaux.encolar(aux->dato);
        if(aux->izq != NULL)
          listar(aux->izq,idp);
        else
          cout << "\nEl post -" << aux->dato.getTitulo() << "- no posee comentarios al momento" << endl;
      }
    } else {  //Si estoy recorriendo comentarios
      if(aux->der != NULL){
        colaaux.encolar(aux->dato);
        listar(aux->der,idp);
      } else {
        colaaux.encolar(aux->dato);
        MostrarLista();
      }
    }
    
  }
}

void Arbol::MostrarLista(){
  Cola<Post> aux = colaaux;

  while(!aux.colavacia())
  {
    if(aux.tope().getTipo() == 2)
      cout << "Post: " << aux.tope().getTitulo() << "\nComentarios:" << endl;
    if(aux.tope().getTipo() == 1)
      cout << aux.tope().getNombre() << endl;
    aux.desencolar();
  }
}

/*int Arbol::EncontrarID(int id){
  Cola<Post> aux = colaaux;
  int aux2 = id+1;
  while(!aux.colavacia() && aux2 >= 0){
    aux.desencolar();
    aux2--;
  }
  return aux.tope().getIdComentario(); 
}*/

void Arbol::VotacionAux(Nodo<Post>* &nodo,int post, int com, int voto) {
  
if (nodo->dato.getTipo() == 2){ 
  if(post != nodo->dato.getIdPost()){
     VotacionAux(nodo->der,post,com,voto);
   } else {
     if(com == 0){
       if (voto == 1){
         nodo->dato.setRating(nodo->dato.getRating()+1);
       } else {
         nodo->dato.setRating(nodo->dato.getRating()-1);      
       }
         
     } else {
       VotacionAux(nodo->izq,post,com,voto);
     }
   }
  }
  else if (nodo->dato.getTipo() == 1){
    if(com != nodo->dato.getIdComentario()){
      VotacionAux(nodo->der,post,com,voto);
    } else {
        if (voto == 1){
          nodo->dato.setRating(nodo->dato.getRating()+1);
        } else {
          nodo->dato.setRating(nodo->dato.getRating()-1);
        }
    }
  }
}

void Arbol::Stats(Nodo<Post> *&aux,int post) {
  
  if(aux->dato.getTipo() == 2){
    if(aux->dato.getIdPost() != post){
      Stats(aux->der,post);
    } else {
      if(aux->izq != NULL){
        Promedio += aux->dato.getRating();  //sumo la votacion del Post
        Stats(aux->izq,post);
      } else {
        cout << "El post no tiene comentarios" << endl;
      }
    }
  } else {
    if(aux->der != NULL){
      Promedio += aux->dato.getRating();
      if(MAXRating < aux->dato.getRating()){
        MAXRating = aux->dato.getRating();
        idMaxRat = aux->dato.getIdComentario();
      }
      int MAX = MAXParticipe(aux->dato.getNombre(),post);
      if(Veces < MAX){
        Veces = MAX;
        Participe = aux->dato.getNombre();
      }
      Stats(aux->der,post);
    } else {
      Promedio += aux->dato.getRating();
      if(MAXRating < aux->dato.getRating()){
        MAXRating = aux->dato.getRating();
        idMaxRat = aux->dato.getIdComentario();
      }
      int MAX = MAXParticipe(aux->dato.getNombre(),aux->dato.getIdPost());
      if(Veces < MAX){
        Veces = MAX;
        Participe = aux->dato.getNombre();
      }
      
      if(idMaxRat != 0){
      cout << "El comentario con mejor votacion es el " << idMaxRat << " con " << MAXRating << " votos." << endl;
      } else {
        cout << "Todos los comentarios tienen el mismo rating" << endl;
      }
      cout << "La cantidad total de votos es " << Promedio << endl;
      if(Veces > 1){
        cout << "\nEl usuario que mas veces participo es " << Participe << " con un total de " << Veces << "comentarios en el mismo post" << endl;
      } else {
        cout << "\nNo hubo usuarios con mas de 1 participacion en este post" << endl;
      }
    }
  }
}

int Arbol::participar(Nodo<Post>*&nodo , Post &post) { // no se si anda
  string nombre_participante = post.getNombre();
  
if (nodo != NULL){
  if (nodo->dato.getTipo()==2){
    if (nodo->dato.getIdPost() != post.getIdPost()){
      participar(nodo->der,post);
    } else{
      if (nodo->izq == NULL){
        if (nodo->dato.getNombre() == nombre_participante)
          post.setParticipaciones(1);
      } else {
        if (nodo->dato.getNombre() == nombre_participante)
          post.setParticipaciones(1);
        
          participar(nodo->izq,post);
      }
    }    
  } else if (nodo->dato.getTipo() == 1) {
    if (nodo->izq == NULL && nodo->der == NULL){
        if (nodo->dato.getNombre()==nombre_participante)
          post.setParticipaciones(1);
    } else if (nodo->izq == NULL) {
        if (nodo->dato.getNombre()==nombre_participante)
          post.setParticipaciones(1);
          participar(nodo->der,post);
    } else {
        if (nodo->dato.getNombre()==nombre_participante)
          post.setParticipaciones(1);
          participar(nodo->izq,post);
    }
      
  } else if (nodo->dato.getTipo() == 0) {
    if (nodo->der == NULL){
      if (nodo->dato.getNombre()==nombre_participante)
          post.setParticipaciones(1);
    } else {
      if (nodo->dato.getNombre()==nombre_participante)
          post.setParticipaciones(1);
          participar(nodo->der,post);
    }
  }
}
  
  return post.getParticipaciones();
     
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class GestionPost {
private:
  Arbol arbol_post;
  int idPost;
  int idComentario;
  int idRespuesta;

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
  bool arbolVacio() {return arbol_post.arbol_vacio();}
  void MostrarPosts() { arbol_post.VerArbol(); }
  void BorrarPost(int idp) { arbol_post.Borrar(idp); }
  void ListarComentarios(int idp) { arbol_post.ListarA(idp); }
  int encontrarId(int id) { return arbol_post.EncontrarID(id);}
  void Votar();
  void VotarAux(int post, int com, int voto){arbol_post.Votacion(post,com,voto);}
  void EstadisticasPost(int post){arbol_post.Estadisticas(post);}
  
};

void GestionPost::Votar(){
  int post = 0, com = 0, aux = 0, vot=0;
  cout << "\nQue desea votar? \n[Presione 0 para un Post o 1 para un Comentario]" << endl;
  cin >> aux;
  //cin.ignore();
  cout << "De que post desea votar?" << endl;
  cin >> post;
  if (aux==1){
  cout << "Que Comentario desea votar del post " << post << "?" << endl;
  cin >> com;
  }
  cout << "¿Desea votar negativa o positivamente? \n[1 es positivo y 0 es negativo]\n";
  cin >> vot;
  this->VotarAux(post,com,vot);
}

void GestionPost::Menu() { // andando
  int proseguir = 2;
  int opcion;
  int idp, idc;
  string titulo, nombre, contenido;
  
  if (arbolVacio()) {
    proseguir = 0;
    cout << "----------------------------------------------------------------"
            "\n\n";
    cout
        << "             NO HAY POST's SUBIDOS HASTA EL MOMENTO           \n\n";
    cout << "----------------------------------------------------------------"
            "\n\n";
    cout << "     ¿DESEA AGREGAR UN POST NUEVO? ESCRIBA '1' EN EL CASO DE SI:";
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
    cout << "0. Salir\n" << endl;
    cout << "Ingrese su opción: ";
    cin >> opcion;
    cout << endl;
    
    if (opcion < 0 || opcion > 3) {
      cout << "INGRESE UNA OPCION VALIDA [0 || 1 || 2 || 3] y vuelva a "
              "intentarlo\n\n";
      continue;
    }
    if (opcion == 1) {
      
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "TITULO: ";
      getline(cin, titulo);
      

      cout << "NOMBRE: ";
      getline(cin,nombre);
      

      cout << "CONTENIDO: ";
      getline(cin,contenido);
      
      agregarPost(titulo, nombre, contenido);
      continue;

    } else if (opcion == 2) {
      int aux = 0;
      
      cout << "INGRESE EL NUMERO DEL POST A COMENTAR: ";
      cin >> aux;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "NOMBRE: ";
      getline(cin,nombre);
      
      cout << "CONTENIDO: ";
      getline(cin,contenido);
      
      agregarComentario(aux, nombre, contenido);
      continue;
      
    } else if (opcion == 3) {
      int idp, idc = 0;
      
      cout << "INGRESE EL NUMERO DEL POST Y SU COMENTARIO A RESPONDER: ";
      cin >> idp;
      cin.ignore();
      cin >> idc;
    
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "NOMBRE: ";
      getline(cin,nombre);
    
      cout << "CONTENIDO: ";
      getline(cin,contenido);
      
      agregarRespuesta(idc,idp , nombre, contenido);
      continue;
      
    } else {
      proseguir = 0;
    }
  }
  }
 
}

void GestionPost::agregarPost(string titulo, string nombre, string contenido) {
  Post post_nuevo = Post(titulo, nombre, contenido);
  this->idPost++;
  post_nuevo.setIdPost(idPost);
  post_nuevo.setIdComentario(0);
  post_nuevo.setIdRespuesta(0);
  post_nuevo.setTipo(2);
  arbol_post.CreaArbolBus(post_nuevo);
}

void GestionPost::agregarComentario(int idp, string nombre, string contenido) {
  Post post_nuevo = Post(" ", nombre, contenido);
  this->idComentario++;
  post_nuevo.setIdComentario(idComentario);
  post_nuevo.setIdPost(idp);
  post_nuevo.setTipo(1);
  arbol_post.CreaArbolBus(post_nuevo);
}

void GestionPost::agregarRespuesta(int idc, int idp, string nombre, string contenido) {
  Post post_nuevo = Post(" ", nombre, contenido);
  this->idRespuesta++;
  post_nuevo.setIdRespuesta(idRespuesta);
  post_nuevo.setIdComentario(idc);
  post_nuevo.setIdPost(idp);
  post_nuevo.setTipo(0);
  arbol_post.CreaArbolBus(post_nuevo);
}

/*
void GestionPost:: Menu(){
  string aux = NULL;
  string nombre = NULL;
  string contenido = NULL;
  int aux2 = 0;
  int aux3 = 0;
  cout << "\nBienvenido a AyEDdit" << endl;
  cout << "Que desea hacer?" << endl;
  cin >> aux;

  if(aux == "responder"){
    cout << "\nDe que post desea hacer la respuesta?" << endl;
    cin >> aux2;
    MostrarLista(aux2);
    cout << "\nA que comentario desea responder?" << endl;
    cin >> aux3;
    cout << "Cual es su nombre?" << endl;
    cin >> nombre;
    cout << "Cual es la respuesta?" << endl;
    cin >> contenido;
    //agregarRespuesta(encontrarId(aux3),aux2,nombre,contenido);
    cout << "Respuesta Agregada" << endl;
  }
}*/

//-------------------------------------------------------

int main() {
  GestionPost* gestionPost = new GestionPost();
  //gestionPost->Menu();
  //gestionPost->MostrarPosts();
  //gestionPost->MostrarPosts();
  
  gestionPost->agregarPost("MI PRIMER POST - TEORIA DE REDES", "Rodrigo",
                          "POST 1"); //
  gestionPost->agregarPost("MI SEGUNDO POST", "Simon", "POST 2");
  gestionPost->agregarComentario(1, "Manolito", "Comentario al POST 1"); // COM 1
  gestionPost->agregarComentario(2, "Anibal", "Comentario al POST 2");   // COM2
  gestionPost->agregarComentario(1, "Manolito", "Comentario al POST 1");  //
  gestionPost->agregarRespuesta(
      3, 1, "Laura", "Respuesta al comentario 1 del post 1");       // RESP 1
  gestionPost->agregarComentario(2, "Jose", "Comentario al POST 2"); // COM 4
  gestionPost->agregarComentario(2, "Raul", "Comentario al POST 2"); // COM5
  gestionPost->agregarPost("ASDSAAD", "Ramiro", "POST 3");
  gestionPost->agregarComentario(3, "Samira", "Comentario al POST 3"); // COM 6
  // gestionPost.agregarComentario(1, "Nicolas", "Comentario al post1");
  // gestionPost.agregarComentario(1, "Lautaro", "Comentario al Post1");
  gestionPost->agregarComentario(3, "Jessica", "Comentario Post 3");
  gestionPost->agregarPost("", "Christian", "blabla");
  gestionPost->agregarComentario(4, "Hugo", "Comentario Post 4");
  gestionPost->agregarComentario(4, "Roberto", "Comentario Post 4");
  // gestionPost.agregarRespuesta(4, 1, "Lola", "Respuest al comentario 2 del
  // post 1");
  gestionPost->agregarRespuesta(6, 3, "Ricardo",
                               "Respuest al comentario 2 del post 1");
  gestionPost->agregarRespuesta(2, 2, "Pedro",
                               "Respuest al comentario 2 del post 1");
  gestionPost->agregarRespuesta(2, 2, "Anuel",
                               "Respuest al comentario 2 del post 3");
  gestionPost->agregarRespuesta(7, 3, "Marco",
                               "Respuest al comentario 3 del post 1");
  gestionPost->agregarPost("POST 6", "Gonzalo", "blabla");

  gestionPost->MostrarPosts();
  //gestionPost->Votar();
  //gestionPost->Votar();
  //gestionPost->Votar();
  gestionPost->EstadisticasPost(1);

  //gestionPost.MostrarPosts();
  /*
  cout << "------------------ARBOL ANTES DEL BORRADO------------\n\n\n\n";

  gestionPost.BorrarPost(1);
  gestionPost.MostrarPosts();
  cout << "------------------ARBOL DESPUES DEL BORRADO------------\n\n\n\n";

  gestionPost.BorrarPost(2);
  gestionPost.MostrarPosts();
  cout << "------------------ARBOL DESPUES DEL BORRADO------------\n\n\n\n";

  gestionPost.BorrarPost(3);
  gestionPost.MostrarPosts();
  cout << "------------------ARBOL DESPUES DEL BORRADO------------\n\n\n\n";

  gestionPost.BorrarPost(4);
  gestionPost.MostrarPosts();
  cout << "------------------ARBOL DESPUES DEL BORRADO------------\n\n\n\n";
  */
  return 0;
}