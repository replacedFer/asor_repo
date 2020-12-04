#include <sys/types.h> // Añadir par que funcione
#include <unistd.h> // Añadir para que funvcione
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
       getuid() returns the real user ID of the calling process.
       geteuid() returns the effective user ID of the calling process.
   */

   printf("El ID del usuario real es:  %i\n",getuid());
   printf("El ID del usuario efectivo es: %i\n",geteuid());
 
     return 0;
}