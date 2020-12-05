#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/*
compilar 

gcc -c NombreArchivo.c
gcc -o nombreQueQuieras NombreArchivo.o
./ nombreQueQuieras 

-------
gcc -g -o ejercicio<X> ejercicio<x>.c 
*/
int main() 
{

    int MAX_BUCLE = 1000000;

    int var=0;
    struct timeval inicio;
    int error1 = gettimeofday(&inicio,NULL);

    if (error1 == -1){
        printf("Error: %s\n", strerror(errno));
        perror("Error en setuid");
        return -1;
    }
    
     int inicioBucle = inicio.tv_usec;
    for (int i =0; i< MAX_BUCLE;i++){
        var+=1;
    }

    struct timeval fin;
    int error2 = gettimeofday(&fin,NULL);

     if (error2 == -1){
        printf("Error: %s\n", strerror(errno));
        perror("Error en setuid");
        return -1;
    }
    int finBucleBucle = fin.tv_usec;
    printf("El bucle ha tardado: %i microsegundos \n",(finBucleBucle - inicioBucle));
     return 0;
     
}