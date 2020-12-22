//Programa que suma valores aleatorios obtenidos por n hebras en la variable par (si estamos en hebra con indice par) 
//o en la variable impar en el otro caso

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

int indiceGlobal = 0;                                   //Indice de la hebra
int par = 0;                                            //Suma de valores generados por los hilos pares
int impar = 0;                                          //Suma de valores generados por los hilos impares
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      //Mutex


int main( int argc, const char * argv[]){
    
    if (argc != 2){                                         //Comprobamos que el usuario ejecute el programa de manera correcta
        printf("Error, ejecucion: ./ej2 nºDeHebras\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));          //Plantamos la semilla de los numeros aleatorios
    int n = atoi(argv[1]);      //Guardamos el numero de hebras que queremos crear en n
    int *resultado;             //Resultado donde guardaremos la suma de los valores generados por cada hebra
    pthread_t thread[n];        //Creamos un vector para guardar las n hebras 

    for(int i=0; i<n; i++){
        
        //Creacion de hebras con comprobacion de error

        if (pthread_create(&thread[i], NULL, suma, (void *) &indiceGlobal)){  
           
            printf("Error, no se ha podido crear la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i=0; i<n; i++){

        //Recogida de hebras con comprobacion de error

        if (pthread_join(thread[i], (void **) &resultado )){

            printf("Error, no se ha podido recoger la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    printf("Valor total de par %d\n", par);         //Imprimimos el valor de par
    printf("Valor total de impar %d\n", impar);     //Imprimimos el valor de impar

    exit(EXIT_SUCCESS);     //Salimos del programa si todo ha ido segun lo previsto
}

//Funcion que recibe el indice de la hebra

void * suma(void * n){               
        
    int *indiceLocal= (int *)n;             //Guardamos el indice n en indiceLocal haciendo un casting
    int *suma = malloc(sizeof(int *));      //Reservamos memoria para la variable que devolvemos al salir de la hebra
    
    //Bucle que generara 5 numeros aleatorios y los sumara guardandolos en *suma

    for (int i = 0; i < 5 ; i++){                               
                        
        int x = rand()%11;      //Generamos numero aleatorio del 0 al 10
        *suma = *suma + x;      //Aumentamos la suma que devolveremos al salir de la hebra
    }
    
    //Lock del semaforo con comprobacion de error

    if (pthread_mutex_lock(&mutex)){                  

        printf("Error en bloqueo de mutex. Codigo de error %d", errno);
        exit(EXIT_FAILURE);
    }

    indiceGlobal++;     //Aumentamos en uno el indiceGlobal, para que en la siguiente hebra se tenga el indice siguiente
       
    printf("Hebra %ld con indice %d\n", pthread_self(), *indiceLocal);
    printf("Valor de la suma en %d es %d\n", *indiceLocal, *suma);    //Imprimimos por pantalla el valor de la suma de la hebra

    //Entramos aqui si el indice es par
        
    if(*indiceLocal%2==0){ par = par + *suma; }     //Aumentamos el valor de la variable global par                                                  
        
    //Entramos aqui si el indice es impar

    else{ impar = impar + *suma; }      //Aumentamos el valor de la variable global impar                                                              
                                                         
    //Unlock del semaforo con comprobacion de error

    if (pthread_mutex_unlock(&mutex)){      

        printf("Error en bloqueo de mutex. Codigo de error %d", errno);
        exit(EXIT_FAILURE);
    }

    pthread_exit((void *)suma);     //Salimos de la hebra devolviendo suma                                            
}