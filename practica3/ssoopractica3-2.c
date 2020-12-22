#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

int indiceGlobal = 0;                                   
int par = 0;                                      
int impar = 0;                                  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;    


int main( int argc, const char * argv[]){
    
    if (argc != 2){      
        
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));      
    
    int n = atoi(argv[1]);     
    
    int *resultado;          
    
    pthread_t thread[n];        

    for(int i=0; i<n; i++){

        if (pthread_create(&thread[i], NULL, suma, (void *) &indiceGlobal)){  
           
            printf("Error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i=0; i<n; i++){
        
        if (pthread_join(thread[i], (void **) &resultado )){

            printf("Error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    printf("Valor del par %d\n", par);      
    printf("Valor del impar %d\n", impar);

    exit(EXIT_SUCCESS);     
}

void * suma(void * n){               
        
    int *indiceLocal= (int *)n;            
    int *suma = malloc(sizeof(int *));    

    for (int i = 0; i < 5 ; i++){                               
                        
        int x = rand()%11;      
        *suma = *suma + x; 
    }

    if (pthread_mutex_lock(&mutex)){                  

        printf("Error %d", errno);
        exit(EXIT_FAILURE);
    }

    indiceGlobal++; 
       
    printf("Hebra %ld con indice %d\n", pthread_self(), *indiceLocal);
    printf("La suma en %d es %d\n", *indiceLocal, *suma); 

    if(*indiceLocal%2==0){ par = par + *suma; }                                              
   

    else{ impar = impar + *suma; }                                                               

    if (pthread_mutex_unlock(&mutex)){      

        printf("Error %d", errno);
        exit(EXIT_FAILURE);
    }

    pthread_exit((void *)suma);                                           
}
