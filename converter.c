#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convertidor.h"

// Macros para mejor claridad al leer el c�digo

/** Lee el argumento A y verifica B **/
#define LEER(A) if( strcmp(*(argv+i), A) ==0)

#define MAXNUM              25 // Caracteres m�ximos del n�mero contando la coma.

/**
        Fases del programa
        Fase 1: El usuario ingresa por consola los parametros
        Fase 2: El programa lee los parametros y los almacena.
        Fase 2.1: El programa TERMINA e indica como se debe usar ya que el usuario pidi� ayuda (-h)
        Fase 2.2: El programa valida que el n�mero ingresado corresponda a la base solicitada.
        Fase 3: El programa convierte el n�mero.
        Fase 4: Si el n�mero es correcto (no supera los digitos establecidos) lo muestra por pantalla.

**/

/** Variable global encargada de mostrar los pasos realizados por consola **/
int mostrarPasos = 0;

/** Declaraci�n de funciones **/
int guardarParametros(int *argc, char *argv[], char *p_numero, int *baseOrigen, int *baseDestino);

/** -- Definici�n de funciones -- **/
//
/**
    Funci�n: guardarParametros
    Descripci�n: Guarda los parametros ingresados por la consola en las variables a utilizar.
    Parametros:
                int *argc: Longitud de los parametros ingresados por consola
                char *argv[]: Parametros ingresados por consola
                char *p_numero: Direcci�n de memoria del n�mero.

    Retorna 0 si el usuario no pidi� ayuda sobre el programa.
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
                Aclaraci�n: Despu�s del <number> puede ir cualquier parametro en cualquier orden, pero al principio se tiene que respetar el orden.
        */
        if( strcmp(*(argv+1), "-n") !=0)
            exit(EXIT_FAILURE);
        while(i < (*argc)){
            /** Lee el n�mero **/
            LEER("-n"){
                    i++; // Itera nuevamente para leer el numero ya que seguido al -n siempre debe estar el n�mero. De lo contrario el formato ingresado es inv�lido.
                    if(*(argv+i) != NULL) {
                        if(strlen(*(argv+i)) > MAXNUM) exit(EXIT_FAILURE);
                        int j;
                        for(j = 0; j < strlen(*(argv+i)); j++){
                            *(p_numero+j) = (*(argv+i))[j];
                        }
                    } else exit(EXIT_FAILURE);
            /** Lee la base origen **/
           } else LEER("-s"){
                    i++; // Itera nuevamente para leer el numero ya que seguido al -s siempre debe estar la base origen. De lo contrario el formato ingresado es inv�lido.
                    if(*(argv+i) != NULL) {
                        if( atoi(*(argv+i)) >= 2 && atoi(*(argv+i)) <= 16) {
                            *baseOrigen = atoi(*(argv+i));
                        } else exit(EXIT_FAILURE);
                    } else exit(EXIT_FAILURE);
            /** Lee la base destino **/
           } else LEER("-d"){
                    i++; // Itera nuevamente para leer el numero ya que seguido al -d siempre debe estar la base destino. De lo contrario el formato ingresado es inv�lido.
                    if(*(argv+i) != NULL) {
                        if( atoi(*(argv+i)) >= 2 && atoi(*(argv+i)) <= 16) {
                            *baseDestino = atoi(*(argv+i));
                        } else exit(EXIT_FAILURE);
                    } else exit(EXIT_FAILURE);
            /** Activa la ayuda del programa **/
           } else LEER("-h"){
                    retorno = 1;
            /** Muestra por consola los pasos que se van haciendo para convertir al n�mero **/
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

    /** El n�mero se almacenar� en una cadena de caracteres ya que, puede contener letras si la base est� en [11, 16] **/
    char numero[MAXNUM];
    char *p_numero; // Puntero al n�mero. Guarda la direcci�n de memoria del primer digito del n�mero.
    p_numero = numero;

    /** Existen dos posibilidades, que el usuario pida ayuda o no. En el caso de pedir ayuda, el n�mero no se convierte **/
    if( guardarParametros(&argc, argv, p_numero, &baseOrigen, &baseDestino) == 0){
            if(mostrarPasos == 1){ // Carteles a mostrar por consola si el usuario solicit� "-v"
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
