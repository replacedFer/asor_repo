#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sysmacros.h>


int main(int argc, char *argv[]){

    struct stat sb;

     if (stat(argv[1], &sb) == -1) {
               perror("lstat");
               return -1;
           }
    // Numeros Major y Minor
    /*
    printf("Numeros Major y Minor: %d %d\n",major(sb.st_dev), minor(sb.st_dev));
    */
   printf("Numero major y minor:  [%lx,%lx]\n",(long) major(sb.st_dev), (long) minor(sb.st_dev));
    // Numero de inodo
    printf("I-node number:  %ld\n", (long) sb.st_ino);

    //Tipo de Fichero(directorio, enlace simbolico o fichero ordinario)
     printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

    //printf("Mode:                 %lo (octal)\n",(unsigned long) sb.st_mode);
    // La hora en que se accedio el fichero por ultima vez
    printf("Hora del ultimo acceso al fichero:     %d\n", ctime(&sb.st_atime));

    return 0;
}