//programa donde se crean dos hijos, uno abrira la calculadora y otro que abra un editor de texto con N ficheros pasados
// como argumentos (el padre tendra que esperar a los hijos); usar la familia de funciones exec();


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //API de POSIX, para usar fork()
#include <sys/types.h> //define algunas estructuras de daros como pid_t, libreria necesaria para fork()
#include <errno.h> //para utilizar la variable errno (errores)
#include <sys/wait.h> //para utilizar la funcion wait()


int main(int argc, char * argv[]){

    int status;
    pid_t pid[2]; //variable tipo pid_t

    switch ( fork() ){

            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); //la variable errno se modifica cuando fork() devuelve -1
                exit(EXIT_FAILURE);
                break;

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                //execlp("cd", "cd", "/System/Applications/Calculator.app/Contents/MacOS", argv[1], NULL);
                //execlp("open", "open", "Calculator", NULL);        
                //no consigo abrir la calculadora        
                exit(EXIT_SUCCESS); //aqui mueren los hijos
            }

    switch ( fork() ){

            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); //la variable errno se modifica cuando fork() devuelve -1
                exit(EXIT_FAILURE);
                break;

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                execlp("open", "open", "-t", argv[1], argv[2], NULL); 
                exit(EXIT_SUCCESS); //aqui mueren los hijos
            }

    pid[0]=wait(&status);
    pid[1]=wait(&status);


        
}


