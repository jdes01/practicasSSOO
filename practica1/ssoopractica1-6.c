// Realizar un programa que capture la señal de alarma, de manera que imprima la cadena “RING” pasados 5 segundos, 
// después pasados otros 3 segundos y por último cada segundo. Implementar esto último, 
// utilizando un bucle infinito que vaya imprimiendo el número de timbrazos. 
// Pasados 4 timbrazos, el proceso se debe parar utilizando para ello la función kill().


#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //API de POSIX, para usar fork()
#include <sys/types.h> //define algunas estructuras de daros como pid_t, libreria necesaria para fork()
#include <errno.h> //para utilizar la variable errno (errores)
#include <sys/wait.h> //para utilizar la funcion wait()

void ring (int signo) { printf("RING\n"); }

void funcion(int segundos){ 

    alarm(segundos); // genera la señal SIGALRM 
    pause(); //hace una pausa que dura lo que haya recibido alarm (en concreto, el parametro 'segundos')
    }

int main(){

    signal(SIGALRM, ring); //signal espera a funciones que activen la SIGALRM para ejecutar la funcion ring

    printf("Alarma en 5 segundo\n");
    funcion(5); //llama a la funcion ring

    printf("Alarma en 3 segundo\n");
    funcion(3);

    for (int i = 0; i < 90; i++){

        printf("Alarma en 1 segundo\n");
        funcion(1);

        printf("TIMBRAZOS: %d\n", i+1);
        
        if (i==3) kill(getpid(),9);
        
    }

    return 0;
    
}