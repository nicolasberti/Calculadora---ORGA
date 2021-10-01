#include "convertidores.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "auxiliares.h"
#include "constantes.h"


void origenADecimal(char* parteEntera, int* baseOrigen, int* mostrarPasos){
    int *posicion, *potencia;
    double *suma; // Se utiliza un double para tener los digitos necesarios en la suma.

    /** Asignación de memoria **/
    posicion = (int*) malloc(sizeof(int));
    potencia = (int*) malloc(sizeof(int));
    suma = (double*) malloc(sizeof(double));

    if(*mostrarPasos){
        printf("Paso de base origen %i a base decimal \n",*baseOrigen);
    }

    *suma = 0;
    *posicion = 0; // Posición del digito.
    *potencia = strlen(parteEntera) - 1; // Potencia que se tiene que elevar el digito.

    while(*posicion < strlen(parteEntera)){
        int *actual;
        /** Muestra los pasos detallados de las conversiones por consola, si es que se piden **/
        if(*mostrarPasos){
            if(!*potencia)
                printf("%c * %i^%i + ",*(parteEntera + *posicion), *baseOrigen, *potencia);
            else
                printf("%c * %i^%i ",*(parteEntera + *posicion), *baseOrigen, *potencia);
        }
        actual = pasajeInt((parteEntera + *posicion));
        (*suma) += pow(*baseOrigen, *potencia) * *actual;
        (*posicion)++;
        (*potencia)--;
        /** Liberación de memoria **/
        free(actual);
    }

    if(*mostrarPasos){
        printf("\n El resultado de la conversion es : %d", *suma);
    }

    sprintf(parteEntera, "%.0lf", *suma); // Se copia el double sin su parte decimal.

    /** Liberación de memoria **/
    free(posicion); free(potencia); free(suma);
}


/**
    Método auxiliar : Convierte la parte entera de un número de base 10 a un número de base destino.
**/
static void decimalADestinoAux(int* parteEntera, int* baseDestino, char* enBaseDestino, int* mostrarPasos){
    int *actual;

    /** Asignación de memoria **/
    actual = (int*) malloc(sizeof(int));

    *actual = 0;

    if(*parteEntera != 0){
        (*actual) = *parteEntera % *baseDestino;
        if(*mostrarPasos){
            printf("%i mod %i = %i    (%i - %i)/%i = ",*parteEntera, *baseDestino, *actual, *parteEntera, *actual, *baseDestino);
        }
        (*parteEntera) /= *baseDestino;
        if(*mostrarPasos)
            printf("%i \n",*parteEntera);
        if(*parteEntera != 0)
            decimalADestinoAux(parteEntera, baseDestino, enBaseDestino);
    }

    char *pasaje;
    pasaje = pasajeChar(actual);
    strcat(enBaseDestino, pasaje);

    if(*mostrarPasos){
        printf("\n El resultado de la conversion es: ");
        imprimirCadena(enBaseDestino);
        printf("\n");
    }

    /** Liberación de memoria **/
    free(pasaje); free(actual);
}


void decimalADestino(char* parteEntera, int* baseDestino, int* mostrarPasos){
    int *numero;

    /** Asignación de memoria **/
    numero = (int*) malloc(sizeof(int));
    *numero = atoi(parteEntera); // Como siempre es de decimal a destino, utilizo la librería.

    if(*mostrarPasos){
        printf("Paso de base decimal a base destino %i \n", *baseDestino)
    }

    strcpy(parteEntera, "");
    decimalADestinoAux(numero, baseDestino, parteEntera, mostrarPasos);

    /** Liberación de memoria **/
    free(numero);
}


// Se asume que la parte fraccionaria esta pasada por parametro como 0.<numero fraccionario>. Al ser en base 10, se puede hacer esto.
void decimalADestinoFrac(char* parteFraccionaria, int* baseDestino, int* mostrarPasos){
    char *enBaseDestino;
    float *parteFrac;
    int *contador;
    int *parteEntera;

    /** Asignación de memoria **/
    enBaseDestino = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    parteFrac = (float*) malloc(sizeof(float));
    contador = (int*) malloc(sizeof(int));
    parteEntera = (int*) malloc(sizeof(int));

    if(*mostrarPasos){
        printf("Paso la parte fraccionaria del numero de base decimal a base destino %i\n",*baseDestino);
    }


    strcpy(enBaseDestino, "");
    *parteFrac = (atoi(parteFraccionaria)/pow(10, strlen(parteFraccionaria)));
    *parteEntera = 0;
    *contador = 0;

    while(*contador < PRECISION){

        if(*mostrarPasos){
            printf("0.%f * %i = ",*parteFrac, *baseDestino);
        }
        (*parteFrac) *= (*baseDestino);
        (*parteEntera) = *parteFrac;
        (*parteFrac) -= *parteEntera;

        char *pasaje;
        pasaje = pasajeChar(parteEntera);
        strcat(enBaseDestino, pasaje);
        (*contador)++;

        if(*mostrarPasos){
            printf("%f = x-%i  =>  x-%i = %c \n",*parteFrac, *contador, *contador, *pasaje);
        }
        free(pasaje);
    }

    strcpy(parteFraccionaria, enBaseDestino);

    if(*mostrarPasos){
        printf("\n El resultado de la conversion es: ");
        imprimirCadena(enBaseDestino);
        printf("\n");
    }

    /** Liberación de memoria **/
    free(enBaseDestino); free(contador); free(parteEntera); free(parteFrac);
}


void origenADecimalFrac(char* parteFrac, int* baseOrigen, int* mostrarPasos){
    int *posicion;
    float *enBaseDecimal;

    /** Asignación de memoria **/
    posicion = (int*) malloc(sizeof(int));
    enBaseDecimal = (float*) malloc(sizeof(float));

    *posicion = strlen(parteFrac) - 1;
    *enBaseDecimal = 0;

    if(*mostrarPasos){
        printf("Paso la parte fraccionaria del numero de base origen %i a base decimal \n ",*baseOrigen);
    }


    while(*posicion >= 0){
        int *pasaje;
        pasaje = pasajeInt( (parteFrac+*posicion));
        (*enBaseDecimal) += *pasaje;

        if(*mostrarPasos){
            if(*posicion > 0)
                printf("%i/%i) + ",*pasaje, *baseOrigen);
            else
                printf("%i/%i");
        }

        (*enBaseDecimal) = *enBaseDecimal / *baseOrigen;
        (*posicion)--;
        free(pasaje);
    }

    if(*mostrarPasos){
        printf("\n El resultado de la conversion es: 0.%f",*enBaseDecimal);
    }

    sprintf(parteFrac, "%f", *enBaseDecimal); // Copia lo convertido en la cadena parteFrac

    /** En este momento, parteFrac contendrá el "0,(parteFraccionaria convertida)" entonces utilizo este algoritmo para sacar el "0," **/
    char *auxFrac;
    auxFrac = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    strcpy(auxFrac, parteFrac);
    strcpy(parteFrac, "");
    strncat(parteFrac, auxFrac+2, PRECISION); // Solo concateno con la precisión establecida.
    free(auxFrac);

    /** Liberación de memoria **/
    free(posicion); free(enBaseDecimal);

}
