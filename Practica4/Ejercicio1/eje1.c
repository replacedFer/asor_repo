#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */


int main(int argc, char ** argv){

   
    // array de descriptores de fichero
    int fd[2];

    if (pipe(fd) == -1){
        perror("Error en la llamada pipe()\n");
        return -1;
    }

     pid_t pid = fork();

     switch (pid)
     {
     case -1:
         perror("Error en la llamada fork()\n");
         return -1;
         break;
    
     case 0: // El hijo reedireccionara la entrada estandar al extremo de lectura
        if (dup2(fd[0],0) == -1){
            perror("Error en el dup2 del hijo.\n");
            return -1;
        }

        if (close(fd[0]) == -1){
             perror("Error en el close fd[0] del hijo.\n");
            return -1;
        }

        if (close(fd[1]) == -1){
             perror("Error en el close fd[1] del hijo.\n");
            return -1;
        }

        execlp(argv[3],argv[3],argv[4],NULL);
        break;

     
     default:// el padre reedireccionara la salida estandar al extremo de escritura
        if (dup2(fd[1],1) == -1){
            perror("Error en el dup2 del hijo.\n");
            return -1;
        }

        if (close(fd[0]) == -1){
             perror("Error en el close fd[0] del hijo.\n");
            return -1;
        }

        if (close(fd[1]) == -1){
             perror("Error en el close fd[1] del hijo.\n");
            return -1;
        }

        execlp(argv[1],argv[1],argv[2],NULL);
         break;
     }

    return 0;
}