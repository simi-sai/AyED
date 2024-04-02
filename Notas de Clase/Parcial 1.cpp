#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>

using namespace std;

class Frutas{
    private:
       string tipo;
       long int cantidad;

    public:
       void setTipo();
       string getTipo();
       void setCantidad();
       long int getCantidad();

       void Almacenar();
       void Quitar();
       void Seccionar();
};

class Stock{
    Secciones sector;
};

class Secciones{

};

class Cliente{      //aun no se si esta clase es necesaria
    private:
    string nombre;
    string tipo;
};

class Pedido{    //en esta clase se supone que deberiamos tener la cola de pedidos
    private:
    Cliente cliente;
    string f;
    long int numero;
};

class Cajon {    //es la clase principal
    private:
    Frutas fruta;
    int ID;
    int pesoActual;
    bool Estado;   //True si está lleno y false si no
    int const cantMAX = 20;

    public:
    Cajon(){}; //Constructor
    ~Cajon();

}; 

int main() {
    Frutas* f = new Frutas();

    return 0;
}