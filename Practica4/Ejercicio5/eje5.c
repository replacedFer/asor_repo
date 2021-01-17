#include <sys/select.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
/*
**************************************** PARA EJECUTAR ******************************************
Crear las dos tunerias conn mkfifo <nombre_tuberia>

luego:
        TERMINAL 1:
        usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio5$ gcc -o eje5 eje5.c 
        usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio5$ ./eje5 

            (cuando en el terminal2 me mande el mensaje, en este terminal sale esto)
            [TUBERIA2]:  Esto es el mensaje

            [TUBERIA1]:  Esto es el mensaje


        TERMINAL 2: En este terminal iremos pasando los mensajes y estos mensajes se veran en el terminal 1

        usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio5$ echo "Esto es el mensaje" > tuberia1
        usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio5$ echo "Esto es el mensaje" > tuberia2
*/


// CREAR UNA TUBERIA SIN NOMMRE EN EL TERMINAL 1: mkfifo tuberia
int main (int argc, char **argv){
    /* 00    --> O_RDONLY
       04000 --> O_NONBLOCK    
    */
    int fd1 = open("tuberia1",00 | 04000);
    int fd2 = open("tuberia2",00 | 04000);

    if(fd1 == -1 || fd2 == -1 ){
        perror("Error en lka apertura de la tuberia open()\n");
        return -1;
    }

    char buff_tuberia1[256];
    char buff_tuberia2[256];

    do
    {   //creamos el conjunto
        fd_set fds;
        

        //inicializamos los conjuntos como vacios
        FD_ZERO(&fds);
        FD_ZERO(&fds);

        //añadimos un desriptor al conjunto
        FD_SET(fd1,&fds);
        FD_SET(fd2,&fds);

        //Comprobacion de que descriptor en mayor  para pasarselo el select()
        int mayor_fd = fd1;
        if(fd1<fd2){
            mayor_fd = fd2;
        }

        if (select(mayor_fd +1,&fds,0,0,0) == -1){
            perror("Error en el select()\n");
            return -1;
        }
        // si esta lista la tuberia 1
        if(FD_ISSET(fd1,&fds)){ 
            int bytes = read(fd1,buff_tuberia1,255);
            buff_tuberia1[bytes] = '\0';

            if(bytes == 0){
                fd1 = open("tuberia1",00 | 04000);
                if(fd1 == -1 ){
                perror("Error en open()\n");
                return -1;
             }
            }else{
                printf("[TUBERIA1]:  %s\n", buff_tuberia1);
            }
             
        }
        // si esta lista la tuberia 2
        if(FD_ISSET(fd2,&fds)){ 
            int bytes = read(fd2,buff_tuberia2,255);
            buff_tuberia2[bytes] = '\0';

            if(bytes == 0){
                fd2 = open("tuberia2",00 | 04000);
                if(fd2 == -1 ){
                perror("Error en open()\n");
                return -1;
             }
            }else{
                printf("[TUBERIA2]:  %s\n", buff_tuberia2);
            }
             
        }
        
    } while (1);
    

    return 0;
}