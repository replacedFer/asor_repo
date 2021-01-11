#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int main (int argc, char *argv[]){

    sigset_t conjunto_senyales;

    //Creamos un conjunto vacio
   if(sigemptyset(&conjunto_senyales) == -1){
       perror("Error en sigemptyset()\n");
       return -1;
   } 

    //Añadimos las señales que queremos bloquear al conjunto
    sigaddset(&conjunto_senyales,SIGINT);
    sigaddset(&conjunto_senyales,SIGTSTP);
    /*
   if ((sigaddset(&conjunto_senyales,SIGINT) == -1) || (sigaddset(&conjunto_senyales,SIGTSTP) == -1) ){
       perror("Error en sigaddset()\n");
       return -1;
   }*/

    // Bloquemos las señales del conjunto
    sigprocmask(SIG_BLOCK,&conjunto_senyales,NULL);

    /*CODIGO PROTEGIDO FRENTE A SEÑALES SIGINT Y SIGTSTP*/

    //Obtener el valor de la variable de entorno SLEEP_SECS
    char *var_entorno = getenv("SLEEP_SECS");

    // Suspendemos la ejecucion con sleep
     sleep(atoi(var_entorno));


    //Comprobamos las señales pendientes
        sigset_t sig_pendientes;
        sigpending(&sig_pendientes);

    int senyal_init = sigismember(&sig_pendientes, SIGINT);
    int senyal_stop = sigismember(&sig_pendientes, SIGTSTP);
    if (senyal_init == -1 || senyal_stop == -1){
        perror("Error en sigismember()\n");
        return -1;
    }    
    // si se ha recibido señal de init --> se desbloquea
    if (senyal_init == 1){
       sigdelset(&sig_pendientes,SIGINT);
       printf("Se puede volver a usar SIGTSTP\n ");
    }
     // si se ha recibido señal de init --> se desbloquea
    if (senyal_stop == 1){
        sigdelset(&sig_pendientes,SIGTSTP);
        printf("Se puede volver a usar SIGTSTP\n ");
    }

    // DESBLOQUEMOS EL CONJUNTO DE SEÑALES --> CODIGO YA NP ESTA PROTEGIDO FRENTE A LAS SEÑALES INIT Y STOP
    sigprocmask(SIG_UNBLOCK,&conjunto_senyales,NULL);
    return 0;
}
