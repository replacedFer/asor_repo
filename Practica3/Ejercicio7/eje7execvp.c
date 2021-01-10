#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]){


    if (execvp(argv[1], argv + 1) == -1) {
     printf("ERROR: No se ha ejecutado correctamente.\n");
     }

     printf("El comando terminó de ejecutarse.\n");

    return 0;
}