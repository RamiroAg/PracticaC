/*
 ============================================================================
 Name        : ProbandoSockets.c
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

#define IP 			"127.0.0.1"
#define PUERTO		"6667"
#define PACKAGESIZE	1024

//Programa Cliente
int main(void) {
	struct addrinfo hints;
	struct addrinfo *serverInfo;
	int serverSocket;

	memset(&hints, 0, sizeof(hints));	//Primero llena con ceros la estructura para después cargarla
	hints.ai_family = AF_UNSPEC;		//Permite que la máquina se encargue de verificar si usamos IPv4 o IPv6
	hints.ai_socktype = SOCK_STREAM;	//Indica que usaremos protocolo TCP

	getaddrinfo(IP, PUERTO, &hints, &serverInfo);	//Carga en serverInfo los datos de la conexión

	//Creamos el socket con socket()
	serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	//Me conecto
	connect(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo); 			//Libero memoria porque no se precisa más

	//Envío de paquetes
	int enviar = 1;
	char message[PACKAGESIZE];

	printf("Conectando al servidor, Bienvenido al sistema, ya puede enviar mensajes. \n Escriba 'exit' para salir \n");
	while(enviar){
		fgets(message, PACKAGESIZE, stdin);		//Lee lo que escribimos por consola

		if(!strcmp(message, "exit\n"))
			enviar = 0;							//Valido si el usuario quiere salir

		if(enviar)
			send(serverSocket, message, strlen(message) + 1, 0);
	}

	close(serverSocket);

	return EXIT_SUCCESS;
}
