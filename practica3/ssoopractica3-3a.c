//Archivo ej3a.c
//Problema del productor-consumidor
//Programa que crea 1 consumidor y 1 productor, modifican un buffer de 5 datos haciendo cada uno 10 cambios

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

#define n 5                                     //Tamaño del buffer de datos

int v[n];                                       //Buffer de n elementos
int indiceConsumicion=0;                        //Indice de datos de consumicion, lo usaremos para movernos en el buffer y no quitar datos de posiciones donde no haya datos
int indiceProduccion=0;                         //Indice de datos de produccion, lo usaremos para movernos en el buffer y no escribir datos donde ya haya datos

sem_t mutex;                                    //Semaforo que controlara que dos hebras no modifiquen a la vez el buffer v
sem_t full;                                     //Semaforo que se aumentara hasta valer 5, lo que significara que v estara lleno. Cada vez que decremente, es que hemos sacado un valor de v
sem_t empty;                                    //Semaforo que se decrementara hasta valer 0, lo que significara que v estara vacio. Cada vez que aumente, es que hemos sacado un valor de v


int main(){

    srand(time(NULL));                  //Plantamos la semilla del numero aleatorio

    sem_init(&mutex, 0, 1);             //Iniciamos el semaforo mutex a 1
    sem_init(&full, 0, 0);              //Iniciamos el semaforo full a 0, porque al empezar hay 0 elementos llenos en el buffer v
    sem_init(&empty, 0, n);             //Iniciamos el semaforo empty a n, porque al empezar hay n elementos vacios en el buffer v

    pthread_t threadProductor;          //1 hebra productor
    pthread_t threadConsumidor;         //1 hebra consumidor

        if(pthread_create(&threadProductor, NULL, productor, NULL)){                            //Creacion de hebra productora con comprobacion de error
            printf("Error, no se ha podido crear la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }

        if(pthread_create(&threadConsumidor, NULL, consumidor, NULL )){                         //Creacion de hebra consumidora con comprobacion de error                 
            printf("Error, no se ha podido crear la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    
        if (pthread_join(threadProductor, NULL)){                                               //Recogida de hebra productora con comprobacion de error
            printf("Error, no se ha podido recoger la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    
        if (pthread_join(threadConsumidor, NULL)){                                              //Recogida de hebra consumidora con comprobacion de error
            printf("Error, no se ha podido recoger la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
   
    for(int i=0; i<n; i++){                                     //Imprimimos el buffer v al finalizar
        printf("Valor %d del buffer: %d\n", i+1, v[i]);
    }
    exit(EXIT_SUCCESS);                                         //Salimos del programa
}


void * productor(){                                         //Funcion a la que accede la hebra productora
    for (int i=0; i<10; i++){                               //Produciremos 10 valores
        sem_wait(&empty);                                   //Se decrementa empty, indicando que hay un espacio vacio menos en v                           
        sem_wait(&mutex);                                   //Se pone el semaforo a 0
        int numero = rand()%101;                            //Generamos un numero aleatorio del 0 al 100
        producirDato(numero);                               //Producimos el numero
        printf("---->Productor, Dato %d: %d\n", i+1, numero);
        sem_post(&mutex);                                   //Se pone el semaforo a 1
        sem_post(&full);                                    //Se aumenta full, indicando que hay un espacio ocupado mas en v
    }
    pthread_exit(NULL);                                     //Salimos de la hebra
}

void * consumidor(){                                        //Funcion a la que accede la hebra productora
    for (int i=0; i<10; i++){                               //Produciremos 10 valores
        sem_wait(&full);                                    //Se decrementa full, indicando que hay un espacio lleno menos en v  
        sem_wait(&mutex);                                   //Se pone el semaforo a 0
        int numero = consumirDato();                        //Consumimos el numero
        printf("---->Consumidor, Dato %d: %d\n", i+1, numero);
        sem_post(&mutex);                                   //Se pone el semaforo a 1
        sem_post(&empty);                                   //Se aumenta empty, indicando que hay un espacio vacio mas en v                           
    }
    pthread_exit(NULL);                                     //Salimos de la hebra
}


void producirDato(int numero){                  //Funcion para meter datos en el buffer

    v[indiceProduccion] = numero;               //Asignamos el numero a v
    indiceProduccion = (indiceProduccion +1)%n; //Aumentamos en 1 el indice, y cuando lleguemos a la posicion final, volveremos al principio
    for(int i=0; i<n; i++){                     //Imprimimos los valores por pantalla
            printf("|%d", v[i]);
    }
    printf("|");
}

int consumirDato(){                                 //Funcion para sacar datos del buffer

    int numConsumido= v[indiceConsumicion];         //Guardamos el numero sacado en numConsumido
    v[indiceConsumicion] = '\0';                    //Vaciamos la posicion   
    indiceConsumicion = (indiceConsumicion +1)%n;   //Aumentamos en 1 el indice, y cuando lleguemos a la posicion final, volveremos al principio
        for(int i=0; i<n; i++){                     //Imprimimos los valores por pantalla
            printf("|%d", v[i]);
        }
    printf("|");
    return numConsumido;                            //Devolvemos el numero consumido
}



