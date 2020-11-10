// Realizar un programa padre que expanda un hijo y al cual le envíe cada 1 segundo una señal personalizada 
// de usuario SIGUSR1. El hijo debe imprimir un mensaje en pantalla cada vez que recibe la señal del padre, 
// tratándola en una función aparte llamada tratarSennal(). Enviados 5 mensajes los procesos deben salir. 
// Utiliza las funciones signal() y kill().
// RECUERDE, LOS SLEEPS() SON A MODO DIVULGATIVO. NO USAR SLEEPS() PARA SINCRONIZAR SUS PROCESOS, 
// ESO ES CUESTIÓN DEL NÚCLEO DEL SISTEMA OPERATIVO.


#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //API de POSIX, para usar fork()
#include <sys/types.h> //define algunas estructuras de daros como pid_t, libreria necesaria para fork()
#include <errno.h> //para utilizar la variable errno (errores)
#include <sys/wait.h> //para utilizar la funcion wait()

void tratarSennal (int signo) { printf("recibida señal tratada por hijo"); }

int main(void){

    pid_t pid, pidHijo;
    int status, o=0;

    switch (pid) {

    case -1:

        exit(EXIT_FAILURE);
        break;

    case 0:

        signal(SIGUSR1, tratarSennal);

        for (int i = 0; i < 5; i++) pause();
        
        exit(EXIT_SUCCESS);
        break;    
    
    default:

        for (int i = 0; i < 5; i++){

            sleep(1);
            kill(pid,SIGUSR1);
        }

        pidHijo=wait(&status);
        break;
    }
}