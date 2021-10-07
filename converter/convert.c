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
        *retorno = 5;
    }
    else {
        int *i;
        i = (int*) malloc(sizeof(int));
        *i = 1; // Iterador de los argumentos recibidos como parametros. Comienzo desde i=1 para no leer el parametro "converter"

        /**
            Si argv[1] != -n entonces no cumple con el formato pedido.
            Aclaración: Después del <number> puede ir cualquier parametro en cualquier orden, pero al principio se tiene que respetar el orden.
        **/
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
        // Libero la memoria del contador
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


    if( *retornado == 0){ // Leyó correctamente los parametros

            if(*mostrarPasos == 1){ // Carteles a mostrar por consola si el usuario solicitó "-v"
                printf("Numero a convertir: %s\n", numero);
                printf("Base origen: %i | Base destino: %i\n", *baseOrigen, *baseDestino);
            }
            // Libero lo retornado ya que re-utilizo la variable para saber si la conversión se pudo realizar.
            free(retornado);
            retornado = convertir(numero, baseOrigen, baseDestino, mostrarPasos);

            if(*retornado == 0)
                printf("\nNumero convertido -> %s (base %i)", numero, *baseDestino);
            else {
                 printf("Ocurrio un error (numero: %i) y el numero no pudo ser convertido.", *retornado);
                 printf("\nDescripcion del error: ");
                 switch(*retornado){
                    case 1: printf("La parte entera y/o la parte fraccionaria supera el maximo de digitos permitidos."); break;
                    case 2: printf("El numero no es valido."); break;
                 }
            }

    } else if(*retornado == 1){ // El usuario pidió ayuda.

        // En caso de que el usuario pidió ayuda (parametro -h) se mostrará este cartel sin convertir el número.

        printf("\n%s: Convierte un numero de una base r a una base d.\n", *argv);
        mostrarUsoCorrecto;

        printf("\nDescripcion de los parametros:");
        printf("\n -n <numero>: Indica el numero que se convertira.");
        printf("\n -s <base_origen>: Indica la base origen del numero que se convertira. (Bases permitidas [2,16])");
        printf("\n -d <base_destino>: Indica la base destino del numero ingresado. (Bases permitidas [2,16])");
        printf("\n     Si no se ingresa una base destino y/o origen entonces, se asumira que la base destino y/o origen es 10.");
        printf("\n -v: Muestra paso por paso la conversion del numero.\n\n");

    }
    else {

        // El usuario ingresó parametros inválidos, asi que se muestra el uso correcto sin explicar cada parametro.
        printf("\nLos parametros ingresados no son validos. Intente nuevamente.\n");
        mostrarUsoCorrecto;
        printf("Para mas ayuda utiliza el parametro -h. (Sin ingresar parametros invalidos)\n");
        printf("Por ejemplo, ingrese %s -n 0 -h\n", *argv);

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
