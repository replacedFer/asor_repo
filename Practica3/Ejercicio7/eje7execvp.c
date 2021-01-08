#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    /*
    int ret = execvp(argv[0], argv+1);
    if (ret == -1){
        perror("Error en la llamada execvp");
        return -1;
    }*/

    if (execvp(argv[1], argv + 1) == -1) {
    printf("ERROR: No se ha ejecutado correctamente.\n");
  }

     printf("El comando terminó de ejecutarse.\n");

    return 0;
}