#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char **argv){

    int p_h[2];
    int h_p[2];
    

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
        int cont = 0;
        char a[1];
        int salir = 0;

        while (!salir){
             // Leo lo que me llega de papa
            int size = read(p_h[0], &buff, 255);
            if (size == -1){
                perror("Error en la llamada read() del hijo\n");
            return -1;
            }
            //Escribo lo que me llegade papa por la salida estandar
           // write(1,"[HIJO] Me has mandado ?:  ",30);
            write(1,&buff,size);
            sleep(1);  

            if (cont < 10){
                // le mando al padre que estoy listo para seguir recibiendo
                a[0] = 'l';
                write(h_p[1],&a,sizeof(char));
                cont++;
            }else{
                // le mando el de finalizacion
                write(h_p[1],"q",sizeof(char));
                salir = 1;
            }            
        }
         close(p_h[0]);
         close(h_p[1]);        
         break;


    default: // padre
    
        close(p_h[0]);// cierro el de lectura
        close(h_p[1]);// cierro el de escritura 


            char buff2[255];
            char confirmacion[1];
            int res_entrada;
          
            do{     // leemos de la entrada estandar
                   printf("[Padre] Lo que te quiero enviar es: \n");
                   res_entrada = read(0, &buff2, 255);
                    if ( res_entrada == -1 ){
                        perror("Error en read() del padre\n");
                        return -1;
                    }
                      buff2[res_entrada] ='\0';
                    // se lo pasamos por la tuberia al hijo
                    if(write(p_h[1],&buff2,res_entrada) == -1){
                        perror("Error en write() del padre\n");
                        return -1;
                    }
                    //el padre lee la confirmacion del hijo
                     read(h_p[0],&confirmacion[0],sizeof(char));

            } while (confirmacion[0] != 'q');

         close(p_h[1]);
         close(h_p[0]);

        break;
    }



}