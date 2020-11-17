#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * compra();
void * suministro();

int camisetas[5] = {1,2,3,4,5};

pthread_mutex_t mutex_acceso = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char * argv[]){

    srand(time(NULL)); //se establece el número semilla

    int n; //clientes

    printf("introduce el numero de clientes:\n");
    scanf("%i", &n);

    pthread_t clientes[n];

    int m; //proveedores y modelos de camiseta
    m = 5;

    pthread_t proveedores[m];

    for (int i = 0; i < n; i++){ pthread_create(&clientes[i], NULL, compra, NULL); } //llama a la funcion compra 
                                                                                     //por cada cliente n 
                                                                                     
    for (int i = 0; i < m; i++){ pthread_create(&proveedores[i], NULL, suministro, NULL); } //llama a la funcion suministro 
                                                                                            //por cada proveedor m

    for (int i = 0; i < n; i++){ pthread_join(clientes[i], NULL); } //va recibiendo los hilos que bajan 
                                                                                    //del pthreas_create

    for (int i = 0; i < m; i++) { pthread_join(proveedores[i], NULL); } //va recibiendo los hilos que bajan 
                                                                                    //del pthreas_create

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);
}

void * compra(){

    int modelo=(rand()%4)+1; //modelo de camiseta a comprar

    int cantidad=(rand()%10)+1; //cantidad de camiseta a comprar

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    printf("se va a comprar el modelo %i %i veces \n",modelo,cantidad);

    pthread_mutex_lock(&mutex_acceso);

        camisetas[modelo-1] = camisetas[modelo-1] - cantidad;

    pthread_mutex_unlock(&mutex_acceso);

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    pthread_exit(NULL); 

}

void * suministro(){

    int modelo=(rand()%4)+1; //modelo de camiseta a comprar

    int cantidad=(rand()%10)+1; //cantidad de camiseta a comprar

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    printf("se va a suministrar el modelo %i %i veces \n",modelo,cantidad);

    pthread_mutex_lock(&mutex_acceso);

        camisetas[modelo-1] = camisetas[modelo-1] + cantidad;

    pthread_mutex_unlock(&mutex_acceso);

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    pthread_exit(NULL); 

}