#include <stdlib.h>
#include <stdio.h>

/*
Para que sea sencialla la implemenmtacion hay que ejecutar de la siguente manera
./eje7system "ls -l"


****************
sino hay que unir los comando en una cadena, pero eso complica la implementacion

int main(int argc, char **argv){

  if (argc < 2) {
    printf("ERROR: Introduce el comando.\n");
    return -1;
  }

  //Concatenamos todo lo que nos pase por pantalla:
  //Calculamos el tamaño del sting para reservar espacio en memoria:
  int cmdLen = 1;
  int i;
  for (i = 1; i < argc; i++)
    cmdLen += strlen(argv[i]) + 1;
  char *cmd = malloc(sizeof(char)*cmdLen);
  strcpy(cmd, "");

  //Concatenamos todos los argumentos
  for (i = 1; i < argc; i++) {
    strcat(cmd, argv[i]);
    strcat(cmd, " ");
  }

  //Ejecutamos el comando correspondiente a la entrada por argumentos
  if (system(cmd) == -1) {
    printf("ERROR: No se ha ejecutado correctamente.\n");
  }

  printf("El comando terminó de ejecutarse.\n");


  return 0;
}

*/
int main (int argc, char *argv[]){

    int ret = system(argv[1]);
    if (ret == -1){
        perror("Error en la llamada system");
        return -1;
    }

     printf("El comando terminó de ejecutarse.\n");
    return 0;
}