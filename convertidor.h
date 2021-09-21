#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "validador.h"

#ifndef CONVERTIDOR_H_INCLUDED
#define CONVERTIDOR_H_INCLUDED

#define MAX_PARTEENTERA     10
#define MAX_PARTEFRACC      5

#define MAX_PARTEENTERA     10
#define MAX_PARTEFRACC      5

#define PARTE_ENTERA        40
#define PARTE_FRACCIONARIA  14
#define PRECISION           5

/** --- Funciones privadas --- **/
/**
    Procesa el caracter de la posicion actual
    y devuelve su valor tipo entero equivalente.
**/
static int* pasajeInt(char *posicionActual){
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

/**
    Recibe como parametro la parte entera
    de un numero con su base origen, y retorna
    su valor en base decimal.
**/
static void origenADecimal(char* parteEntera, int* baseOrigen){
    int *posicion, *potencia;
    long float *suma;
    long float *numeroFinal;

    /** Asignaci�n de memoria **/
    posicion = (int*) malloc(sizeof(int));
    potencia = (int*) malloc(sizeof(int));
    suma = (long float*) malloc(sizeof(float));
    numeroFinal = (long float*) malloc(sizeof(float));

    *numeroFinal = 0; *suma = 0;
    *posicion = 0; // Posici�n del digito.
    *potencia = strlen(parteEntera) - 1; // Potencia que se tiene que elevar el digito.

    while(*posicion < strlen(parteEntera)){
        int *actual;
        actual = pasajeInt((parteEntera + *posicion));
        (*suma) += pow(*baseOrigen, *potencia) * *actual;
        (*posicion)++;
        (*potencia)--;
        /** Liberaci�n de memoria **/
        free(actual);
    }

    *numeroFinal = (float) *suma;
    sprintf(parteEntera, "%d", *numeroFinal);

    /** Liberaci�n de memoria **/
    free(posicion); free(potencia); free(numeroFinal); free(suma);
}

/**
    Procesa el entero actual y
    retorna su caracter equivalente
**/
static char* pasajeChar(int* actual){
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

/**
    Recibe como parametro un numero y devuelve la posicion
    de la , del numero. Si el numero no tiene , entonces
    la posicion es nula
**/
static int* buscaPosComa(char* numero){

    int *pos, *longitud, *encontro;

    *longitud = strlen(numero);
    *encontro = 0;
    *pos = 0;

    while(*pos < *longitud && !*encontro){
        if(*(numero + *pos) == ','){
            encontro = 1;
        }
        else
            *(pos)++;
    }

    return pos;
}


/**
    Recibe como parametro la parte entera de un numero
    con su base destino, un contador, y el numero en su base
    destino correspondiente.
**/
static void decimalADestinoAux(int* parteEntera, int* baseDestino, char* enBaseDestino){
    int *actual;

    /** Asignaci�n de memoria **/
    actual = (int*) malloc(sizeof(int));

    *actual = 0;

    if(*parteEntera != 0){
        (*actual) = *parteEntera % *baseDestino;
        (*parteEntera) /= *baseDestino;

        if(*parteEntera != 0)
            decimalADestinoAux(parteEntera, baseDestino, enBaseDestino);
    }

    char *pasaje;
    pasaje = pasajeChar(actual);
    strcat(enBaseDestino, pasaje);
    /** Liberaci�n de memoria **/
    free(pasaje); free(actual);
}
/**
    Recibe como parametro la parte entera
    de un numero con su base destino, y retorna
    su valor en la base destino.
**/
 static void decimalADestino(char* parteEntera, int* baseDestino){
    int *numero;

    /** Asignaci�n de memoria **/
    numero = (int*) malloc(sizeof(int));

    *numero = atoi(parteEntera); // Como siempre es de decimal a destino, utilizo la librer�a.

    strcpy(parteEntera, "");
    decimalADestinoAux(numero, baseDestino, parteEntera);
    /** Liberaci�n de memoria **/
    free(numero);
}

/**
    Recibe como parametro la parte fraccionaria
    de un numero en base decimal, con su base destino.
    Y retorna su valor en la base destino.
**/
                                //se asume que la parte fraccionaria esta pasada por parametro como 0.<numero fraccionario> Al ser en base 10, se puede hacer esto
static void decimalADestinoFrac(char* parteFraccionaria, int* baseDestino){
    char *enBaseDestino;
    float *parteFrac;
    int *contador, *parteEntera;

    /** Asignaci�n de memoria **/
    enBaseDestino = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    parteFrac = (float*) malloc(sizeof(float));
    contador = (int*) malloc(sizeof(int));
    parteEntera = (int*) malloc(sizeof(int));


    strcpy(enBaseDestino, "");
    *parteFrac = (atoi(parteFraccionaria)/pow(10, strlen(parteFraccionaria)));
    *parteEntera = 0;
    *contador = 0;

    while(*contador < PRECISION){
        (*parteFrac) *= (*baseDestino);
        (*parteEntera) = *parteFrac;
        (*parteFrac) -= *parteEntera;

        char *pasaje;
        pasaje = pasajeChar(parteEntera);
        strcat(enBaseDestino, pasaje);
        (*contador)++;
        free(pasaje);
    }

    strcpy(parteFraccionaria, enBaseDestino);

    /** Liberaci�n de memoria **/
    free(enBaseDestino); free(contador); free(parteEntera); free(parteFrac);
}
    /**
        Recibe como parametro la parte fraccionaria de un numero
        en el formato <parte fraccionaria> y su base origen.
        y devuelve el equivalente de la parte fraccionaria en
        base decimal
    **/
static void origenADecimalFrac(char* parteFrac, int* baseOrigen){
    int *posicion;
    long float *enBaseDecimal;

    /** Asignaci�n de memoria **/
    posicion = (int*) malloc(sizeof(int));
    enBaseDecimal = (long float*) malloc(sizeof(float));

    *posicion = strlen(parteFrac) - 1;
    *enBaseDecimal = 0;

    while(*posicion >= 0){
        int *pasaje;
        pasaje = pasajeInt( (parteFrac+*posicion));
        (*enBaseDecimal) += *pasaje;
        (*enBaseDecimal) = *enBaseDecimal / *baseOrigen;
        (*posicion)--;
        free(pasaje);
    }

    sprintf(parteFrac, "%f", *enBaseDecimal);

    /** En este momento, parteFrac contendr� el "0,(parteFraccionaria convertida)" entonces utilizo este algoritmo para sacar el "0," **/
    char *auxFrac;
    auxFrac = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    strcpy(auxFrac, parteFrac);
    strcpy(parteFrac, "");
    strcat(parteFrac, auxFrac+2);
    free(auxFrac);

    /** Liberaci�n de memoria **/
    free(posicion); free(enBaseDecimal);

}


/** Separa la parte entera y la parte fraccionaria del n�mero **/
static void separar(char *numero, char *parteEntera, char *parteFraccionaria){
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

/** --- Funciones p�blicas --- **/

int* convertir(char *numero, int *baseOrigen, int* baseDestino, int *mostrarPasos){
    int *retorno;
    char *parteEntera;
    char *parteFraccionaria;
    int *validador;

    /** Asignaci�n de memoria **/
    retorno = (int*) malloc(sizeof(int));
    parteEntera = (char*) malloc(PARTE_ENTERA * sizeof(char));
    parteFraccionaria = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));

    *retorno = 0;
    strcpy(parteEntera, "");
    strcpy(parteFraccionaria, "");

    /** Comprueba si la cadena ingresada pertenece a la base. (Retorna 0 si pertenece) **/
    validador = validar(numero, baseOrigen);

    if( *validador == 0) {

        /** Separaci�n de la parte fraccionaria y la parte entera **/
        separar(numero, parteEntera, parteFraccionaria);

        if( strlen(parteEntera) > MAX_PARTEENTERA || strlen(parteFraccionaria) > MAX_PARTEFRACC) {
            // La parte entera o la parte fraccionaria supera el m�ximo de digitos permitidos.
            *retorno = 1;

        } else {

            /** -- Inicio convertidores -- **/

                /** Si la bases son iguales, es el mismo n�mero **/
                if(*baseOrigen == *baseDestino){
                    if(*mostrarPasos == 1)
                        printf("[convertir] Las bases son iguales, por ende el n�mero no se convierte.");
                }

                /** Hace una conversi�n de base 10 a base r **/
                else if(*baseOrigen == 10 && *baseDestino != 10){
                    decimalADestino(parteEntera, baseDestino);
                    strcpy(numero, parteEntera);
                    if(strlen(parteFraccionaria) > 0){
                            decimalADestinoFrac(parteFraccionaria, baseDestino);
                            strcat(numero, ",");
                            strcat(numero, parteFraccionaria);
                    }
                }

                /** Hace una conversi�n de base r a base 10 **/
                else if(*baseOrigen != 10 && *baseDestino == 10){
                    origenADecimal(parteEntera, baseOrigen);
                    strcpy(numero, parteEntera);
                    if(strlen(parteFraccionaria) > 0){
                            /** testear **/
                            origenADecimalFrac(parteFraccionaria, baseOrigen);
                            strcat(numero, ",");
                            strcat(numero, parteFraccionaria);
                    }
                }

                /** Base origen r y base destino d diferentes a 10. Entonces, se utiliza como auxiliar la base 10 para hacer la conversi�n. **/
                else {

                    /** Conversi�n de la parte entera **/
                        /** Conversi�n de base r a base 10 **/
                        origenADecimal(parteEntera, baseOrigen);
                        /** Conversi�n de base 10 a base d **/
                        decimalADestino(parteEntera, baseDestino);
                        strcpy(numero, parteEntera);

                    /** Una vez que ya se convirti�, ahora se convierte la parte fraccionaria si es que tiene **/
                    if(strlen(parteFraccionaria) > 0){
                            /** Conversi�n de base r a base 10 **/
                            origenADecimalFrac(parteFraccionaria, baseOrigen);
                            /** Conversi�n de base 10 a base d **/
                            decimalADestinoFrac(parteFraccionaria, baseDestino);
                            strcat(numero, ",");
                            strcat(numero, parteFraccionaria);
                    }
                }

            /** -- Fin convertidores -- **/
        }
    } else *retorno = 2;

    /** Liberaci�n de memoria **/
    free(parteEntera); free(parteFraccionaria); free(validador);

    return retorno;
}

#endif // CONVERTIDOR_H_INCLUDED
