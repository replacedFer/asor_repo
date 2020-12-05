#include <time.h> // Añadir para que funcione
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

    time_t tloc = time(NULL);
   
    if (tloc == -1){
        perror("error en la llamada time()");
        return -1;
    }

    printf("Tiempo en segundos desde Epoch: %li\n segundos", tloc );
     return 0;
     
}