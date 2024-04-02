#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Tiempo {

public:
    Tiempo(int = 0, int = 0, int = 0); // constructor predeterminado
    ~Tiempo(); // destructor predeterminado
    // funciones establecer = set
    void estableceHora(int, int, int); // establece hora, minuto, segundo
    void set_hora(int);
    void estableceHora1(int);   // establece hora
    void estableceMinuto(int);  // establece minuto
    void estableceSegundo(int); // establece segundo

    // funciones obtener = get
    int obtieneHora1();        // obtiene hora
    int obtieneMinuto();       // obtiene minuto
    int obtieneSegundo();      // obtiene segundo

    void imprimeUniversal();         // imprime la hora en formato universal
    void imprimeEstandar();          // imprime la hora en formato est�ndar

    void incrementaSegundos(const int);
    void incrementaMinutos(const int);
    void incrementaHoras(const int);
private:
    int hora;     // 0 - 23 (formato de reloj de 24 horas)
    int minuto;   // 0 - 59
    int segundo;  // 0 - 59

}; // fin de la clase Tiempo

// funci�n constructor para inicializar datos privados;
// llama a la funci�n miembro estableceHora para asignar los valores;
// los valores predeterminados son 0 (vea la definic�n de la clase)
Tiempo::Tiempo(int hr, int min, int seg)
{
    cout << "\n soy el constructor\n";
    estableceHora(hr, min, seg);

} // fin del constructor Tiempo
Tiempo::~Tiempo()
{
    cout << "\n soy el destructor ------------";
}
// establece los valores de hora, minuto y segundo
void Tiempo::estableceHora(int h, int m, int s)
{
    estableceHora1(h);
    estableceMinuto(m);
    estableceSegundo(s);

} // fin de la funci�n estableceHora

void Tiempo::set_hora(int h) {
    hora = h;
}
// establece el valor de hora
void Tiempo::estableceHora1(int h)
{
    hora = (h >= 0 && h < 24) ? h : 0;

} // fin de la funci�n estableceHora1

// establece el valor de minuto
void Tiempo::estableceMinuto(int m)
{
    minuto = (m >= 0 && m < 60) ? m : 0;

} // fin de la funci�n estableceMinuto

// establece el valor de segundo
void Tiempo::estableceSegundo(int s)
{
    segundo = (s >= 0 && s < 60) ? s : 0;

} // fin de la funci�n estableceSegundo

// devuelve el valor de hora
int Tiempo::obtieneHora1()
{
    return hora;

} // fin de la funci�n obtieneHora1

// devuelve el valor de minuto 
int Tiempo::obtieneMinuto()
{
    return minuto;

} // fin de la funci�n obtieneMinuto

// devuelve el valor de segundo 
int Tiempo::obtieneSegundo()
{
    return segundo;

} // fin de la funci�n obtieneSegundo

// imprime Tiempo en formato universal
void Tiempo::imprimeUniversal()
{
    cout << setfill('0') << setw(2) << hora << ":"
        << setw(2) << minuto << ":"
        << setw(2) << segundo;

} // fin de la funci�n imprimeUniversal

// print Time in standard format
// imprime Tiempo en formato est�ndar
void Tiempo::imprimeEstandar()
{
    cout << ((hora == 0 || hora == 12) ? 12 : hora % 12)
        << ":" << setfill('0') << setw(2) << minuto
        << ":" << setw(2) << segundo
        << (hora < 12 ? " AM" : " PM");

} // fin de la funcion imprimeEstandar
void Tiempo::incrementaSegundos(const int cuenta)
{
    cout << "Incrementa segundo " << cuenta
        << " veces:\nHora inicio: ";
    imprimeEstandar();

    for (int i = 0; i < cuenta; i++) {
        estableceSegundo((obtieneSegundo() + 1) % 60);

        if (obtieneSegundo() == 0)
            incrementaMinutos(1);

        cout << "\nsegundo + 1: ";
        imprimeEstandar();

    } // fin de for

    cout << endl;

} // fin de la funci�n incrementaSegundos

void Tiempo::incrementaMinutos(const int cuenta)
{
    cout << "Incrementa minuto " << cuenta
        << " veces:\nHora inicio: ";
    imprimeEstandar();

    for (int i = 0; i < cuenta; i++) {
        estableceMinuto((obtieneMinuto() + 1) % 60);

        if (obtieneMinuto() == 0)
            incrementaHoras(1);

        cout << "\nminuto + 1: ";
        imprimeEstandar();

    } // fin de for

    cout << endl;

} // fin de la funci�n incrementaMinutos

void Tiempo::incrementaHoras(const int cuenta)
{
    cout << "Incrementa hora " << cuenta
        << " veces:\nHora inicio: ";
    imprimeEstandar();

    for (int i = 0; i < cuenta; i++) {
        estableceHora1((obtieneHora1() + 1) % 24);

        cout << "\nhora + 1: ";
        imprimeEstandar();

    } // fin de for

    cout << endl;

} // fin de la funci�n incrementaHoras

class Semana_Laboral {
private:
    string nombre;
    double dni;
    Tiempo T[5][2];
    Tiempo total_horas;

public:
    void set_entrada(int = 0, int = 0, int = 0, int = 0);
    void set_salida(int = 0, int = 0, int = 0, int = 0);

    Tiempo get_total_horas();
    
};

void Semana_Laboral::set_entrada(int i,int h, int m, int s)
{
    T[i][0].estableceHora1(h);
    T[i][0].estableceMinuto(m);
    T[i][0].estableceSegundo(s);

} // fin de la funci�n set_entrada

void Semana_Laboral::set_salida(int i, int h, int m, int s)
{
    T[i][1].estableceHora1(h);
    T[i][1].estableceMinuto(m);
    T[i][1].estableceSegundo(s);

} // fin de la funci�n set_salida

Tiempo Semana_Laboral::get_total_horas() {
    double te, ts, tx, acumula;
    acumula = 0;
    for (int i = 0; i < 5; i++) {
        te = T[i][0].obtieneHora1() * 3600 + T[i][0].obtieneMinuto() * 60 + T[i][0].obtieneSegundo();
        ts = T[i][1].obtieneHora1() * 3600 + T[i][1].obtieneMinuto() * 60 + T[i][1].obtieneSegundo();
        acumula = acumula + ts - te;
    }
    te = int(acumula / 3600);
    ts = int((acumula - te * 3600) / 60);
    tx = int(acumula - te * 3600 - ts * 60);
    total_horas.set_hora(te);
    total_horas.estableceMinuto(ts);
    total_horas.estableceSegundo(tx);

    return total_horas;
}

int main(int argc, char* argv[]) {
    Semana_Laboral s;
    Tiempo ht;
    for (int i = 0; i < 5; i++) {
        s.set_entrada(i, 8, 0, 0);
        s.set_salida(i, 18, 20, 40);
    }
    ht = s.get_total_horas();
    cout << endl;
    cout << "total horas="<< ht.obtieneHora1() << "  min=" << ht.obtieneMinuto()<< "  seg=" << ht.obtieneSegundo() << endl;


}

/*
Hacer una clase Semana_Laboral
que almacene:
el Nombre de un empleado
su documento
en un arreglo de 5 x 2 de tipo Tiempo la hora de ingreso y de salida de cada d?a
La clase debe tener m?todos para
setear la hora de ingreso y de salida para cada d?a
obtener el n?mero total de horas y minutos trabajados en la semana
todo otro m?todo que considere
*/
