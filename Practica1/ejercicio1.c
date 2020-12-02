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
gcc -g -o ejercicio1 ejercicio1.c 
*/
int main() 
{
    int error;

    error = setuid(0);

    if ( error == -1){
        printf("Error: %s\n", strerror(errno));
        perror("Error en setuid");
        return -1;
    }
    return 0;
}