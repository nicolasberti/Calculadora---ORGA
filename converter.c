#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convertidor.h"

// Macros para mejor claridad al leer el código

/** Lee el argumento A y verifica B **/
#define LEER(A) if( strcmp(*(argv+i), A) ==0)

#define MAXNUM              25 // Caracteres máximos del número contando la coma.

/**
        Fases del programa
        Fase 1: El usuario ingresa por consola los parametros
        Fase 2: El programa lee los parametros y los almacena.
        Fase 2.1: El programa TERMINA e indica como se debe usar ya que el usuario pidió ayuda (-h)
        Fase 2.2: El programa valida que el número ingresado corresponda a la base solicitada.
        Fase 3: El programa convierte el número.
        Fase 4: Si el número es correcto (no supera los digitos establecidos) lo muestra por pantalla.

**/

/** Variable global encargada de mostrar los pasos realizados por consola **/
int mostrarPasos = 0;

/** Declaración de funciones **/
int guardarParametros(int *argc, char *argv[], char *p_numero, int *baseOrigen, int *baseDestino);

/** -- Definición de funciones -- **/
//
/**
    Función: guardarParametros
    Descripción: Guarda los parametros ingresados por la consola en las variables a utilizar.
    Parametros:
                int *argc: Longitud de los parametros ingresados por consola
                char *argv[]: Parametros ingresados por consola
                char *p_numero: Dirección de memoria del número.

    Retorna 0 si el usuario no pidió ayuda sobre el programa.
    Retorna 1 en caso contrario.
**/
int guardarParametros(int *argc, char *argv[], char *p_numero, int *baseOrigen, int *baseDestino){
    int retorno;
    retorno = 0;
    /** Valida que los argumentos sean correctos --> Rango de los argumentos [3, 9] **/
    if(*argc < 3 || *argc > 9)
        exit(EXIT_FAILURE);
    else {
        int i;
        i = 1; // Comienzo desde i=1 para no leer el parametro "converter"
        /*
                Si argv[1] != -n entonces no cumple con el formato pedido.
                Aclaración: Después del <number> puede ir cualquier parametro en cualquier orden, pero al principio se tiene que respetar el orden.
        */
        if( strcmp(*(argv+1), "-n") !=0)
            exit(EXIT_FAILURE);
        while(i < (*argc)){
            /** Lee el número **/
            LEER("-n"){
                    i++; // Itera nuevamente para leer el numero ya que seguido al -n siempre debe estar el número. De lo contrario el formato ingresado es inválido.
                    if(*(argv+i) != NULL) {
                        if(strlen(*(argv+i)) > MAXNUM) exit(EXIT_FAILURE);
                        int j;
                        for(j = 0; j < strlen(*(argv+i)); j++){
                            *(p_numero+j) = (*(argv+i))[j];
                        }
                    } else exit(EXIT_FAILURE);
            /** Lee la base origen **/
           } else LEER("-s"){
                    i++; // Itera nuevamente para leer el numero ya que seguido al -s siempre debe estar la base origen. De lo contrario el formato ingresado es inválido.
                    if(*(argv+i) != NULL) {
                        if( atoi(*(argv+i)) >= 2 && atoi(*(argv+i)) <= 16) {
                            *baseOrigen = atoi(*(argv+i));
                        } else exit(EXIT_FAILURE);
                    } else exit(EXIT_FAILURE);
            /** Lee la base destino **/
           } else LEER("-d"){
                    i++; // Itera nuevamente para leer el numero ya que seguido al -d siempre debe estar la base destino. De lo contrario el formato ingresado es inválido.
                    if(*(argv+i) != NULL) {
                        if( atoi(*(argv+i)) >= 2 && atoi(*(argv+i)) <= 16) {
                            *baseDestino = atoi(*(argv+i));
                        } else exit(EXIT_FAILURE);
                    } else exit(EXIT_FAILURE);
            /** Activa la ayuda del programa **/
           } else LEER("-h"){
                    retorno = 1;
            /** Muestra por consola los pasos que se van haciendo para convertir al número **/
           } else LEER("-v"){
                    mostrarPasos = 1;
           } else exit(EXIT_FAILURE);
            i++;
        }
    }
    return retorno;
}


int main(int argc, char *argv[]){

    /** Por defecto, la base origen y la base destino es 10. **/
    int baseOrigen, baseDestino;
    baseOrigen = 10;
    baseDestino = 10;

    /** El número se almacenará en una cadena de caracteres ya que, puede contener letras si la base está en [11, 16] **/
    char numero[MAXNUM];
    char *p_numero; // Puntero al número. Guarda la dirección de memoria del primer digito del número.
    p_numero = numero;

    /** Existen dos posibilidades, que el usuario pida ayuda o no. En el caso de pedir ayuda, el número no se convierte **/
    if( guardarParametros(&argc, argv, p_numero, &baseOrigen, &baseDestino) == 0){
            if(mostrarPasos == 1){ // Carteles a mostrar por consola si el usuario solicitó "-v"
                printf("[main] Numero a convertir: %s\n", numero);
                printf("[main] Base origen: %i | Base destino: %i\n", baseOrigen, baseDestino);
            }
            convertir(p_numero, &baseOrigen, &baseDestino, &mostrarPasos);
            printf("Numero convertido -> %s (base %i)", numero, baseDestino);
    } else {
            // Mostrar ayuda del programa
    }
    exit(EXIT_SUCCESS);
    return 0;
}
