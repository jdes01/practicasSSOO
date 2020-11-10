// Implemente un programa que cree un vector de 10 elementos relleno con números aleatorios entre 1 y 9. 
// Reparta ese vector entre 2 hebras o 5 hebras a partes iguales, según se indique por linea de argumentos un 2 o un 5, 
// de forma que cada hebra sume la parte del vector que le corresponda y se lo devuelva al hilo principal, 
// el cual mostrará la suma de los resultados devuelto por las hebras creadas.
// Ejemplo de invocación del programa para crear 4 hebras que se repartan el vector: ./a.out 5

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * suma2(void * i);
void * suma5(void * i);
void rellenarAleatorio(int v[]);

typedef struct Vector
{
    int inicio;
    int final;
    int v[10];
}Vect;


int main(int argc, char * argv[]){

    Vector Vect v[];

    rellenarAleatorio(v); 
    
    int x = atoi(argv[1]);

    if ( (x!=2) && (x!=5) ) exit(EXIT_FAILURE);

    pthread_t hilo[x];
    
    if(x==2){

        for (int i = 0; i < x; i++){ 

            pthread_create ( &hilo[i], NULL, (void *) suma2(i), (void*) v); //crea las hebras y llama a la funcion suma
        }  

    }
    
    else if(x==5){

        for (int i = 0; i < x; i++){ 

            pthread_create ( &hilo[i], NULL, (void *) suma5(i), (void*) v); //crea las hebras y llama a la funcion suma
        }

    }

      

}

void * suma2(void * v){

    for (int i = 0; i < 10; i++ ) {

      printf(v[i]);
    }
    return 0;
}

void * suma5(void * v){

    for (int i = 0; i < 10; i++ ) {

      printf(v[i]);
    }
    return 0;
}

void rellenarAleatorio(int v[]){

    srand(time(0)); //se establece el número semilla

    for (int i = 0; i < 10; i++ ) {

      v[i]=(rand()%9)+1;
    }

    for (int i = 0; i < 10; i++ ) {

      printf(v[i]);
    }
}

