#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(){


umask(0027);
// Importate, hay que añadir un 0 delante de los permisos
int fd = open("FicheroCreado",O_CREAT,0645);
    if(fd == -1){
        perror("Fallo al crear el fichero");
    }
    return 0;
}