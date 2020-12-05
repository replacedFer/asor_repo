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
    struct tm *estructura;
    /*
    OJO
    Hay que pasarle a localtime un time
    */
    estructura = localtime(&tloc);
    int anioRestado = estructura->tm_year;
    printf("Año: %i\n", 1900 + anioRestado);
    return 0;
}