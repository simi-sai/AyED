#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;
// prototipos
void burbuja( int [],  int, bool (*)( int, int ) );
void intercambia( int * , int *  );   
bool ascendente( int, int );
bool descendente( int, int );

int main(int argc, char *argv[])
{  const int tamanoArreglo = 10;    
   int orden; 
   int contador;
   int a[ tamanoArreglo ] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };

   cout << "Introduzca 1 para ordenar de manera ascendente,\n" 
        << "Introduzca 2 para ordenar de manera descendente: ";
   cin >> orden;
   cout << "\nElementos de datos en el orden original\n";
   
   // muestra el arreglo original
   for ( contador = 0; contador < tamanoArreglo; contador++ )
      cout << setw( 4 ) << a[ contador ];

   // ordena el arreglo en orden ascendente; pasa a la funci�n ascendente
   // como un argumento para especificar el orden ascendente
   if ( orden == 1 ) {
      burbuja( a, tamanoArreglo, ascendente );
      cout << "\nElementos de datos en orden ascendente\n";
   }

   // ordena el arreglo en orden descendente; pasa a la funci�n descendente
   // como un argumento para especificar el orden descendente
   else {
      burbuja( a, tamanoArreglo, descendente );
      cout << "\nElementos de datos en orden descendente\n";
   }

   // muestra arreglo ordenado
   for ( contador = 0; contador < tamanoArreglo; contador++ )
      cout << setw( 4 ) << a[ contador ];

   cout << endl;

    system("PAUSE");
    return EXIT_SUCCESS;
}

// ordenamiento burbuja multiprop�sito; el par�metro compara es un apuntador a
// la funci�n de comparaci�n que determina el tipo de ordenamiento
void burbuja( int trabajo[], const int tamano, 
             bool (*compara)( int, int ) )
{
   // ciclo para controlar las pasadas
   for ( int pasada = 1; pasada < tamano; pasada++ )

      // ciclo para controlar el n�mero de comparaciones por pasada
      for ( int cuenta = 0; cuenta < tamano - 1; cuenta++ )

         // si los elementos adyacentes se encuentran en desorden, los intercambia
         if ( (*compara)( trabajo[ cuenta ], trabajo[ cuenta + 1 ] ) )
            intercambia( &trabajo[ cuenta ], &trabajo[ cuenta + 1 ] );

} // fin de la funci�n burbuja

// intercambia valores en localidades de memoria a los cuales 
// apuntan ptrElemento1 y ptrElement2
void intercambia( int *  ptrElemento1, int *  ptrElemento2 )
{
   int mantiene  = *ptrElemento1;
   *ptrElemento1 = *ptrElemento2;
   *ptrElemento2 = mantiene;

} // fin de la funci�n intercambia

// determina si los elementos est�n en desorden 
// para un ordenamiento ascendente
bool ascendente( int a, int b )
{
   return b < a;   // intercambia si b es menor que a

} // fin de la funci�n ascendente

// determina si los elementos est�n en desorden
// para un ordenamiento descendente
bool descendente( int a, int b )
{
   return b > a;   // intercambia si b es mayor que a

} // fin de la funci�n descendente
