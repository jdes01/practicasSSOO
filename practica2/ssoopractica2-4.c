#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * aumentaVariableGlobal();

int variableGlobal = 0;

int main(int argc, char * argv[]){


    int nHilos = 2; //el numero de hilos sera la cantidad de argumentos que se le pasen
    int total = 0; //total de lineas entre todos los ficheros
    int * nLineas=0;
    pthread_t hilos[nHilos];

    for (int i = 0; i < nHilos; i++){ pthread_create(&hilos[i], NULL, aumentaVariableGlobal, NULL ); }

    for (int i = 0; i < nHilos; i++) { pthread_join(hilos[i], NULL); }

    printf("la variable global suma %i \n", variableGlobal);
    
}

void * aumentaVariableGlobal(){

    for (int i = 0; i < 10; i++)
    {
        variableGlobal++;
        printf("%i\n", variableGlobal);
    }

    printf("la hebra ha aumentado %i veces\n", variableGlobal);
    
    pthread_exit(NULL); 

}