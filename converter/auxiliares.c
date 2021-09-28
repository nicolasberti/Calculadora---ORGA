#include "auxiliares.h"
#include "constantes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void separar(char *numero, char *parteEntera, char *parteFraccionaria){
    // OBS: No veo si tiene 2 comas � si son todos numeros de la misma base porque eso ya se valid� en el "validador.h"
    int *size, *i, *parte;

    /** Asignaci�n de memoria **/
    size = (int*) malloc(sizeof(int));
    i = (int*) malloc(sizeof(int));
    parte = (int*) malloc(sizeof(int));

    *size = strlen(numero);
    *parte = 0; // 0 indica que est� leyendo en la parte entera, 1 en la parte fraccionaria

    for(*i = 0; *i < *size; (*i)++){
            if(*parte == 0){
                if(*(numero+*i) == SEPARADOR) *parte=1;
                else strncat(parteEntera, (numero+*i), 1);
            } else strncat(parteFraccionaria, (numero+*i), 1);
    }

    /** Liberaci�n de memoria **/
    free(i); free(size); free(parte);
}


char* pasajeChar(int* actual){
    char *actualDestino;

    /** Asignaci�n de memoria **/
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


int* pasajeInt(char *posicionActual){
    int *actual;

    /** Asignaci�n de memoria **/
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


int* validar(char *numero, int *r){
    int *size, *retorno, *contador, *i;
    char *caracteres;
    /** Asignaci�n de memoria **/
    size = (int*) malloc(sizeof(int));
    retorno = (int*) malloc(sizeof(int));
    contador = (int*) malloc(sizeof(int));
    i = (int*) malloc(sizeof(int));
    caracteres = (char*) malloc(25 * sizeof(char));

    *size = strlen(numero); // Tama�o del n�mero.
    *retorno = 0;
    *contador = 0;
    strcpy(caracteres, "");

    /**
        Explicaci�n del algoritmo:

        El algoritmo comienza creando una cadena llamada "caracteres" que se encontraran los caracteres de la base r.

        Despu�s, comprueba que no contenga los siguientes casos particulares la cadena n�mero.
            * El separador primero, la cual consideramos un formato inv�lido.
            * El �ltimo digito, es igual al separador.

        Finalmente, se hace uso de dos ciclos for para comprobar que cada caracter de la cadena n�mero pertenezca a la cadena caracteres (esto es, que pertenezca a la base r) y adem�s, comprueba
        que no contenga m�s de 1 separador (ya que ser�a un n�mero inv�lido).
    **/
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
    /** Primer caso particular -> El primer caracter es el separador **/
    if(*size == 1 && *(numero) == SEPARADOR)
        *retorno = 1;
    /** Segundo caso particular -> El �ltimo caracter es el separador **/
    else if(*(numero+(*size)-1) == SEPARADOR)
        *retorno = 1;
    else {
        for(*i = 0; *i < *size && *retorno == 0; (*i)++){
            int *igual;

            /** Asignaci�n de memoria **/
            igual = (int*) malloc(sizeof(int));

            *igual = 1;

            /** Encuentra un separador -> incrementa el contador de separadores **/
            if(*(numero+*i) == SEPARADOR) {
                    (*contador)++;
                    *igual = 0; /** si *igual==0 indica que, el caracter es igual a alg�n caracter de la cadena caracteres **/
            } else {

                int *j;
                /** Asignaci�n de memoria **/
                j = (int*) malloc(sizeof(int));

                for(*j = 0; *j < strlen(caracteres) && *igual==1; (*j)++){
                    if(*(numero+*i) == *(caracteres+*j))
                        *igual = 0;
                }

                /** Liberaci�n de memoria **/
                free(j);
            }

            *retorno = *igual; // Si la variable igual qued� en 1 entonces indica que no encontr� alg�n caracter en la cadena caracteres.

            if(*contador > 1) // Si el contador es mayor que 1, hay m�s de 1 separador, por ende, el n�mero es inv�lido.
                *retorno = 1;

            /** Liberaci�n de memoria **/
            free(igual);
        }
        /** Liberaci�n de memoria **/
        free(i);
    }

    /** Liberaci�n de memoria **/
    free(size); free(caracteres); free(contador);

    return retorno;
}
