#include "auxiliares.h"
#include "constantes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void separar(char *numero, char *parteEntera, char *parteFraccionaria){
    // OBS: No veo si tiene 2 comas ó si son todos numeros de la misma base porque eso ya se validó en el "validador.h"
    int *size, *i, *parte;

    /** Asignación de memoria **/
    size = (int*) malloc(sizeof(int));
    i = (int*) malloc(sizeof(int));
    parte = (int*) malloc(sizeof(int));

    *size = strlen(numero);
    *parte = 0; // 0 indica que está leyendo en la parte entera, 1 en la parte fraccionaria

    for(*i = 0; *i < *size; (*i)++){
            if(*parte == 0){
                if(*(numero+*i) == SEPARADOR) *parte=1;
                else strncat(parteEntera, (numero+*i), 1);
            } else strncat(parteFraccionaria, (numero+*i), 1);
    }

    /** Liberación de memoria **/
    free(i); free(size); free(parte);
}


char* pasajeChar(int* actual){
    char *actualDestino;

    /** Asignación de memoria **/
    actualDestino = (char*) malloc(sizeof(char));
    switch(*actual){
            case 0: strcpy(actualDestino, "0"); break;
            case 1: strcpy(actualDestino, "1"); break;
            case 2: strcpy(actualDestino, "2"); break;
            case 3: strcpy(actualDestino, "3"); break;
            case 4: strcpy(actualDestino, "4"); break;
            case 5: strcpy(actualDestino, "5"); break;
            case 6: strcpy(actualDestino, "6"); break;
            case 7: strcpy(actualDestino, "7"); break;
            case 8: strcpy(actualDestino, "8"); break;
            case 9: strcpy(actualDestino, "9"); break;
            case 10: strcpy(actualDestino, "A"); break;
            case 11: strcpy(actualDestino, "B"); break;
            case 12: strcpy(actualDestino, "C"); break;
            case 13: strcpy(actualDestino, "D"); break;
            case 14: strcpy(actualDestino, "E"); break;
            case 15: strcpy(actualDestino, "F"); break;
    }
    return actualDestino;
}

/** Imprime una cadena de caracteres **/
void imprimirCadena(char *cadena){
    int *posicion, *longitud;

    /** Asignacion de memoria**/
    posicion = (int*) malloc(sizeof(int));
    *posicion = 0;
    *longitud = strlen(cadena);

    while(*posicion < *longitud){
        printf("%c",*(cadena + *posicion));
        *posicion++;
    }
    free(posicion);

}


int* pasajeInt(char *posicionActual){
    int *actual;

    /** Asignación de memoria **/
    actual = (int*) malloc(sizeof(int));
    switch(*posicionActual){
                case 'A' : *actual = 10; break;
                case 'a' : *actual = 10; break;
                case 'B' : *actual = 11; break;
                case 'b' : *actual = 11; break;
                case 'C' : *actual = 12; break;
                case 'c' : *actual = 12; break;
                case 'D' : *actual = 13; break;
                case 'd' : *actual = 13; break;
                case 'E' : *actual = 14; break;
                case 'e' : *actual = 14; break;
                case 'F' : *actual = 15; break;
                case 'f' : *actual = 15; break;
                default: *actual = *posicionActual - '0'; break;
            }
    return actual;
}


// FIJARSE BIEN SI ESTÁ BIEN LIBERADA LA MEMORIA Y VER DETALLES DE CÓDIGO.
int* validar(char *numero, int *r){
    int *encontroError, *size, *contador;
    char *caracteres;

    contador = (int*) malloc(sizeof(int));
    encontroError = (int*) malloc(sizeof(int));
    size = (int*) malloc(sizeof(int));
    caracteres = (char*) malloc(25 * sizeof(char));

    *encontroError = 0;
    strcpy(caracteres, "");
    *size = strlen(numero);
    *contador = 0;

    switch(*r){ // Agrega caracteres a la cadena caracteres según la base pasada como parametro.
            case 16: strcat(caracteres, "Ff");
            case 15: strcat(caracteres, "Ee");
            case 14: strcat(caracteres, "Dd");
            case 13: strcat(caracteres, "Cc");
            case 12: strcat(caracteres, "Bb");
            case 11: strcat(caracteres, "Aa");
            case 10: strcat(caracteres, "9");
            case 9: strcat(caracteres, "8");
            case 8: strcat(caracteres, "7");
            case 7: strcat(caracteres, "6");
            case 6: strcat(caracteres, "5");
            case 5: strcat(caracteres, "4");
            case 4: strcat(caracteres, "3");
            case 3: strcat(caracteres, "2");
            case 2: strcat(caracteres, "01");
    }

    /**
        Fases del algoritmo
        1. Valida casos excepcionales
        2. Valida si el número pertenece a la base y que no contenga más de un separador.
    **/

    /** Fase 1 -> Validación de casos excepcionales **/

    /** Primer caso particular -> El primer caracter es el separador **/
    if(*size == 1 && *(numero) == SEPARADOR)
        *encontroError = 1;
    /** Segundo caso particular -> El último caracter es el separador **/
    else if(*(numero+(*size)-1) == SEPARADOR)
        *encontroError = 1;
    /** Fase 2 -> Validación del número **/
    else {

        /**
            Explicación del algoritmo:
                El algoritmo comprueba para cada caracter de la cadena número si ese caracter
                pertenece a la cadena caracteres. Esto es, si es un caracter válido de la base r.
                A su vez, comprueba de que en la cadena número no haya más de un separador tal que
                esto se considería un formato inválido.
        **/
        int *igual, *i;
        igual = (int*) malloc(sizeof(int));
        *igual = 0;
        i = (int*) malloc(sizeof(int));
        for(*i = 0; *i < strlen(numero) && *encontroError == 0; (*i)++) {
            int *j;
            j = (int*) malloc(sizeof(int));
            for(*j = 0; *j < strlen( caracteres ) && *igual == 0; (*j)++) {
                if( *(numero+*i) == SEPARADOR ) {
                    (*contador)++;
                    *igual = 1;
                } else
                    if( *(numero+*i) == *(caracteres+*j) )
                        *igual = 1;
            }
            if(*igual == 0) // Si comprobó el caracter *(numero+i) con todos los caracteres de la cadena caracteres y ninguno resultó igual, significa que no es un caracter de la base.
                *encontroError = 1;
            else
                *igual = 0;
            if(*contador > 1)
                *encontroError = 1;
            free(j);
		}
		free(igual); free(i);

    }
    free(size); free(caracteres); free(contador);
    return encontroError;
}
