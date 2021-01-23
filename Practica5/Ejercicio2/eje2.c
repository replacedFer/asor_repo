
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

int main (int argc, char **argv){
    //Para seleccionar el tipo de funciones que quiero o direcciones(familia, tipo de socket...) 
	struct addrinfo filtro;
	struct addrinfo *resultado;
    char buffer[80];

	// unicializamos la estructura
	//memset() pone a partir de la direccion de memoria todos los baytes al entero que se le pasa el valor que queremos  
	memset(&filtro,0,sizeof(struct addrinfo)); //pone a 0 toda la estructura
	//direccion sin especificar
	filtro.ai_flags = AI_PASSIVE; // sino ponemos ai_passive nos devuelve local host
	filtro.ai_family = AF_UNSPEC; // coge tando ipv4 como ipv6
	filtro.ai_socktype = SOCK_DGRAM;//UDP

	int rc = getaddrinfo(argv[1],argv[2],&filtro,&resultado);// me devuelve los posibles resultados en una lista
	if (rc !=0){
	    printf("[ERROR] getaadrinfo: %s\n", gai_strerror(rc));
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
	
    // voy a estar recibiendo y enviando 
    while(1){
    char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
    struct sockaddr_storage cliente_addr; // se usa el storage porque he puesto que puedo tener ipv4 como ipv6 
    socklen_t cliente_len = sizeof(struct sockaddr_storage);
    int bytes = recvfrom(sd,buffer,79,0/*(quiero que sea bloquenate)*/, (struct sockaddr *)&cliente_addr, &cliente_len);


    buffer[bytes] = '\0';


    //Ver quien se ha conectado
	getnameinfo((struct sockaddr *)&cliente_addr, cliente_len,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST | NI_NUMERICSERV);
    //el servidor imprime l nombre el host que del cliente y su puerto
	printf("HOST: %s PUERTO: %s \n",host,serv);

    //Obtenemos la fecha y hora
    time_t tiempo = time(NULL);
    struct tm *tlocal = localtime(&tiempo);
   
    char hora[64];
    char fecha[64];
  
    switch (buffer[0])
    {
     //devolver al cliente la hora   
    case 't': 
        
        int b = strftime(hora,0,"%H:%M:%S",tlocal);
        hora[b]='\0';
        sendto(sd,hora,b,0,(struct sockaddr *)&cliente_addr, cliente_len );
              
        break;
     //devolver al cliente la fecha      
    case 'd':
        
        int a = strftime(fecha,0,"%d/ %m/ %y",tlocal);
        fecha[a]='\0';
        sendto(sd,fecha,a,0,(struct sockaddr *)&cliente_addr, cliente_len );
        break;    
    case 'q':
        printf("Salienddo...\n");
        return 0;
        break;
    default:
        printf("Comando no soportado: %d\n",buffer[0]);
        break;
    }


    }

return 0;

    return 0;
}