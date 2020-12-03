#include <sys/types.h>
#include <unistd.h> // para la llamada pathconf necesitamos esta biblioteca
#include <stdio.h>
#include <errno.h>
#include <string.h>
//#include <sys/utsname.h> // biblioteca añadida para ejercicio 5 (uname())

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
  
   
    long MaxEnlaces =pathconf(".",_PC_LINK_MAX);
    long MaxTamPath =pathconf(".",_PC_PATH_MAX);
    long MaxNameFichero =pathconf(".",_PC_NAME_MAX);


    if (MaxEnlaces == -1|| MaxTamPath== -1 || MaxNameFichero == -1){
         printf("Error: %s\n", strerror(errno));
         perror("Error en en alguna llamada del sysconf");
         return -1;
    }

   printf("Número máximo de enlaces: %ld\n",MaxEnlaces);
   printf("Tamaño máximo de una ruta: %ld\n",MaxTamPath);
   printf("Tamaño máximo de un nombre de un fichero: %ld\n",MaxNameFichero);

    return 0;
}