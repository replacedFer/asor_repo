/*
    Identificadores del proceso
        - Id proceso
        - Id padre
        - Id grupo
        - Sesion
    Num max ficheros que puede abrir el proceso y directorio de trabajo actual
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
 #include <stdlib.h>



int main (int argc, char *argv[]){
    //pid proceso
    pid_t proceso = getpid();
    printf("PID del proceso es: %d\n",proceso);

    //pid proceso padre
    pid_t padre= getppid();
    printf("PID del proceso padre es: %d\n",padre);

    //id del grupo
    pid_t grupo = getpgid(proceso);    
    printf("PID del grupo es: %d\n",grupo);

    //id sesion
    pid_t sesion = getsid(proceso); 
    
        if(sesion == -1){
            perror("Error en id de sesion");
            return -1;
        }
    printf("Id de la sesion es: %d\n",sesion);

    // Ruta del directorio actual
        // hacemos un malloc, porque no sabemos cuanto bytes puede ocuapr al ruta, he puesto 1024, porque no creo que la ruta supere ese tamaño
    char *buff = malloc(sizeof(char) * 1024);
    char *path = getcwd(buff,1024);

        if (path == NULL){
            perror("Error en obtener la ruta del directorio actual");
            return -1;
        }
    printf("La ruta del directorio actual es: %s\n",path);

    // Numero maximo de ficherosque puede abrir el proceso
    struct rlimit rlim;

    int a = getrlimit(RLIMIT_NOFILE, &rlim);
        if (a== -1){
            perror("Error en getrlimit \n");
        }
    
    printf("Numero maximo de ficheros que puede abrir el proceso: %ld\n",rlim.rlim_max);
    return 0;
}