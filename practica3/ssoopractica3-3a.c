#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

#define n 5 

int v[n];      

int indiceConsumicion = 0;                    
int indiceProduccion = 0;

sem_t mutex;                                   
sem_t full;                                    
sem_t empty;                                    


int main(){

    srand(time(NULL));                  

    sem_init(&mutex, 0, 1);             
    sem_init(&full, 0, 0);              
    sem_init(&empty, 0, n);           

    pthread_t threadProductor;        
    pthread_t threadConsumidor;        

    if(pthread_create(&threadProductor, NULL, productor, NULL)){ printf("Error %d\n", errno); exit(EXIT_FAILURE); }

    if(pthread_create(&threadConsumidor, NULL, consumidor, NULL )){ printf("Error %d\n", errno); exit(EXIT_FAILURE); }
    
    if (pthread_join(threadProductor, NULL)){ printf("Error %d\n", errno); exit(EXIT_FAILURE); }
    
    if (pthread_join(threadConsumidor, NULL)){ printf("Error %d\n", errno); exit(EXIT_FAILURE); }
   
    for(int i=0; i<n; i++){ printf("Valor %d del buffer: %d\n", i+1, v[i]); }
    
    exit(EXIT_SUCCESS);                                        
}


void * productor(){ 

    for (int i=0; i<10; i++){   
        
        sem_wait(&empty);                                                          
        sem_wait(&mutex);  
        
        int numero = rand()%101;    
        
        producirDato(numero);
        
        printf("Productor:\n");
        printf("Dato %d: %d\n", i+1, numero);
        
        sem_post(&mutex);                                  
        sem_post(&full);                                   
    }
    
    pthread_exit(NULL);                                   
}

void * consumidor(){  
    
    for (int i=0; i<10; i++){ 
        
        sem_wait(&full);                                    
        sem_wait(&mutex);    
        
        int numero = consumirDato();
        
        printf("Consumidor:\n");
        printf("---->Consumidor, Dato %d: %d\n", i+1, numero);
        
        sem_post(&mutex);                             
        sem_post(&empty);                                                
    }
    
    pthread_exit(NULL);                 
}


void producirDato(int numero){    

    v[indiceProduccion] = numero;    
    
    indiceProduccion = (indiceProduccion +1)%n; 
    
    for(int i=0; i<n; i++){ printf("%d ", v[i]); }
}

int consumirDato(){                      

    int numConsumido= v[indiceConsumicion];   
    
    v[indiceConsumicion] = '\0';  
    
    indiceConsumicion = (indiceConsumicion +1)%n;   
    
    for(int i=0; i<n; i++){ printf("%d ", v[i]); }

    return numConsumido;   
}



