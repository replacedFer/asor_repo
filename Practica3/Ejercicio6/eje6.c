#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>



void imprimirDatos(){
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
            return ;
        }
    printf("Id de la sesion es: %d\n",sesion);

    // Ruta del directorio actual
        // hacemos un malloc, porque no sabemos cuanto bytes puede ocuapr al ruta, he puesto 1024, porque no creo que la ruta supere ese tamaño
    char *buff = malloc(sizeof(char) * 1024);
    char *path = getcwd(buff,1024);

        if (path == NULL){
            perror("Error en obtener la ruta del directorio actual");
            return ;
        }
    printf("La ruta del directorio actual es: %s\n",path);

    // Numero maximo de ficherosque puede abrir el proceso
    struct rlimit rlim;

    int a = getrlimit(RLIMIT_NOFILE, &rlim);
        if (a== -1){
            perror("Error en getrlimit \n");
        }
    
    printf("Numero maximo de ficheros que puede abrir el proceso: %ld\n",rlim.rlim_max);
    free(path);

    return;
}

int main (int argc, char *argv[]){


    pid_t pid = fork();

    if(pid == -1){
        perror("Error en el fork");
        exit(1);
        
    }else if( pid == 0){ // proceso hijo

        printf("\n********ESTAMOS EN EL PROCESO HIJO******** \n");
        // creamos una sesion nueva
        pid_t sesion = setsid();

        //Cambiamos directorio de trabajo
          char *path = "/tmp" ;
            int res = chdir(path);
            if(res == -1){
                perror("Error al cambiar la ruta del directorio");
            }

        if (sesion == -1){
            perror("Error en crear la nueva sesion\n");
            exit(1);
        }
        imprimirDatos();
       // exit(0);
    }else{ // proceso padre
        printf("********ESTAMOS EN EL PROCESO padre******** \n");
    }

    return 0;
}

/*

si el proceso padre termina antes que lo haga el hijo el proceso hijo no desaparece totalmente sino que queda en un estado conocido como zombie. Se soluciona poniendo en el padre un 
wait(), con esto hacemos que el padre espere a la finalizacion de los hijos.

*/