/*
 * Codigo.c
 *
 *  Created on: 14/4/2016
 *      Author: Guti
 */

#include<stdio.h>
#include<stdlib.h>

/*
	*   Retorna un String nuevo que es la concatenación
	*   de los dos Strings pasados por parámetro
	*   Ejemplo:
	*   char* nombre = "Ritchie";
	*   char* saludo = string_concat("Hola ", nombre);
	*   =>
	*   saludo = "Hola Ritchie"
	*/
	char* string_concat(char* cadena1[], char* cadena2[]){

		char* result;
		result = strcat(cadena1, cadena2);
		return result;
	}

int main(int argc, char** argv){
	char* cadena1 = "Hola ";
	char* cadena2 = "guti";

	printf(string_concat(cadena1, cadena2));

	return EXIT_SUCCESS;
}
