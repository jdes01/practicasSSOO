// Implemente un programa que cuente las líneas de los ficheros de texto que se le pasen como parámetros y al final muestre el número de líneas totales 
// (contando las de todos los ficheros juntos). Ejemplo de llamada: ./a.out fichero1 fichero2 fichero3
// Debe crear un hilo por cada fichero indicado por linea de argumentos, de forma que todos los ficheros se procesen de manera paralela, uno por cada hilo.


//funcionar funciona pero pone un par de lineas mas de la cuenta, debe ser culpa de la funcion cuentaLineas

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * cuentaLineas(void * fichero);

int main(int argc, char * argv[]){

    int nHilos = argc-1; //el numero de hilos sera la cantidad de argumentos que se le pasen
    int total = 0; //total de lineas entre todos los ficheros
    int * nLineas=0;
    pthread_t hilos[nHilos];

    for (int i = 0; i < nHilos; i++){ pthread_create(&hilos[i], NULL, cuentaLineas, (void*) argv[i+1]); } //al crear los hilos, cada uno llama a cuentaLineas
    // y le pasa el parametro argv[i+1]

    for (int i = 0; i < nHilos; i++) {

        pthread_join(hilos[i], (void**) &nLineas); //va recibiendo los hilos que bajan del pthreas_create

        printf("El fichero %s tiene %i lineas\n", argv[i+1], *nLineas);

        total += *nLineas; //se van sumando al total
    }

    printf("Entre todos los ficheros suman %i lineas\n", total);
    
}

void * cuentaLineas(void * fichero){

    printf("contando el fichero: %s\n", fichero);

    int * nLineas = malloc(sizeof(int)); //guarda memoria para el puntero con el tamaño de un int

    FILE * f = fopen(fichero, "r"); //abre el fichero en modo lectura

    *nLineas = 0; //establece el vector lineas en 0

    char s[200]; //aqui la funcion fgets irá 'almacenando' 

    while(fgets(s, 200, f)){ *nLineas = *nLineas + 1; } //fgets lee el fichero f, va almacenando en s, y salta cuando llega a 200 (por poner algo),
        // cambia de linea o llega al final. el puntero nLineas ira sumando
    pthread_exit((void *) nLineas); //devuelve el numero de lineas

}