// pidiendo el numero n de procesos totales, crear un abanico de procesos de la forma 1padre - 3hijos


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //API de POSIX, para usar fork()
#include <sys/types.h> //define algunas estructuras de daros como pid_t, libreria necesaria para fork()
#include <errno.h> //para utilizar la variable errno (errores)
#include <sys/wait.h> //para utilizar la funcion wait()

int main(){

    int n, status;
    pid_t pid; //variable tipo pid_t

    printf("introduce el numero de procesos:\n");
    scanf("%i", &n);

    for (int i = 0; i < n; i++){

        switch ( fork() ){

        // la funcion fork genera un proceso hijo identico al padre, y devuelve:
        // el PID del hijo si es el padre el que llama a fork, 0 si es un hijo el que llama a fork y -1 en caso de 
        // no poder crear una copia del proceso

        case -1: 
            perror("fork error:\n");
            fprintf(stderr, "errno:  %i\n", errno); //la variable errno se modifica cuando fork() devuelve -1
            exit(EXIT_FAILURE);
            break;

        case 0: //como el padre su fork es el pid del hijo, nunca entra aqui; en cambio, los hijos si
            printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
            exit(EXIT_SUCCESS); //aqui mueren los hijos
        }
    }

    for (int i = 0; i < n; i++){

        pid = wait(&status); //aqui van llegando los padres; los hijos murieron en el exit y estan en modo; devolvera el pid del hijo
        // la funcion wait hara que el proceso padre espere a que su hijo termine; devuelve un valor positivo y equivalente al 
        // ID del hijo si este termina. Si la llamada falla o no hay hijos, devuelve -1

        if (pid > 0){ //exito en la invocacion
        
            if      (WIFEXITED(status))   printf("1 el hijo %i ha sido finalizado con la señal %i\n", pid, WEXITSTATUS(status));
            else if (WIFSIGNALED(status)) printf("2 el hijo %i ha sido finalizado con la señal %i\n", pid, WTERMSIG(status));
            else if (WIFSTOPPED(status))  printf("3 el hijo %i ha sido finalizado con la señal %i\n", pid, WSTOPSIG(status));
        
        }
        else{ //ha habido un error en la invocacion, devolveremos un macro
            printf("fallo en la invocacion\n");
            exit(EXIT_FAILURE);
        }
         
    }
    
    exit(EXIT_SUCCESS);

}