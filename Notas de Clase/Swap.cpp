#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_PS 4

typedef struct {
       int dia;
       int mes;
       int anio;
} FECHA;

typedef struct {
       char nombre[20];
       FECHA nac;
       long int dni;
} persona;

void printfecha(FECHA *f){
     printf("dia:%d - mes:%d - anio:%d\n",f->dia,f->mes,f->anio);
}

void printpersona(persona *p){
    printf("nombre %s,dni %ld,nac:",p->nombre,p->dni);
    printfecha(&(p->nac));
}

void cargar_ps(persona *ps){
     int i;
     for(i=0;i<N_PS;i++){
        strcpy((ps+i)->nombre,"Luisa Castro");
        (ps+i)->dni=10998760+i;
        (ps+i)->nac.dia=10+i;
        (ps+i)->nac.mes=2;
        (ps+i)->nac.anio=1980;
     }
}

void print_ps(persona *ps){
     int i;
     for(i=0;i<N_PS;i++){
         printpersona(ps+i);
     }
}

int main(int argc, char *argv[])
{
     FECHA f1, f2;
     persona p1;
     persona *pp1;
	        
     pp1=(persona *)malloc(sizeof(persona));

     f1.dia=12;f1.mes=3;f1.anio=1999;
     strcpy(p1.nombre,"Juan Lopez");
     p1.dni=12445099;
     p1.nac.dia=1;
     p1.nac.mes=12;
     p1.nac.anio=1999;

     strcpy(pp1->nombre,"Luisa Castro");
     pp1->dni=10998760;
     pp1->nac.dia=10;
     pp1->nac.mes=2;
     pp1->nac.anio=1980;
     printpersona(&p1);
     printpersona(pp1);
     free(pp1);
//   system("PAUSE");

     persona *ps;
						  
     ps=(persona *)malloc(sizeof(persona)*N_PS);
     cargar_ps(ps);
     print_ps(ps);
     free(ps);
//   system("PAUSE");

     return 0;
}