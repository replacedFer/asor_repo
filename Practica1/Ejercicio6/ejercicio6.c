#include <sys/types.h>
#include <unistd.h> // para la llamada sysconf necesitamos esta biblioteca
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
  
   
    long MaxArgumentos =sysconf(_SC_ARG_MAX);
    long MaxHijos =sysconf(_SC_CHILD_MAX);
    long Maxficheros =sysconf(_SC_OPEN_MAX);

    if (MaxArgumentos == -1|| MaxHijos== -1 || Maxficheros == -1){
         printf("Error: %s\n", strerror(errno));
         perror("Error en en alguna llamada del sysconf");
         return -1;
    }

   printf("Número máximo de argumentos: %ld\n",MaxArgumentos);
   printf("Número máximo de hijos: %ld\n",MaxHijos);
   printf("Número máximo de ficheros abiertos por proceso: %ld\n",Maxficheros);

    return 0;
}