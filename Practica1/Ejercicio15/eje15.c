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
int main(int argc, char *argv[])
{
    char outstr[200];
    time_t tloc = time(NULL);
    struct tm *estructura;
    /*
    OJO
    Hay que pasarle a localtime un time
    */
    estructura = localtime(&tloc);
    if (estructura == NULL) {
        perror("localtime");
        return -1;
    }

     if (strftime(outstr, sizeof(outstr), argv[1], estructura) == 0) {
            fprintf(stderr, "strftime returned 0");
            return -1;
    }

    printf("Result string is \"%s\"\n", outstr);
    return 0;
}