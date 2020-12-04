#include <sys/types.h> // Añadir par que funcione
#include <unistd.h> // Añadir para que funcione
#include <pwd.h>// Añadir para que funcione

#include <stdio.h>
#include <errno.h>
#include <string.h>

/*
compilar 

gcc -c NombreArchivo.c
gcc -o nombreQueQuieras NombreArchivo.o
./ nombreQueQuieras 

-------
gcc -g -o ejercicio<X> ejercicio<x>.c 
*/
int main() 
{
   /*
       getuid() returns the real user ID of the calling process.
       geteuid() returns the effective user ID of the calling process.
   */

    printf("El ID del usuario real es:  %i\n",getuid());
    printf("El ID del usuario efectivo es: %i\n",geteuid());
   
 
    struct passwd *datos =getpwuid(getuid());

    if (datos == NULL){
        perror("fallo en la llamada getpwnam");
        return -1;
    }

    printf("El nombre del usuario es: %s\n",datos->pw_name);
    printf("el Directorio home es: %s\n",datos->pw_dir);
    printf("Descripcion de usuario: %s\n",datos->pw_gecos);

     return 0;
     
}