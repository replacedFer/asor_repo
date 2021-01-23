
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

  /******************************************************************
     *          TRATAR UNA CONEXION ESPECIFICA
	******************************************************************/
void haz_conexion(int cliente_sd){
   
    char buffer[80];
    while(1){
        
        //recivimos de un socket especifico
        int bytes = recv(cliente_sd,buffer,79,0/*(quiero que sea bloquenate)*/);
        if (bytes == 0){// para cerrar la conexion
            printf("Fin de la conexion\n");
            close(cliente_sd);
            break;
        }
        buffer[bytes] = '\0';
        //enviamos desde un socket especifico
        printf("\tmensaje: %s\n",buffer);

        send(cliente_sd,buffer,bytes,0 );
    }

}



int main(int argc,char **argv){



 /*****************************************************************
  *                 INICIALIZACION DEL SOCKET
 /******************************************************************/
//Para seleccionar el tipo de funciones que quiero o direcciones(familia, tipo de socket...) 
	struct addrinfo filtro;
	struct addrinfo *resultado;//variable donde se me guardael resultado
   
   
	//memset() pone a partir de la direccion de memoria todos los baytes al entero que se le pasa el valor que queremos  
	memset(&filtro,0,sizeof(struct addrinfo)); //pone a 0 toda la estructura
	// unicializamos la estructura para filtrar lo que quiero
	filtro.ai_flags = AI_PASSIVE; // sino ponemos ai_passive nos devuelve local host
	filtro.ai_family = AF_UNSPEC; // coge tando ipv4 como ipv6
	filtro.ai_socktype = SOCK_STREAM;//TCP

    /*
    getaddrinfo()-->traduce la direccion y el puerto a binario y prepara las estructuras
                    necesarias para crear el socket
    */ 
	int rc = getaddrinfo(argv[1],argv[2],&filtro,&resultado);// me devuelve los posibles resultados en una lista
	if (rc !=0){
	    printf("[ERROR] getaadrinfo: %s\n", gai_strerror(rc));
	    return -1;
	}

    // CREAMOS EL SOCKET(descriptor)
	int sd = socket(resultado->ai_family, resultado->ai_socktype,0);

    //asociar el socket(sd) con la direccion binaria y puerto de la direccion  donde quiero escucachar
	bind(sd,resultado->ai_addr,resultado->ai_addrlen);
    freeaddrinfo(resultado);
    /******************************************************************
		con esto ya tenemos un socket abierto escuchando en la direccion y puerto que yo quiero
	******************************************************************/

    /*
                        GESTION DE LA CONEXION
        como TCP esta orientado a conexion tenemos a nivel de programador gestionar
        estas conexiones

        1º) Inicializar las colas de conexiones en el sistema
                - llamada listen() en un socket hace qu el socket pueda recibir 
                llamadas entrantes e inicializa una cola de conexiones
    */

   listen(sd,16/*16 es el minimo*/);// se pueden gestionar 16 conexiones

   //bucle para aceptar mas de una conexion
    while(1){

        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        struct sockaddr_storage cliente_addr; // se usa el storage porque he puesto que puedo tener ipv4 como ipv6 
        socklen_t cliente_len = sizeof(struct sockaddr_storage);
        

        // aceptamos la peticion del cliente correspondiente a la conexion
        int cliente_sd = accept(sd,(struct sockaddr *)&cliente_addr, &cliente_len);
        /* HAY QUE GESTIONAR ERRORES DE ACCEPT() Y LISTEN()*/
        //Ver quien se ha conectado
        getnameinfo((struct sockaddr *)&cliente_addr, cliente_len,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);
        //el servidor imprime l nombre el host que del cliente y su puerto
        printf("Conexion desde el Host: %s PUERTO: %s \n",host,serv);

        haz_conexion(cliente_sd);

    }





    return 0;
}