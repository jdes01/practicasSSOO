// Implemente un programa que cree un número n de hebras. Cada hebra creará 2 números aleatorios flotantes (consulte Moodle para la generación de aleatorios) 
// y guardará su suma en una variable para ello, que será devuelta a la hebra principal o llamadora (la que invocó pthread_create()).
// La hebra principal ira recogiendo los valores devueltos por las N hebras y los ira sumando en una variable no global cuyo resultado mostrará al final por pantalla.
// Para ver que los resultados finales son los que usted espera, muestre los 2 números que va creando cada hebra y su suma, 
// de forma que pueda comparar esas sumas parciales con la suma final que realizará el main() o hebra principal. 
// Utilice macros definidas y comprobación de errores en sus programas (errno y comprobación de valores devueltos en cada llamada, con sus posibles alternativas).

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * aleatorio();

int main(){

    int n = 2;
    float total = 0, * subtotal;
    pthread_t hilos[n];

    for (int i = 0; i < n; i++){ pthread_create(&hilos[i], NULL, (void *) aleatorio, NULL); } //crea las hebras y llama a la funcion aleatorio; el primer NULL
    //es por que queremos que tenga los atributos por defecto; el segundo NULL porque no queremos enviarle ningun parametro a la funcion aleatorio

    for (int i = 0; i < n; i++){
        
       pthread_join(hilos[i], (void **) &subtotal); //el hilo invocador espera a que acabe el hilo especificado; el primer parametro es el identificador de cada
       //hilo, y el segundo un puntero doble que apunta al valor devuelto por el thread que estamos esperando; es decir, lo que venga de f3 se metera en subtotal
       printf("Valor recibido: %f\n", *subtotal); //va escribiendo el subtotal (suma de los dos aleatorios creados por cada hilo) (f3)
       total = total + *subtotal; //va sumando el total de los subtotales
    }
    printf("la suma del total es: %f\n", total);

    exit(EXIT_SUCCESS);
     
}    

void * aleatorio(){

    float f1 = drand48()*10, f2 = drand48()*10;
    float * f3 = calloc(1, sizeof(float));
    *f3 = f1+f2;
    printf("%f + %f = %f\n", f1, f2, *f3);

    pthread_exit((void *) f3); //la funcion exit, que se ejecuta cuando termina la funcion llamada por la creacion del hilo, tiene como parametro
    // un puntero generico a los datos que queremos devolver como resultado, que sera recogido cuando se use un join con el identificador de cada thread
    //el hecho de que sea (void *) es por que puede ser puntero a cualquier cosa
}