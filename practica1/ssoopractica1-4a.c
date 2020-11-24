//Cree un programa que reciba por la linea de argumentos un número y calcule el factorial de ese número. Compílelo y compruebe su funcionamiento. 
//A partir de ahí cree otro programa aparte que reciba dos números enteros como parámetros en la linea de argumentos y cree dos procesos hijos, 
//de manera que cada uno calcule el factorial de uno de los números usando el ejecutable creado anteriormente (“./a.out 3 5”), 
//use para ello la familia de funciones exec(). En el programa que calcula el factorial ponga un sleep(1) entre los cálculos parciales 
//para poder observar en consola como se van ejecutando los dos procesos que se lanzarán en paralelo.
//RECUERDE, LOS SLEEPS() SON A MODO DIVULGATIVO. NO USAR SLEEPS() PARA SINCRONIZAR SUS PROCESOS, ESO ES CUESTIÓN DEL NÚCLEO DEL SISTEMA OPERATIVO.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //API de POSIX, para usar fork()
#include <sys/types.h> //define algunas estructuras de daros como pid_t, libreria necesaria para fork()
#include <errno.h> //para utilizar la variable errno (errores)
#include <sys/wait.h> //para utilizar la funcion wait()

int factorial(int n);

int main(int argc, char * argv[]){

    int status;
    pid_t pid; //variable tipo pid_t

    int n=0;

    for (int i = 0; i < argc-1; i++){

        switch ( fork() ){

            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); //la variable errno se modifica cuando fork() devuelve -1
                exit(EXIT_FAILURE);

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                sleep(1);
                n = atoi(argv[i+1]);
                printf("el factorial de %i es %i\n", n, factorial(n));
                sleep(1);
                exit(EXIT_SUCCESS); //aqui mueren los hijos
        }

        pid=wait(&status);
    }

    
}

int factorial(int n){

   int fact=1;

   if( n<0 ) return 0;

   if(n==0) return 1;

   for (int i = 1; i <= n; ++i) {fact = fact*i;} 
      
   return fact;
   
}