#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
Caracteristicas de un demonio:
    -Se ejecuta en segundo plano.
    -Esta en su propia sesion y grupo --- > Se consigue creando un nuevo proceso con el fork y una sesion nueva.
*/

int main (int argc, char *argv[]){


    pid_t pid = fork();

    if(pid == -1){
        perror("Error en el fork");
        exit(1);
        
    }else if( pid == 0){ // proceso hijo

        printf("\n********ESTAMOS EN EL PROCESO HIJO******** \n");
        // creamos una sesion nueva
        pid_t sesion = setsid();
        if (sesion == -1){
            perror("Error en crear la nueva sesion\n");
            exit(1);
        }

        int df1 = open("/tmp/daemon.out",O_RDWR | O_CREAT |O_TRUNC,0777);
        int df2 = open("/tmp/daemon.err",O_RDWR | O_CREAT|O_TRUNC,0777);
        int df3 = open("/dev/null",O_RDWR | O_CREAT|O_TRUNC,0777);

        if (df1 == -1 || df2== -1 || df3== -1){
            perror("error en uno de los open()\n");
            return -1;
        }

        int dp1 = dup2(df1,1);//rediriguir la salida estandar
        int dp2 = dup2(df2,2);//rediriguir la salida estandar de error
        int dp3 = dup2(df3,0);//rediriguir la entrada estandar

        if (dp1 == -1 || dp2== -1 || dp3== -1){
            perror("error en uno de los dup2()\n");
            return -1;
        }

        // Hacemos que ejecute lo que nos pasan
        if (execvp(argv[1], argv + 1) == -1) {
         printf("ERROR: No se ha ejecutado correctamente.\n");
        }
    }else{ // proceso padre
        printf("********ESTAMOS EN EL PROCESO padre******** \n");
    }

    return 0;
}