#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> 


int main(int argc, char *argv[]){

    int fd = open(argv[1],O_WRONLY | O_CREAT , 0777);

    if(fd == -1){
        perror("error al abrir el fichero ");
        return -1;
    }

    if (lockf(fd, F_TEST,0) == -1){
        perror("error en lockf");
        return -1;
    }
    return 0;
}