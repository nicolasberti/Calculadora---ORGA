#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convertidor.h"
#include "constantes.h"

/** Variable global encargada de mostrar los pasos realizados por consola **/
int *mostrarPasos;

/** Declaración de funciones **/
int* guardarParametros(int *argc, char *argv[], char *numero, int *baseOrigen, int *baseDestino);

/** -- Definición de funciones -- **/

/**
    Función: guardarParametros
    Descripción: Guarda los parametros ingresados por la consola en las variables a utilizar.
    Parametros:
                int *argc: Longitud de los parametros ingresados por consola
                char *argv[]: Parametros ingresados por consola
                char *numero: Variable donde se almacenará el número.
                int *baseOrigen: Variable donde se almacenará la base de origen.
                int *baseDestino: Variable donde se almacenará la base de destino.

    Retorna 0 en caso de que se hayan guardado los parametros correctamente
    Retorna 1 si el usuario pidio ayuda sobre el programa.
    Retorna x (x > 1) en caso de que haya ocurrido un error.
**/
int* guardarParametros(int *argc, char *argv[], char *numero, int *baseOrigen, int *baseDestino){
    int *retorno;
    retorno = (int*) malloc(sizeof(int));
    *retorno = 0;
    /** Valida que los argumentos sean correctos --> Rango de los argumentos [3, 9] **/
    if(*argc < 3 || *argc > 9) {
        //mostrarUsoCorrecto;
        *retorno = 5;
    }
    else {
        int *i;
        i = (int*) malloc(sizeof(int));
        *i = 1; // Iterador de los argumentos recibidos como parametros. Comienzo desde i=1 para no leer el parametro "converter"

        /*
                Si argv[1] != -n entonces no cumple con el formato pedido.
                Aclaración: Después del <number> puede ir cualquier parametro en cualquier orden, pero al principio se tiene que respetar el orden.
        */
        if( strcmp(*(argv+1), "-n") !=0)
            *retorno = 2;

        while(*i < (*argc) && *retorno <= 1){

            /** Lee el número **/
            LEER("-n"){
                    (*i)++; // Itera nuevamente para leer el numero ya que seguido al -n siempre debe estar el número. De lo contrario el formato ingresado es inválido.
                    if(*(argv+*i) != NULL) {
                        if(strlen(*(argv+*i)) > MAXNUM)
                            *retorno = 3;
                        else strcpy(numero, *(argv+*i));
                    } else *retorno = 4;


            /** Lee la base origen **/
           } else LEER("-s"){
                    (*i)++; // Itera nuevamente para leer el numero ya que seguido al -s siempre debe estar la base origen. De lo contrario el formato ingresado es inválido.
                    if(*(argv+*i) != NULL) {
                        if( atoi(*(argv+*i)) >= 2 && atoi(*(argv+*i)) <= 16) {
                            *baseOrigen = atoi(*(argv+*i));
                        } else *retorno = 4;
                    } else *retorno = 4;


            /** Lee la base destino **/
           } else LEER("-d"){
                    (*i)++; // Itera nuevamente para leer el numero ya que seguido al -d siempre debe estar la base destino. De lo contrario el formato ingresado es inválido.
                    if(*(argv+*i) != NULL) {
                        if( atoi(*(argv+*i)) >= 2 && atoi(*(argv+*i)) <= 16) {
                            *baseDestino = atoi(*(argv+*i));
                        } else *retorno = 4;
                    } else *retorno = 4;


            /** Activa la ayuda del programa **/
           } else LEER("-h"){
                    *retorno = 1;

            /** Muestra por consola los pasos que se van haciendo para convertir al número **/
           } else LEER("-v"){
                    *mostrarPasos = 1;
           } else *retorno = 5; // Ante cualquier otro parametro, indica un error.
            (*i)++;
        }
        free(i);
    }
    return retorno;
}


int main(int argc, char *argv[]){
    int *baseOrigen, *baseDestino;
    char *numero; // Arreglo donde se almacenará el número. Se usará la aritmetica de punteros para manejarlo.
    int *retornado; // Retorno de la función guardarParametros
    /** Asignación de memoria **/

    baseOrigen = (int*) malloc(sizeof(int));
    baseDestino = (int*) malloc(sizeof(int));
    mostrarPasos = (int*) malloc(sizeof(int));
    numero = (char*) malloc(MAXNUM * sizeof(char));

    strcpy(numero, "");
    *baseOrigen = 10;
    *baseDestino = 10;
    *mostrarPasos = 0;

    /**
        Guardo los parametros ingresados en la línea de comandos en los punteros.
    **/
    retornado = guardarParametros(&argc, argv, numero, baseOrigen, baseDestino);

    if( *retornado == 0){
            if(*mostrarPasos == 1){ // Carteles a mostrar por consola si el usuario solicitó "-v"
                printf("Numero a convertir: %s\n", numero);
                printf("Base origen: %i | Base destino: %i\n", *baseOrigen, *baseDestino);
            }
            free(retornado);
            retornado = convertir(numero, baseOrigen, baseDestino, mostrarPasos);
            if(*retornado == 0) printf("\nNumero convertido -> %s (base %i)", numero, *baseDestino);
            else printf("Ocurrio un error y el numero no pudo ser convertido.");
    } else if(*retornado == 1){ // En caso de que el usuario pidió ayuda (parametro -h) se mostrará este cartel sin convertir el número.
        printf("\n%s: Convierte un numero de una base r a una base d.\n", *argv);
        printf("Si no se ingresa una base destino y/o origen entonces, se asumira que la base destino y/o origen es 10.\n");
        printf("El comando -v mostrara paso por paso la conversion del numero.\n");
    }
    else {
        printf("Los parametros ingresados no son validos. Intente nuevamente.\n");
        mostrarUsoCorrecto;
        printf("Para más ayuda utiliza el parametro -h");
    }

    /** Liberación de memoria **/
    free(baseOrigen); free(baseDestino); free(numero); free(mostrarPasos);

    if(*retornado <= 1) {
        /** Liberación de memoria **/
        free(retornado);
        /** El programa finaliza correctamente **/
        exit(EXIT_SUCCESS);
    } else {
        /** Liberación de memoria **/
        free(retornado);
        /** El programa finaliza con un error **/
        exit(EXIT_FAILURE);
    }

    return 0;
}
