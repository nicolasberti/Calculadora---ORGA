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

    /** Asignaci�n de memoria **/
    posicion = (int*) malloc(sizeof(int));
    potencia = (int*) malloc(sizeof(int));
    suma = (double*) malloc(sizeof(double));

    if(*mostrarPasos){
        SEPARADORCONVERTORES;
        printf("\nPaso la parte entera de base origen %i a base 10 (decimal)\n",*baseOrigen);
    }

    *suma = 0;
    *posicion = 0; // Posici�n del digito.
    *potencia = strlen(parteEntera) - 1; // Potencia que se tiene que elevar el digito.

    while(*posicion < strlen(parteEntera)){
        int *actual;

        /** Muestra los pasos detallados de las conversiones por consola, si es que se piden **/
        if(*mostrarPasos){
            if(!*potencia != 0)
                printf("%c * %i^%i",*(parteEntera + *posicion), *baseOrigen, *potencia);
            else
                printf("%c * %i^%i + ",*(parteEntera + *posicion), *baseOrigen, *potencia);
        }

        actual = pasajeInt((parteEntera + *posicion));
        (*suma) += pow(*baseOrigen, *potencia) * *actual;
        (*posicion)++;
        (*potencia)--;
        /** Liberaci�n de memoria **/
        free(actual);
    }

    if(*mostrarPasos){
        printf(" = %.0lf (Resultado final de la parte entera)", *suma);
        SEPARADORCONVERTORES;
    }

    sprintf(parteEntera, "%.0lf", *suma); // Se copia el double sin su parte decimal.

    /** Liberaci�n de memoria **/
    free(posicion); free(potencia); free(suma);
}


/**
    M�todo auxiliar: Convierte la parte entera de un n�mero de base 10 a un n�mero de base destino.
**/
static void decimalADestinoAux(int* parteEntera, int* baseDestino, char* enBaseDestino, int* mostrarPasos){
    int *actual;

    /** Asignaci�n de memoria **/
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
            decimalADestinoAux(parteEntera, baseDestino, enBaseDestino, mostrarPasos);
        else
            if(*mostrarPasos)
                printf("\nHago la concatenacion de los ultimos restos a los primeros para formar el numero:");
    }

    char *pasaje;
    pasaje = pasajeChar(actual);
    strcat(enBaseDestino, pasaje);

    if(*mostrarPasos){
        printf("\n -> %s", enBaseDestino);
    }

    /** Liberaci�n de memoria **/
    free(pasaje); free(actual);
}


void decimalADestino(char* parteEntera, int* baseDestino, int* mostrarPasos){
    int *numero;

    /** Asignaci�n de memoria **/
    numero = (int*) malloc(sizeof(int));
    *numero = atoi(parteEntera); // Como siempre es de decimal a destino, utilizo la librer�a.

    if(*mostrarPasos){
        SEPARADORCONVERTORES;
        printf("\nPaso la parte entera de base 10 (decimal) a base destino %i \n", *baseDestino);
    }

    strcpy(parteEntera, "");
    decimalADestinoAux(numero, baseDestino, parteEntera, mostrarPasos);
    if(*mostrarPasos){
        printf(" (Resultado final de la parte entera)");
        SEPARADORCONVERTORES;
    }

    /** Liberaci�n de memoria **/
    free(numero);
}


// Se asume que la parte fraccionaria esta pasada por parametro como 0.<numero fraccionario>. Al ser en base 10, se puede hacer esto.
void decimalADestinoFrac(char* parteFraccionaria, int* baseDestino, int* mostrarPasos){
    char *enBaseDestino;
    float *parteFrac;
    int *contador;
    int *parteEntera;

    /** Asignaci�n de memoria **/
    enBaseDestino = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    parteFrac = (float*) malloc(sizeof(float));
    contador = (int*) malloc(sizeof(int));
    parteEntera = (int*) malloc(sizeof(int));

    if(*mostrarPasos){
        SEPARADORCONVERTORES;
        printf("\nPaso la parte fraccionaria del numero de base 10 (decimal) a base destino %i\n",*baseDestino);
    }


    strcpy(enBaseDestino, "");
    *parteFrac = (atoi(parteFraccionaria)/pow(10, strlen(parteFraccionaria)));
    *parteEntera = 0;
    *contador = 0;

    while(*contador < PRECISION){

        if(*mostrarPasos){
            printf("%f * %i = ",*parteFrac, *baseDestino);
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
        printf("\nEl resultado de la conversion de la parte fraccionaria es: 0.%s", enBaseDestino);
        SEPARADORCONVERTORES;
    }

    /** Liberaci�n de memoria **/
    free(enBaseDestino); free(contador); free(parteEntera); free(parteFrac);
}


void origenADecimalFrac(char* parteFrac, int* baseOrigen, int* mostrarPasos){
    int *posicion;
    float *enBaseDecimal;

    /** Asignaci�n de memoria **/
    posicion = (int*) malloc(sizeof(int));
    enBaseDecimal = (float*) malloc(sizeof(float));

    *posicion = strlen(parteFrac) - 1;
    *enBaseDecimal = 0;

    if(*mostrarPasos){
        SEPARADORCONVERTORES;
        printf("\nPaso la parte fraccionaria del numero de base origen %i a base decimal\n",*baseOrigen);
    }


    while(*posicion >= 0){
        int *pasaje;
        pasaje = pasajeInt( (parteFrac+*posicion));

            if(*mostrarPasos)
                printf("Digito: %i | Posicion: %i\n", *pasaje, *posicion);
            if(*mostrarPasos)
                printf("%f + %i", *enBaseDecimal, *pasaje);

        (*enBaseDecimal) += *pasaje;

            if(*mostrarPasos)
                printf(" = %f\n", *enBaseDecimal);
            if(*mostrarPasos)
                printf("%f / %i", *enBaseDecimal, *baseOrigen);

        (*enBaseDecimal) = *enBaseDecimal / *baseOrigen;

             if(*mostrarPasos)
                printf(" = %f\n\n", *enBaseDecimal);

        (*posicion)--;
        free(pasaje);
    }

    if(*mostrarPasos){
        printf("\nEl resultado de la conversion es: %f",*enBaseDecimal);
        SEPARADORCONVERTORES;
    }

    sprintf(parteFrac, "%f", *enBaseDecimal); // Copia lo convertido en la cadena parteFrac

    /** En este momento, parteFrac contendr� el "0,(parteFraccionaria convertida)" entonces utilizo este algoritmo para sacar el "0," **/
    char *auxFrac;
    auxFrac = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    strcpy(auxFrac, parteFrac);
    strcpy(parteFrac, "");
    strncat(parteFrac, auxFrac+2, PRECISION); // Solo concateno con la precisi�n establecida.
    free(auxFrac);

    /** Liberaci�n de memoria **/
    free(posicion); free(enBaseDecimal);

}
