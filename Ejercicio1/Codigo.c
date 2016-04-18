/*
 * Codigo.c
 *
 *  Created on: 14/4/2016
 *      Author: Guti
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
	*   Retorna un String nuevo que es la concatenación
	*   de los dos Strings pasados por parámetro
	*   Ejemplo:
	*   char* nombre = "Ritchie";
	*   char* saludo = string_concat("Hola ", nombre);
	*   =>
	*   saludo = "Hola Ritchie"
	*/

//Declaración de la funciones
char *string_concat(char *s,char *t);

//Programa principal
int main(int argc, char** argv){

	char *cadena1="Hola ";
	char *cadena2="mundo!";

	char *resultado = string_concat(cadena1,cadena2);
	printf("cat: %s\n", resultado);               /* 2: you can use %s to print a string */
	free(resultado);

	return EXIT_SUCCESS;
}


char *string_concat(char *start,char *end)
{
    char *result = malloc(strlen(start)+strlen(end)+1);    /* 3: you will have to reserve memory to hold the copy. */
    int ptr =0, temp = 0;                   /* 4 initialise some helpers */

    while(start[temp]!='\0'){                  /* 5. use the temp to "walk" over string 1 */
        result[ptr++] = start[temp++];
    }
    temp=0;
    while(end[temp]!='\0'){                   /* and string two */
        result[ptr++]=end[temp++];
    }
    return result;
}
