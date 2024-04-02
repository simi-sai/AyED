#include <stdio.h>
#include <iostream>

using namespace std;

class Fecha {
    private:
       int dia;
       int mes;
       int anio;
    public:
       Fecha(){cout << "soy el constructor " << endl;};
       ~Fecha(){};
       void setDia(int a){dia = a;}
       void setMes(int m){mes = m;}
       void setAnio(int aa){anio = aa;}
       int getDia(){return dia;}
       int getMes(){return mes;}
       int getAnio(){return anio;}
};

int main(int argc, char *argv[])
{
    Fecha *f1 = new Fecha();
    f1 -> setDia(3);
    f1 -> setMes(9);
    f1 -> setAnio(2003);
    
    cout << "dia " << f1 -> getDia() << ", mes " << f1 -> getMes() << ", anio " << f1 -> getAnio() << endl;
    
    delete(f1);
    return 0;
}
