#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
/*
    sigaction()
    Se trata de otro gestor de señales. La función sigaction permite modificar o examinar la acción asociada con una señal determinada. 
    Resulta de gran utilidad, puesto que permite averiguar la disposición respecto a una determinada señal sin modificarla: por ejemplo,
    si una señal va a ser ignorada, puede programarse una acción para capturarla, si no está siendo ignorada en un determinado instante,
    lo que resulta de gran utilidad en los procesos interactivos. La función sigaction sustituye a la función signal de las primeras versiones de Unix.
    Su definición es la siguiente:
            #include <signal.h>

              int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    
    donde el argumento signum es el número de la señal cuya acción se desea examinar o modificar.
    El puntero *act representa la función con la que se desea gestionar la señal, 
    y el puntero *oldact representa la función que estaba gestionando la señal.

    Si el puntero *act no es nulo, entonces se está modificando la acción, que pasa a ser la contenida en la dirección de *act. 
    Si el puntero *oldact no es nulo, la acción que va a ser modificada se almacena en *oldact. 
    La estructura empleada por esta función es:
                        truct sigaction {
                            void     (*sa_handler)(int);
                            void     (*sa_sigaction)(int, siginfo_t *, void *);
                            sigset_t   sa_mask;
                            int        sa_flags;
                            void     (*sa_restorer)(void);
                         };

    -  sa_handler será bien la constante SIG_DFL, para la acción por defecto, o bien SIG_IGN,
       para ignorar la señal o la dirección a una función que maneje esa señal. Su significado, por tanto, es el mismo que el del parámetro func en la función signal.
    -  sa_mask proporciona una máscara para las señales que deben ser bloqueadas durante la ejecución del gestor de señales.
    -  sa_flags es la combinación or de ninguna o alguna de las siguientes flags:

*/


// SIGTSTP         20 
//SIGINT           2

volatile int var_sigint =0;
volatile int var_sigtstp =0;
volatile int cont =0;
void contador(int s){
    
    if (s == SIGINT){
        var_sigint++;
        cont++;
    }

    if(s == SIGTSTP){
        var_sigtstp++;
        cont++;
    }
}
int main (int argc, char *argv[]){

    struct sigaction sa;

    sa.sa_handler = contador;
    sa.sa_flags = SA_RESTART;

    //instalamos el manejador
    sigaction(SIGINT,&sa,0);
    sigaction(SIGTSTP,&sa,0);

    while(cont < 10){}

    printf("El contador de SIGINT es: %d\n",var_sigint);
    printf("El contador de SIGTSTP es: %d\n",var_sigtstp);
    return 0;
}

/*

Ejecucion:
en otra terminal tras hacer el ./eje12 hacemos ps -a:
      usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ ps -a
        PID TTY          TIME CMD
        6775 pts/2    00:00:03 eje12
        6776 pts/1    00:00:00 ps


usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6775

EN el terminal donde se ejecuto el ./eje12 sale:
    usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3/Ejercicio12$ ./eje12 
    El contador de SIGINT es: 10
    El contador de SIGTSTP es: 0


***********************************************
OTRO EJEMPLO
***********************************************
TERMINAL 1:
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ ps -a
    PID TTY          TIME CMD
   6820 pts/2    00:00:03 eje12
   6823 pts/1    00:00:00 ps
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGINT 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGTSTP 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGTSTP 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGTSTP 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGTSTP 6820
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3$ kill -SIGTSTP 6820

TERMINAL 2:
usuarioso@usuarioso-virtualbox:~/asor_repo/asor_repo/Practica3/Ejercicio12$ ./eje12 
El contador de SIGINT es: 5
El contador de SIGTSTP es: 5
*/