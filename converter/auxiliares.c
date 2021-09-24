#include "auxiliares.h"
#include "constantes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** Separa la parte entera y la parte fraccionaria del número **/
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

/**
    Procesa el entero actual y
    retorna su caracter equivalente
**/
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

/**
    Procesa el caracter de la posicion actual
    y devuelve su valor tipo entero equivalente.
**/
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

int* validar(char *p_numero, int *r){
    int *size, *retorno, *contador, *i;
    char *caracteres;
    /** Asignación de memoria **/
    size = (int*) malloc(sizeof(int));
    retorno = (int*) malloc(sizeof(int));
    contador = (int*) malloc(sizeof(int));
    i = (int*) malloc(sizeof(int));
    caracteres = (char*) malloc(25 * sizeof(char));

    *size = strlen(p_numero); // Tamaño del número.
    *retorno = 0;
    *contador = 0;
    strcpy(caracteres, "");

    switch(*r){
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
    if(*size == 1 && *(p_numero) == SEPARADOR) // Si el usuario ingresa simplemente una coma, no es un número válido.
        *retorno = 1;
    else if(*(p_numero+(*size)-1) == SEPARADOR) // Si el usuario ingresa un número que termina con una coma, no es un número válido.
        *retorno = 1;
    else {
        for(*i = 0; *i < *size && *retorno == 0; (*i)++){
            int *igual;
            igual = (int*) malloc(sizeof(int));
            *igual = 1;
            if(*(p_numero+*i) == SEPARADOR) { // Si el caracter es una coma, la cuenta ya que si contiene más de 1, es inválido.
                    (*contador)++;
                    *igual = 0;
            } else {
                int *j;
                j = (int*) malloc(sizeof(int));
                for(*j = 0; *j < strlen(caracteres) && *igual==1; (*j)++){
                    if(*(p_numero+*i) == *(caracteres+*j))
                        *igual = 0;
                }
                free(j);
            }
            *retorno = *igual;
            if(*contador > 1)
                *retorno = 1;
            free(igual);
        }
        free(i);
    }
    free(size);
    free(caracteres);
    free(contador);
    return retorno;
}
