#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char ** argv){


    int fd = open("tuberia",O_WRONLY,0777);
    if (fd == -1){
        perror("Error al abrir el fichero\n");
        return -1;
    }

    int tam = strlen(argv[1]);

    if (write(fd,argv[1],tam) == -1){
        perror("Error al escribiren  el fichero\n");
        return -1;
    }
    close(fd);

    return 0;
}

/*
TERMIANAL 1:
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio4$ mkfifo tuberia
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio4$ ls
eje4.c  tuberia
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio4$ gcc -o eje4 eje4.c 
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio4$ ./eje4 HolaMundo


TERMIANAL 2:

usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica4/Ejercicio4$ cat tuberia 
HolaMundo
*/