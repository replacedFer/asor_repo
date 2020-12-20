#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <dirent.h>
#include <sys/stat.h>


int main (int argc, char *argv[]){

    DIR *directorio = opendir(argv[1]);
    char buffer[PATH_MAX];
    int totalBytes =0;
    struct stat datoFichero;

    if(directorio == NULL){
        perror("fallo al abrir el directorio ");
        return -1;
    }

    struct dirent *structDir;

    while((structDir = readdir(directorio)) != NULL){
        
        int a;
        char path[PATH_MAX];

        strcpy(path,argv[1]);
        strcat(path,"/");
        strcat(path,structDir->d_name);

        if(stat(path, &datoFichero) == -1){
            perror("Fallo en stat()");
            return -1;
        }

        totalBytes += datoFichero.st_size;


        if (S_ISDIR(datoFichero.st_mode)){
                printf("Nombre del Directorio: %s\n /", structDir->d_name);
        }else 
        if (S_ISREG(datoFichero.st_mode)){
                printf("Nombre del fichero: %s\n", structDir->d_name);
        }else 
        if (S_ISLNK(datoFichero.st_mode)){
                a = readlink(structDir->d_name,buffer,PATH_MAX);
                printf("Nombre del ficheroSimbolico: %s -> %s\n", structDir->d_name, buffer);
        }
     
    }

    totalBytes= totalBytes / 1024;

    printf("Tamaño de los ficheros: %d\n" , totalBytes);
    closedir(directorio);

    return 0;
}