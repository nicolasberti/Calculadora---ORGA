#include "convertidores.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "auxiliares.h"
#include "constantes.h"

/**
    Recibe como parametro la parte entera
    de un numero con su base origen, y retorna
    su valor en base decimal.
**/
void origenADecimal(char* parteEntera, int* baseOrigen){
    int *posicion, *potencia;
    double *suma;
    //long long *suma; // Se usa el tipo long long porque para el m�ximo origen representable necesita 13 digitos.

    /** Asignaci�n de memoria **/
    posicion = (int*) malloc(sizeof(int));
    potencia = (int*) malloc(sizeof(int));
    //suma = (long long*) malloc(sizeof(long));
    suma = (double*) malloc(sizeof(double));

    *suma = 0;
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

    sprintf(parteEntera, "%.0lf", *suma);

    /** Liberaci�n de memoria **/
    free(posicion); free(potencia); free(suma);
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
void decimalADestino(char* parteEntera, int* baseDestino){
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
// Se asume que la parte fraccionaria esta pasada por parametro como 0.<numero fraccionario> Al ser en base 10, se puede hacer esto
void decimalADestinoFrac(char* parteFraccionaria, int* baseDestino){
    char *enBaseDestino;
    float *parteFrac;
    int *contador;
    int *parteEntera;

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
void origenADecimalFrac(char* parteFrac, int* baseOrigen){
    int *posicion;
    float *enBaseDecimal;

    /** Asignaci�n de memoria **/
    posicion = (int*) malloc(sizeof(int));
    enBaseDecimal = (float*) malloc(sizeof(float));

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
    strncat(parteFrac, auxFrac+2, PRECISION); // Solo concateno con la precisi�n establecida.
    free(auxFrac);

    /** Liberaci�n de memoria **/
    free(posicion); free(enBaseDecimal);

}
