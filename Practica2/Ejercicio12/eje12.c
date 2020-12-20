#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 

int main(int argc, char *argv[]){

    int fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd == -1){
        perror("fallo al abrir el fichero");
        return -1;
    }
    int res = dup2(fd,1);
    if (res == -1){
        perror("Fallo al duplicar descriptor");
        return -1;
    }

    printf("Hola esto es una prueba \n");
    printf("Hola esto es una prueba \n");
    printf("Hola esto es una prueba \n");
    printf("Hola esto es una prueba \n");

    if (close(fd) == -1){
        perror("Fallo al cerrar el descriptor");
        return -1;
    }

    return 0;
}