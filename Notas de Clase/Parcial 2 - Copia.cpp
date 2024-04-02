
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

template <class T> class Nodo {
public:
  T dato;
  Nodo *der, *izq;
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

public:
  Post(string titulo, string nombre, string contenido) {
    this->titulo = titulo;
    this->nombre = nombre;
    this->contenido = contenido;
    this->idPost = 0;
    this->idComentario = 0;
    this->idRespuesta = 0;
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
  void ArbolBusq(Post x, Nodo<Post> *&nuevo);
  void show(Nodo<Post> *aux, int n);
  void borrar(Nodo<Post> *&p, int id);
  void listar(Nodo<Post> *&aux, int id); //met priv para encolar comentarios de un post

public:
  Arbol() { raiz = NULL; };
  ~Arbol(){};
  void CreaArbolBus(Post x);
  void VerArbol() { show(raiz, 0); }
  void Borrar(int idp) { borrar(raiz, idp);}
  void ListarA(int idp){listar(raiz,idp);}
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
void Arbol::CreaArbolBus(Post x) { ArbolBusq(x, raiz); }

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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class GestionPost {
private:
  Arbol arbol_post;
  int idPost;
  int idComentario;
  int idRespuesta;

public:
  GestionPost() {
    int idPosteo = 0;
    int idCom = 0;
    int idResp = 0;
  }
  void agregarPost(string titulo, string nombre, string contenido);
  void agregarComentario(int idPost, string nombre, string contenido);
  void agregarRespuesta(int idComent, int idp, string n, string c);
  Arbol GetArbol() { return arbol_post; }
  void Votar();
  void Menu();
  bool arbolVacio();
  void MostrarPosts() { arbol_post.VerArbol(); }
  void BorrarPost(int idp) { arbol_post.Borrar(idp); }
  void ListarArbol(int idp) { arbol_post.ListarA(idp)}
};

bool GestionPost::arbolVacio() {
  if (idPost == 0) {
    return true;
  } else {
    return false;
  }
}
/*
void GestionPost::Menu() {
  int proseguir = 1;
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
    cout << "      ¿DESEA AGREGAR UN POST NUEVO? ESCRIBA '1' EN EL CASO DE SI:";
cin >> proseguir;
  }

  if (proseguir == 1) {
    MostrarPosts();
  }

  while (proseguir == 1) {
    cout << "\n----- Red Social REDDIT-LIKE -----\n";
    cout << "1. Agregar un nuevo post\n";
    cout << "2. Mostrar posts\n";
    cout << "0. Salir\n";
    cout << "Ingrese su opción: ";
    cin >> opcion;
    if (opcion < 0 || opcion > 3) {
      cout << "INGRESE UNA OPCION VALIDA (0 || 1 || 2 || 3) y vuelva a "
              "intentarlo\n\n";
      continue;
    }
    if (opcion == 1) {
      cout << "TITULO: ";
      getline(cin, titulo);

      cout << "NOMBRE: ";
      getline(cin, nombre);

      cout << "CONTENIDO: ";
      getline(cin, contenido);

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      this->agregarPost(titulo, nombre, contenido);
      break;

    } else if (opcion == 2) {
      cout << "INGRESE EL NUMERO DEL POST A COMENTAR: ";
      cin >> idp;
      cout << "NOMBRE: ";
      cin >> nombre;
      cout << "CONTENIDO: ";
      cin >> contenido;
      cout << endl;
      this->agregarComentario(idp, nombre, contenido);
      break;
    } else if (opcion == 3) {
      cout << "INGRESE EL NUMERO DEL POST Y SU COMENTARIO A RESPONDER: ";
      cin >> idp;
      cout << endl;
      cout << "NOMBRE: ";
      cin >> nombre;
      cout << endl;
      cout << "CONTENIDO: ";
      cin >> contenido;
      cout << endl;
      //this->agregarRespuesta(idc, nombre, contenido);
      break;
    } else {
      proseguir = 0;
    }
  }
  MostrarPosts();
}*/

void GestionPost::agregarPost(string titulo, string nombre, string contenido) {
  Post post_nuevo = Post(titulo, nombre, contenido);
  this->idPost++;
  post_nuevo.setIdPost(idPost);
  post_nuevo.setIdComentario(0);
  // post_nuevo.setIdRespuesta(0);
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

void GestionPost::agregarRespuesta(int idc, int idp, string nombre,
                                   string contenido) {
  Post post_nuevo = Post(" ", nombre, contenido);
  this->idRespuesta++;
  post_nuevo.setIdRespuesta(idRespuesta);
  post_nuevo.setIdComentario(idc);
  post_nuevo.setIdPost(idp);
  post_nuevo.setTipo(0);
  arbol_post.CreaArbolBus(post_nuevo);
}

int main() {
  GestionPost gestionPost;
  gestionPost.MostrarPosts();
  gestionPost.agregarPost("MI PRIMER POST - TEORIA DE REDES", "Rodrigo",
                          "POST 1"); //
  gestionPost.agregarPost("MI SEGUNDO POST", "Simon", "POST 2");
  gestionPost.agregarComentario(1, "Manolito", "Comentario al POST 1"); // COM 1
  gestionPost.agregarComentario(2, "Anibal", "Comentario al POST 2");   // COM2
  gestionPost.agregarComentario(1, "Marcelo", "Comentario al POST 1");  //
  gestionPost.agregarRespuesta(
      3, 1, "Laura", "Respuesta al comentario 1 del post 1");       // RESP 1
  gestionPost.agregarComentario(2, "Jose", "Comentario al POST 2"); // COM 4
  gestionPost.agregarComentario(2, "Raul", "Comentario al POST 2"); // COM5
  gestionPost.agregarPost("ASDSAAD", "Ramiro", "POST 3");
  gestionPost.agregarComentario(3, "Samira", "Comentario al POST 3"); // COM 6
  // gestionPost.agregarComentario(1, "Nicolas", "Comentario al post1");
  // gestionPost.agregarComentario(1, "Lautaro", "Comentario al Post1");
  gestionPost.agregarComentario(3, "Jessica", "Comentario Post 3");
  gestionPost.agregarPost("", "Christian", "blabla");
  gestionPost.agregarComentario(4, "Hugo", "Comentario Post 4");
  gestionPost.agregarComentario(4, "Roberto", "Comentario Post 4");
  // gestionPost.agregarRespuesta(4, 1, "Lola", "Respuest al comentario 2 del
  // post 1");
  gestionPost.agregarRespuesta(6, 3, "Ricardo",
                               "Respuest al comentario 2 del post 1");
  gestionPost.agregarRespuesta(2, 2, "Pedro",
                               "Respuest al comentario 2 del post 1");
  gestionPost.agregarRespuesta(2, 2, "Anuel",
                               "Respuest al comentario 2 del post 3");
  gestionPost.agregarRespuesta(7, 3, "Marco",
                               "Respuest al comentario 3 del post 1");
  // gestionPost.agregarRespuesta(7, 1, "Merca", "Respuest al comentario 3 del
  // post 1");

  gestionPost.MostrarPosts();
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

  return 0;
}