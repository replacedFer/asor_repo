#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){

    /*
        $ touch Fichero  // creamos el fichero primero
        $ gcc -o eje11 eje11.c   // compilamos
        ./eje11 Fichero
    */
    struct stat sb;
    char rigido[50];
    char nombreSimbolico[50];
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        return -1;
    }

    switch (sb.st_mode & S_IFMT)
    {
    case S_IFREG:

              
                stpcpy(rigido,argv[1]);
                strcat(rigido,".hard");
                if(link(argv[1],rigido) == -1){
                    perror("Fallo al crear el enlace rigido \n");
                    return -1;
                }
                
                stpcpy(nombreSimbolico,argv[1]);
                strcat(nombreSimbolico,".sym");
                if(symlink(argv[1],nombreSimbolico) == -1){
                    perror("Fallo al crear el enlace simbolico \n");
                    return -1;
                }

        break;

    
    default: 
        printf("no es un fichero regular/n");break;
    }

    return 0;
}