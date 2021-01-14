#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main (int argc, char **argv){

    int p_h[2];
    int h_p[2];
    return 0;

    if (pipe(p_h) == -1){
        perror("Error en la llamada pipe_p_h()\n");
        return -1;
    }

    if (pipe(h_p) == -1){
        perror("Error en la llamada pipe()_h_p\n");
        return -1;
    }

    pid_t pid = fork();

    switch (pid)
    {
     case -1:
         perror("Error en la llamada fork()\n");
         return -1;
         break;
     case 0: // hijo
        close(p_h[1]);//cierro el de escritura 
        close(h_p[0]);// cierro el de lectura 
        char buff[255];

        read(p_h[1], buff, 255);


        // soy yo que se me peta el ordfenador


         break;
    default: // padre
        close(p_h[0]);// cierro el de lectura
        close(h_p[1]);// cierro el de escritura 
            char buff[255];
         if (read(0, &buff, 255) == -1 ){
             perror("Error en read() del padre\n");
             return -1;
         }

        if(write(p_h[0],&buff,255) == -1){
             perror("Error en write() del padre\n");
             return -1;
         } 
        while (1){

        }

        break;
    }



}