#include <sys/types.h>
#include <unistd.h>
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
    /*
    En realidad hay 134 errores*/
   for (int i= 0; i<255; i++){
       printf("Error: %s\n", strerror(i));
   }
    return 0;
}