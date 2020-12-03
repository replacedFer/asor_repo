#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h> // biblioteca añadida para ejercicio 5 (uname())

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
   int error;
   struct utsname estructura;

   error =uname(&estructura);

   if (error == -1 ){
       perror("Error en la llamada uname()");
       return -1;
   }

   printf("System name: %s\n",estructura.sysname);
   printf("NodeName: %s\n",estructura.nodename);
   printf("Release: %s\n",estructura.release);
   printf("Version: %s\n",estructura.version);
   printf("Machine: %s\n",estructura.machine);
    return 0;
}