/*
 ============================================================================
 Name        : Server.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


#define PUERTO "6667"
#define BACKLOG 5			// Define cuantas conexiones vamos a mantener pendientes al mismo tiempo
#define PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar

int main(){
	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		//Delego en la máquina la elección entre IPv4 o IPv6
	hints.ai_flags = AI_PASSIVE;		//Asigna el address del localhost: 127.0.0.1
	hints.ai_socktype = SOCK_STREAM;	//Usamos protocolo TCP

	getaddrinfo(NULL, PUERTO, &hints, &serverInfo);		//Paso NULL en el parámetro de IP porque antes indiqué que use el localhost en AI_PASSIVE

	//Necesito conocer cuáles serán las conexiones que quieren establecerse con el server
	int listeningSocket;
	listeningSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	//Asociar el socket de escucha a un puerto
	bind(listeningSocket, serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo);

	//Escuchar
	listen(listeningSocket, BACKLOG);		//listen() es una llamada al sistema bloqueante

	//El sistema esperará hasta que reciba una conexión entrante
	//Aceptar conexión entrante y crear un nuevo socket
	//Nota: Para que el listenningSocket vuelva a esperar conexiones, necesitariamos volver a decirle que escuche, con listen();
	 //*				En este ejemplo nos dedicamos unicamente a trabajar con el cliente y no escuchamos mas conexiones.

	struct sockaddr_in addr;			//Estructura que contendrá los datos de la conexión del cliente
	socklen_t addrlen = sizeof(addr);

	int socketCliente = accept(listeningSocket, (struct sockaddr *) &addr, &addrlen);


	//Espero bloqueado los mensajes del cliente
	//Cuando el cliente cierra la conexion, recv() devolvera 0.
	char package[PACKAGESIZE];
	int status = 1;						//Maneja el estado de los recieve

	printf("Cliente conectado. Esperando mensajes:\n");

	while(status != 0){
		status = recv(socketCliente, (void*) package, PACKAGESIZE, 0);
		if(status != 0)
			printf("%s", package);
	}

	//Terminado el intercambio de paquetes, cerramos todas las conexiones
	close(socketCliente);
	close(listeningSocket);

	return 0;
}
