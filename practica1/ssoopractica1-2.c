//programa en el que un hijo acaba inmediatamente (imprimira su ID y terminara); El padre dormira (con la funcion sleep()) durante x segundos 
//y luego acabara con exit(EXIT_SUCCESS) sin recoger al hijo. Con otro terminal ejecutamos la orden "ps -a", para ver como uno de los procesos aparece como
// zombie o perdido. Cuando muere el padre sin haber tomado el codigo del hijo con wait, el hijo es heredado por el proceso init que lo elimina del sistema

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //API de POSIX, para usar fork()
#include <sys/types.h> //define algunas estructuras de daros como pid_t, libreria necesaria para fork()
#include <errno.h> //para utilizar la variable errno (errores)
#include <sys/wait.h> //para utilizar la funcion wait()

int main(){

        switch ( fork() ){

        case -1: 
            perror("fork error:\n");
            fprintf(stderr, "errno:  %i\n", errno); //la variable errno se modifica cuando fork() devuelve -1
            exit(EXIT_FAILURE);
            break;

        case 0: //como el padre su fork es el pid del hijo, nunca entra aqui; en cambio, los hijos si
            printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
            break;//los hijos no mueren, sino que solo se salen del switch con el break

        default:
            sleep(10);
            exit(EXIT_FAILURE);
        }

}