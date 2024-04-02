#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

class Tiempo {

public:
   Tiempo(int = 0, int = 0, int = 0); // constructor predeterminado
   ~Tiempo(); // destructor predeterminado
   // funciones establecer = set
   void estableceHora( int, int, int ); // establece hora, minuto, segundo
   void estableceHora1( int );   // establece hora
   void estableceMinuto( int );  // establece minuto
   void estableceSegundo( int ); // establece segundo

   // funciones obtener = get
   int obtieneHora1();        // obtiene hora
   int obtieneMinuto();       // obtiene minuto
   int obtieneSegundo();      // obtiene segundo

   void imprimeUniversal();         // imprime la hora en formato universal
   void imprimeEstandar();          // imprime la hora en formato est�ndar
   
   void incrementaSegundos(const int);
   void incrementaMinutos(const int );
   void incrementaHoras(const int);
private:
   int hora;     // 0 - 23 (formato de reloj de 24 horas)
   int minuto;   // 0 - 59
   int segundo;  // 0 - 59

}; // fin de la clase Tiempo

// funci�n constructor para inicializar datos privados;
// llama a la funci�n miembro estableceHora para asignar los valores;
// los valores predeterminados son 0 (vea la definic�n de la clase)
Tiempo::Tiempo( int hr, int min, int seg ) 
{ 
   cout<<"\n soy el constructor\n";
   estableceHora( hr, min, seg ); 

} // fin del constructor Tiempo
Tiempo::~Tiempo()
{ cout<<"\n soy el destructor ------------";
}
// establece los valores de hora, minuto y segundo
void Tiempo::estableceHora( int h, int m, int s )     //los metodos de la clase timepo llevan ::
{ 
   estableceHora1( h );
   estableceMinuto( m );
   estableceSegundo( s );

} // fin de la funci�n estableceHora

// establece el valor de hora
void Tiempo::estableceHora1( int h ) 
{
   hora = ( h >= 0 && h < 24 ) ? h : 0; 

} // fin de la funci�n estableceHora1

// establece el valor de minuto
void Tiempo::estableceMinuto( int m )
{ 
   minuto = ( m >= 0 && m < 60 ) ? m : 0; 

} // fin de la funci�n estableceMinuto

// establece el valor de segundo
void Tiempo::estableceSegundo( int s )
{ 
   segundo = ( s >= 0 && s < 60 ) ? s : 0; 

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
   cout << setfill( '0' ) << setw( 2 ) << hora << ":"
        << setw( 2 ) << minuto << ":"
        << setw( 2 ) << segundo;

} // fin de la funci�n imprimeUniversal

// print Time in standard format
// imprime Tiempo en formato est�ndar
void Tiempo::imprimeEstandar()
{
   cout << ( ( hora == 0 || hora == 12 ) ? 12 : hora % 12 )
        << ":" << setfill( '0' ) << setw( 2 ) << minuto
        << ":" << setw( 2 ) << segundo 
        << ( hora < 12 ? " AM" : " PM" );

} // fin de la funcion imprimeEstandar
void Tiempo::incrementaSegundos(const int cuenta )
{
   cout << "Incrementa segundo " << cuenta
        << " veces:\nHora inicio: ";
   imprimeEstandar();

   for ( int i = 0; i < cuenta; i++ ) {
      estableceSegundo( ( obtieneSegundo() + 1 ) % 60 );  

      if ( obtieneSegundo() == 0 )
         incrementaMinutos(1);

      cout << "\nsegundo + 1: ";
      imprimeEstandar();

   } // fin de for

   cout << endl;

} // fin de la funci�n incrementaSegundos

void Tiempo::incrementaMinutos(const int cuenta )
{
   cout << "Incrementa minuto " << cuenta
        << " veces:\nHora inicio: ";
   imprimeEstandar();

   for ( int i = 0; i < cuenta; i++ ) {
      estableceMinuto( ( obtieneMinuto() + 1 ) % 60 );  

      if ( obtieneMinuto() == 0 )
         incrementaHoras(1);

      cout << "\nminuto + 1: ";
      imprimeEstandar();

   } // fin de for

   cout << endl;

} // fin de la funci�n incrementaMinutos

void Tiempo::incrementaHoras(const int cuenta )
{
   cout << "Incrementa hora " << cuenta
        << " veces:\nHora inicio: ";
   imprimeEstandar();

   for ( int i = 0; i < cuenta; i++ ) {
      estableceHora1( ( obtieneHora1() + 1 ) % 24 );

      cout << "\nhora + 1: ";
      imprimeEstandar();

   } // fin de for

   cout << endl;

} // fin de la funci�n incrementaHoras

/*
Hacer una clase Semana_Laboral
que almacene:
el Nombre de un empleado
su documento
en un arreglo de 5 x 2 de tipo Tiempo la hora de ingreso y de salida de cada d�a
La clase debe tener m�todos para
setear la hora de ingreso y de salida para cada d�a
obtener el n�mero total de horas y minutos trabajados en la semana
todo otro m�todo que considere
*/

class Semana_Laboral{

   public:
   Semana_Laboral(string nom, long int doc, Tiempo s[5][2]);   //constructor
   ~Semana_Laboral();  //destructor
    
   void setHoraIngreso(int = 0, int = 0, int = 0, int = 0);
   void setHoraSalida(int = 0, int = 0, int = 0, int = 0);

   Tiempo getTotal_Horas();

   private:
   string nombre;
   long int documento;
   Tiempo Trabajo[5][2];
   Tiempo Total_Horas;
    

};  //fin de la clase

Semana_Laboral::Semana_Laboral(string nom, long int doc, Tiempo s[5][2]) 
{ 
   cout<<"\nSoy el constructor\n";
   nombre = nom;
   documento = doc;
   for(int i = 0; i < 5; i++);
   {
      for(int j = 0; j < 2, j++);
      {
         s[i][j].estableceHora(0,0,0);
      }
   }

} // fin del constructor Semana_Laboral

Semana_Laboral::~Semana_Laboral()
{
   cout << "\nSoy el destructor\n";
}

void Semana_Laboral::setHoraIngreso(int d, int h, int m, int s)
{
   Trabajo[d][0].estableceHora(h,m,s);
}

void Semana_Laboral::setHoraSalida(int d, int h, int m, int s)
{
   Trabajo[d][1].estableceHora(h,m,s);
}

Tiempo Semana_Laboral::getTotal_Horas()
{
   long int Acumulacion = 0, TE = 0, TS = 0;
   int th = 0, tm = 0, ts = 0; 

   for(int i = 0; i < 4; i++)
   {
      TE = Trabajo[0][i].obtieneHora1() * 3600 + Trabajo[0][i].obtieneMinuto() * 60 
      + Trabajo[0][i].obtieneSegundo();
      
      TS = Trabajo[1][i].obtieneHora1() * 3600 + Trabajo[1][i].obtieneMinuto() * 60
      + Trabajo[1][i].obtieneSegundo();

      Acumulacion += TS - TE;
   }

   th = int(Acumulacion / 3600);
   tm = int((Acumulacion - (th * 3600)) / 60);
   ts = int(Acumulacion - (th * 3600) - (tm * 60));

   Total_Horas.estableceHora1(th);
   Total_Horas.estableceMinuto(tm);
   Total_Horas.estableceSegundo(ts);

   return Total_Horas;
}

int main(int argc, char *argv[])
{  
    {Tiempo t(14,40,0),x,y(10);              // crea el objeto de Tiempo
      t.imprimeEstandar(); cout<<endl;
      x.imprimeEstandar(); cout<<endl;
      y.imprimeEstandar(); cout<<endl;
    
      //Tiempo *p= new Tiempo(11,11,11);
      //p->imprimeEstandar();cout<<endl;
      
   // establece la hora mediante funciones establece (set) individuales
   t.estableceHora1( 17 );     // establece hora en un valor v�lido
   t.estableceMinuto( 34 );   // establece minuto en un valor v�lido
   t.estableceSegundo( 25 );   // establece segundo en un valor v�lido

   // funciones obtener (get) para obtener hora, minuto y segundo
   cout << "Resultado de establecer todos los valores validos:\n" 
        << "  Hora: " << t.obtieneHora1()
        << "  Minuto: " << t.obtieneMinuto()
        << "  Segundo: " << t.obtieneSegundo();

   // establece hora mediante el uso de funciones individuales
   t.estableceHora1( 234 );     // establece hora no v�lida en 0
   t.estableceMinuto( 43 );    // establece minuto en un valor v�lido
   t.estableceSegundo( 6373 ); // establece segundo no v�lido en 0

   // despliega hora, minuto y segundo despu�s de establecer 
   // los valores no v�lidos de hora y segundo
   cout << "\n\nResultado del intento de establecer los valores no validos de minuto"
        << " y segundo:\n  Hora: " << t.obtieneHora1()
        << "  Minuto: " << t.obtieneMinuto()
        << "  Segundo: " << t.obtieneSegundo() << "\n\n";

   t.estableceHora( 11, 58, 0 );    // establece hora
   t.incrementaSegundos( 150 );  // incrementa los minutos de t en 3
   t.imprimeEstandar(); cout<<endl;



    cout<<endl<<endl;

  }

  {
   Semana_Laboral s("Simon", 42978650, s), g("Geronimo", 43926874, g);
   Tiempo HT;

   s.setHoraIngreso(0,8,15,0);
   s.setHoraIngreso(1,8,15,0);
   s.setHoraIngreso(2,8,15,0);
   s.setHoraIngreso(3,8,15,0);
   s.setHoraIngreso(4,8,15,0);

   s.setHoraSalida(0,16,50,14);
   s.setHoraSalida(1,16,50,14);
   s.setHoraSalida(2,16,50,14);
   s.setHoraSalida(3,16,50,14);
   s.setHoraSalida(4,16,50,14);

   HT = s.getTotal_Horas();
   cout << "Horas: " << HT.obtieneHora1() << ", Minutos: " << HT.obtieneMinuto() << ", Segundos: "
   << HT.obtieneSegundo() << endl;

   HT = g.getTotal_Horas();
   cout << "Horas: " << HT.obtieneHora1() << ", Minutos: " << HT.obtieneMinuto() << ", Segundos: "
   << HT.obtieneSegundo() << endl;

  }
    cout<<endl<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
