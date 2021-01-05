#include <sched.h>
#include <stdio.h>
//#include <unistd.h>


int main(int argc, char *argv[]){

    // pid == 0  -> proceso actual

    // obtenre la politica de planificacion
    int politica = sched_getscheduler(1);
    if ( politica == -1){
        perror("Error en obtener la politica de planificacion");
        return -1;
    }

    // obteemos la prioridad del proceso actual
    struct sched_param dato;
    int prioridad = sched_getparam(0, &dato);
     if ( prioridad == -1){
        perror("Error en obtener los datos de prioridad");
        return -1;
        }

    int maxPrioridad = sched_get_priority_max(politica);
    if ( maxPrioridad == -1){
        perror("Error en obtener la maxima prioridad");
        return -1;
        }  

    int minPrioridad = sched_get_priority_min(politica);
    if ( minPrioridad == -1){
        perror("Error en obtener la minima prioridad");
        return -1;
        } 


      switch(politica) {
            case SCHED_OTHER : printf("Politica de planificacion  SCHED_OTHER \n");  break;
            case SCHED_FIFO  : printf("Politica de planificacion  SCHED_FIFO \n"); break;
            case SCHED_RR    : printf("Politica de planificacion  SCHED_RR  \n");break;
            default          : printf("Politica de planificacion  OTRA \n"); break;
        }        
    printf("Prioridad del proceso: %d\n", dato.sched_priority);
    printf("Valor maximo de la prioridad: %d, valor minimo de la prioridad:  %d\n",maxPrioridad,minPrioridad);
    return 0;
}


