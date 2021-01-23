
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main (int argc, char **argv){
    //Para seleccionar el tipo de funciones que quiero o direcciones(familia, tipo de socket...) 
	struct addrinfo filtro;
	struct addrinfo *resultado;
	// unicializamos la estructura

	//memset() pone a partir de la direccion de memoria todos los baytes al entero que se le pasa el valor que queremos  
	memset(&filtro,0,sizeof(struct addrinfo)); //pone a 0 toda la estructura
	//direccion sin especificar
	filtro.ai_flags = AI_PASSIVE; // sino ponemos ai_passive nos devuelve local host
	filtro.ai_family = AF_UNSPEC; // coge tando ipv4 como ipv6
	
	int rc = getaddrinfo(argv[1],NULL,&filtro,&resultado);// me devuelve los posibles resultados en una lista
	if (rc !=0){
	    printf("[ERROR] getaadrinfo: %s\n", gai_strerror(rc));
	    return -1;
	}
	
	for (struct addrinfo *i = resultado;i!=NULL; i=i->ai_next){
		char host[NI_MAXHOST];
		
		// para cada resultado que me devuelva la representacion numerica del host
		getnameinfo(i->ai_addr, i->ai_addrlen,host,NI_MAXHOST,0,0,NI_NUMERICHOST);

		printf("HOST: %s FAMILIA: %d  SOCKET: %d\n",host,i->ai_family, i->ai_socktype );
	}

	freeaddrinfo(resultado);
return 0;

    return 0;
}