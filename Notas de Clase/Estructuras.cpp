#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct {
    int dia;
    int mes;
    int anio;
} FECHA;

int compFecha(FECHA *ff1, FECHA *ff2){
    if(ff1 -> anio > ff2 -> anio){
        return 1;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]){
    FECHA f1;
    f1.dia = 10;
    f1.mes = 4;
    f1.anio = 1997;

    FECHA *f2;
    f2 = (FECHA *)malloc(sizeof(FECHA));

    f2 -> mes = 8;
    f2 -> dia = 22;
    f2 -> anio = 2013;

    printf("dia: %d, mes: %d, anio: %d",f1.dia,f1.mes,f1.anio);         //dos formas de escribir lo mismo   
    cout << "\ndia: " << f1.dia << ", mes: " << f1.mes << ", anio: " << f1.anio;
    cout << "\ndia: " << f2->dia << ", mes: " << f2->mes << ", anio: " << f2->anio;
    cout << "\nf1 > f2 = " << compFecha(&f1,f2) << endl;

    free(f2);

    return 0;

}