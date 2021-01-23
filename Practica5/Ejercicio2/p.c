#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


/*
	udp direccion_escuchar puerto_escuchar    donde mi servidor va a escuchar 

	TERMINAL 1:
	./udp localhost 8080
	
	TERMINAL2:
	nc -u localhost 8080
	HOLA ESTO ES UN MENSAJE DE UDP

*/

int main(int argc, char **argv){
	
	char buffer[80];
	//Para seleccionar el tipo de funciones que quiero o direcciones(familia, tipo de socket...) 
	struct addrinfo filtro;
	struct addrinfo *resultado;
	// unicializamos la estructura

	//memset() pone a partir de la direccion de memoria todos los baytes al entero que se le pasa el valor que queremos  
	memset(&filtro,0,sizeof(struct addrinfo)); //pone a 0 toda la estructura
	//direccion sin especificar
	filtro.ai_flags    = AI_PASSIVE; // sino ponemos ai_passive nos devuelve local host
	filtro.ai_family   = AF_UNSPEC;  // coge tando ipv4 como ipv6
	filtro.ai_socktype = SOCK_DGRAM; // TCP
	
	//conseguir representacion binaria del socket que quiero escuchar  
	int rc = getaddinfo(argv[1],argv[2],&filtro,&resultado);// me devuelve los posibles resultados en una lista
	if (rc !=0){
	    printf("[ERROR] getaadrinfo: %s\n", gai_srterror(rc));
	    return -1;
	}
	
	
	// CREAMOS EL SOCKET(descriptor)
	int sd = socket(resultado->ai_family, resultado->ai_socktype,0);
	//asociar el socket(sd) con la direccion binaria y puerto de la direccion  donde quiero escucachar
	bind(sd,resultado->ai_addr,resultado->ai_addrlen);

	/*
		con esto ya tenemos un socket abierto escuchando en la direccion y puerto que yo quiero
	*/

	freeaddrinfo(resultado);
	while(1){// voy a estar recibiendo y enviando 
	
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	struct sockaddr_storage cliente_addr; // se usa el storage porque he puesto que puedo tener ipv4 como ipv6 
	socklen_t cliente_len = sizeof(struct sockaddr_storage);
	 int bytes = recvfrom(sd,buffer,79,0/*quiero que sea bloquenate)*/, (struct sockaddr *)&cliente_addr, &cliente_len);

	buffer[bytes]='\0';

	//Ver quien se ha conectado
	getnameinfo((struct sockaddr *)&cliente_addr, cliente_len,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);
	printf("HOST: %s PUERTO: %s  MSG %s \n",host,serv,buffer);

	// envio al host
	sendto(sd,buffer,bytes,0,(struct sockaddr *)&cliente_addr, &cliente_len );

	}
















	

	
return 0;
}


/********************************EJECUCION*************************************************
	./addr www.google.com https

	./addr www.facebook.com 80

	./addr localhost 80
/**********************************************************************************/