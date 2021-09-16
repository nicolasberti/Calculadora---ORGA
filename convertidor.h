#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "validador.h"

#ifndef CONVERTIDOR_H_INCLUDED
#define CONVERTIDOR_H_INCLUDED

#define PARTE_ENTERA        40 // Máximos digitos para la parte entera. (El máximo valor que puede tomar una parte entera es 40 tal que es el numero de digitos de pasar de base 16 el numero FF..F (10 F's) a base 2.
#define PARTE_FRACCIONARIA  14 // Máximos digitos que puede tener la parte fraccionaria. (es decir, 0,..14digitos..)
#define PRESICION           5 // Digitos de presicion para la parte fraccionaria

/** --- Funciones privadas --- **/
/**
    Procesa el caracter de la posicion actual
    y devuelve su valor tipo entero equivalente.
**/
static int* pasajeInt(char *posicionActual){
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

/**
    Recibe como parametro la parte entera
    de un numero con su base origen, y retorna
    su valor en base decimal.
**/
static void origenADecimal(char* parteEntera, int* baseOrigen){
    int *posicion, *potencia;
    long double *suma;
    long int *numeroFinal;

    /** Asignación de memoria **/
    posicion = (int*) malloc(sizeof(int));
    potencia = (int*) malloc(sizeof(int));
    suma = (long double*) malloc(sizeof(double));
    numeroFinal = (long int*) malloc(sizeof(int));

    *numeroFinal = 0; *suma = 0;
    *posicion = 0; // Posición del digito.
    *potencia = strlen(parteEntera) - 1; // Potencia que se tiene que elevar el digito.

    while(*posicion < strlen(parteEntera)){
        int *actual;
        actual = pasajeInt((parteEntera + *posicion));
        (*suma) += pow(*baseOrigen, *potencia) * *actual; // nocomputa bien la potencia. por qué?
        (*posicion)++;
        (*potencia)--;
        /** Liberación de memoria **/
        free(actual);
    }

    *numeroFinal = (int) *suma;
    /* No se puede expresar el número en la base solicitada.
    if(numeroFinal >= pow(*baseDestino, PARTE_ENTERA))
        exit(EXIT_FAILURE);*/
    sprintf(parteEntera, "%d", *numeroFinal);
    /** Liberación de memoria **/
    free(posicion); free(potencia); free(numeroFinal); free(suma);
}

/**
    Procesa el entero actual y
    retorna su caracter equivalente
**/
static char* pasajeChar(int* actual){
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
    Recibe como parametro la parte entera de un numero
    con su base destino, un contador, y el numero en su base
    destino correspondiente.
**/
static void decimalADestinoAux(int* parteEntera, int* baseDestino, char* enBaseDestino){
    int *actual;

    /** Asignación de memoria **/
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
    /** Liberación de memoria **/
    free(pasaje); free(actual);
}
/**
    Recibe como parametro la parte entera
    de un numero con su base destino, y retorna
    su valor en la base destino.
**/
 static void decimalADestino(char* parteEntera, int* baseDestino){
    int *numero;

    /** Asignación de memoria **/
    numero = (int*) malloc(sizeof(int));

    *numero = atoi(parteEntera); // Como siempre es de decimal a destino, utilizo la librería.

    /* No se puede expresar el número en la base solicitada.
    if(parteEntera >= pow(*baseDestino, PARTE_ENTERA))
        exit(EXIT_FAILURE);*/

    strcpy(parteEntera, "");
    decimalADestinoAux(numero, baseDestino, parteEntera);
    /** Liberación de memoria **/
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

    /** Asignación de memoria **/
    enBaseDestino = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));
    parteFrac = (float*) malloc(sizeof(float));
    contador = (int*) malloc(sizeof(int));
    parteEntera = (int*) malloc(sizeof(int));


    strcpy(enBaseDestino, "");
    *parteFrac = (atoi(parteFraccionaria)/pow(10, strlen(parteFraccionaria)));
    *parteEntera = 0;
    *contador = 0;

    while(*contador < PRESICION){
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
    /** Liberación de memoria **/
    free(enBaseDestino); free(contador); free(parteEntera); free(parteFrac);
}
                    //se asume que la parte fraccionaria esta pasada por parametro como <numero fraccionario>
static void origenADecimalFrac(char* parteFrac, int* baseDestino){

    int *posicion;
    float *enBaseDecimal;

    /** Asignación de memoria **/
    posicion = (int*) malloc(sizeof(int));
    enBaseDecimal = (float*) malloc(sizeof(float));

    *posicion = strlen(parteFrac) - 1;
    *enBaseDecimal = 0;

    while(*posicion >= 0){
        int *pasaje;
        pasaje = pasajeInt(parteFrac + *posicion);
        (*enBaseDecimal) += *pasaje;
        (*enBaseDecimal) /= *baseDestino;
        free(pasaje);
    }

    sprintf(parteFrac, "%d", *enBaseDecimal);
    /** Liberación de memoria **/
    free(posicion); free(enBaseDecimal);

}


/** Separa la parte entera y la parte fraccionaria del número **/
static void separar(char *numero, char *parteEntera, char *parteFraccionaria){
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
                else strcat(parteEntera, (numero+*i));
            } else strcat(parteFraccionaria, (numero+*i));
    }
    /** Liberación de memoria **/
    free(i); free(size); free(parte);
}

/** --- Funciones públicas --- **/

int* convertir(char *numero, int *baseOrigen, int* baseDestino, int *mostrarPasos){
    int *retorno;
    char *parteEntera;
    char *parteFraccionaria;
    int *validador;

    /** Asignación de memoria **/
    retorno = (int*) malloc(sizeof(int));
    parteEntera = (char*) malloc(PARTE_ENTERA * sizeof(char));
    parteFraccionaria = (char*) malloc(PARTE_FRACCIONARIA * sizeof(char));

    *retorno = 0;
    strcpy(parteEntera, "");
    strcpy(parteFraccionaria, "");
    validador = validar(numero, baseOrigen);

    if( *validador == 0) { // La función "validar" retorna 0 cuando el número sea válido y sea de la base indicada.

        /**
            Configurar estas excepciones:
            * Máximo representable con un long 10 bits.
                Máximo base binaria: 1023
                Maximo base r: N = r^10.

            Agregar parte fraccionaria entre base r a 10. testear.

            Agregar paso por paso a las conversiones. agregar prints segun *mostrarpasos.

            Agregar base r y base d fraccionarias. completo.
        **/
        /** Si la bases son iguales, es el mismo número **/
        if(*baseOrigen == *baseDestino){
            if(*mostrarPasos == 1)
                printf("[convertir] Las bases son iguales, por ende el número no se convierte.");
        }

        /** Hace una conversión de base 10 a base r **/
        else if(*baseOrigen == 10 && *baseDestino != 10){
            separar(numero, parteEntera, parteFraccionaria);
            decimalADestino(parteEntera, baseDestino);
            strcpy(numero, parteEntera);
            if(strlen(parteFraccionaria) > 0){
                    decimalADestinoFrac(parteFraccionaria, baseDestino);
                    strcat(numero, ",");
                    strcat(numero, parteFraccionaria);
            }
        }

        /** Hace una conversión de base r a base 10 **/
        else if(*baseOrigen != 10 && *baseDestino == 10){
            separar(numero, parteEntera, parteFraccionaria);
            origenADecimal(parteEntera, baseOrigen);
            strcpy(numero, parteEntera);
            if(strlen(parteFraccionaria) > 0){
                    /** testear **/
                    origenADecimalFrac(parteFraccionaria, baseDestino);
                    strcat(numero, ",");
                    strcat(numero, parteFraccionaria);
            }
        }

        /** Base origen r y base destino d diferentes a 10. Entonces, se utiliza como auxiliar la base 10 para hacer la conversión. **/
        else {
            /** Separación de la parte fraccionaria y la parte entera **/
            separar(numero, parteEntera, parteFraccionaria);

            /** Conversión de la parte entera **/
                /** Conversión de base r a base 10. **/
                origenADecimal(parteEntera, baseOrigen);
                /** Conversión de base 10 a base d **/
                decimalADestino(parteEntera, baseDestino);
                strcpy(numero, parteEntera);

            /** Una vez que ya se convirtió, ahora se convierte la parte fraccionaria si es que tiene **/
        }
    } else *retorno = 2;

    free(parteEntera);
    free(parteFraccionaria);
    free(validador);
    return retorno;
}

#endif // CONVERTIDOR_H_INCLUDED
