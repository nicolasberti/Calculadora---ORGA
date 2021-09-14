#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "validador.h"

#ifndef CONVERTIDOR_H_INCLUDED
#define CONVERTIDOR_H_INCLUDED

/**
    De entrada se permite cualquier digito, pero al retornar en la parte entera solo tendrá

**/
#define PARTE_ENTERA        10 // Máximos digitos para la parte entera.
#define PARTE_FRACCIONARIA  5 // Máximos digitos de presición para la parte fraccionaria.

/** --- Funciones privadas --- **/
/**
    Procesa el caracter de la posicion actual
    y devuelve su valor tipo entero equivalente.
**/
static int pasajeInt(char *posicionActual){
    int actual;
    switch(*posicionActual){
                case 'A' : actual = 10; break;
                case 'a' : actual = 10; break;
                case 'B' : actual = 11; break;
                case 'b' : actual = 11; break;
                case 'C' : actual = 12; break;
                case 'c' : actual = 12; break;
                case 'D' : actual = 13; break;
                case 'd' : actual = 13; break;
                case 'E' : actual = 14; break;
                case 'e' : actual = 14; break;
                case 'F' : actual = 15; break;
                case 'f' : actual = 15; break;
                default: actual = *posicionActual - '0'; break;
            }
    return actual;
}

/**
    Recibe como parametro la parte entera
    de un numero con su base origen, y retorna
    su valor en base decimal.
**/
static void origenADecimal(char* p_parteEntera, int* baseOrigen){
    int actual, posicion, potencia;
    long double suma;
    long int numeroFinal;
    numeroFinal = 0; actual = 0; suma = 0;
    posicion = 0; // Posición del digito.
    potencia = strlen(p_parteEntera) - 1; // Potencia que se tiene que elevar el digito.

    while(posicion < strlen(p_parteEntera)){
        actual = pasajeInt((p_parteEntera + posicion));
        suma += pow(*baseOrigen, potencia) * actual; // nocomputa bien la potencia. por qué?
        posicion++;
        potencia--;
    }

    numeroFinal = (int) suma;
    /* No se puede expresar el número en la base solicitada.
    if(numeroFinal >= pow(*baseDestino, PARTE_ENTERA))
        exit(EXIT_FAILURE);*/
    sprintf(p_parteEntera, "%d", numeroFinal);
}

/**
    Procesa el entero actual y
    retorna su caracter equivalente
**/
static char* pasajeChar(int actual){
    char *actualDestino;
    actualDestino = (char*) malloc(sizeof(char));
    switch(actual){
            case 0 : *actualDestino = '0'; break;
            case 1 : *actualDestino = '1'; break;
            case 2 : *actualDestino = '2'; break;
            case 3 : *actualDestino = '3'; break;
            case 4 : *actualDestino = '4'; break;
            case 5 : *actualDestino = '5'; break;
            case 6 : *actualDestino = '6'; break;
            case 7 : *actualDestino = '7'; break;
            case 8 : *actualDestino = '8'; break;
            case 9 : *actualDestino = '9'; break;
            case 10 : *actualDestino = 'A'; break;
            case 11 : *actualDestino = 'B'; break;
            case 12 : *actualDestino = 'C'; break;
            case 13 : *actualDestino = 'D'; break;
            case 14 : *actualDestino = 'E'; break;
            case 15 : *actualDestino = 'F'; break;
    }
    return actualDestino;
}

/**
    Recibe como parametro la parte entera de un numero
    con su base destino, un contador, y el numero en su base
    destino correspondiente.
**/
static void decimalADestinoAux(int* parteEntera, int* baseDestino, char* p_enBaseDestino, int* contador){
    int actual;
    actual = 0;

    if(*parteEntera != 0){
        actual = *parteEntera % *baseDestino;
        *parteEntera /= *baseDestino;

        if(*parteEntera != 0)
            decimalADestinoAux(parteEntera, baseDestino, p_enBaseDestino, contador);
    }

    char *caracter;
    caracter = pasajeChar(actual);
    *(p_enBaseDestino + (*contador)) = *caracter;
    free(caracter);
    *(contador) += 1;

}
/**
    Recibe como parametro la parte entera
    de un numero con su base destino, y retorna
    su valor en la base destino.
**/
 static void decimalADestino(char* p_parteEntera, int* baseDestino){
    int contador;
    contador = 0;

    int parteEntera;
    parteEntera = atoi(p_parteEntera); // Como siempre es de decimal a destino, utilizo la librería.

    /* No se puede expresar el número en la base solicitada.
    if(parteEntera >= pow(*baseDestino, PARTE_ENTERA))
        exit(EXIT_FAILURE);*/
    decimalADestinoAux(&parteEntera, baseDestino, p_parteEntera, &contador);
}

/**
    Recibe como parametro la parte fraccionaria
    de un numero en base decimal, con su base destino.
    Y retorna su valor en la base destino.
**/
                                //se asume que la parte fraccionaria esta pasada por parametro como 0.<numero fraccionario> Al ser en base 10, se puede hacer esto
/*static char *decimalADestinoFrac(float* parteFrac, int* baseDestino){
    char* enBaseDestino;
    int* contador, *parteEntera, *termino;
    float* parteDecimal;

    *termino = 0;
    *contador = 0;

    while(*contador < PARTE_FRACCIONARIA && *parteFrac){

        *parteFrac *= *baseDestino;
        *parteEntera = *parteFrac;
        *parteFrac -= *parteEntera;
        *enBaseDestino = strcat(enBaseDestino, *pasajeChar(parteEntera));
        *contador++;

    }

    return enBaseDestino;

}
                    //se asume que la parte fraccionaria esta pasada por parametro como <numero fraccionario>
static int *origenADecimalFrac(char* parteFrac, int* baseDestino){

    int *posicion;
    float *enBaseDecimal;

    *posicion = strlen(parteFrac) - 1;
    *enBaseDecimal = 0;

    while(*posicion >= 0){
        *enBaseDecimal += pasajeInt(parteFrac + *posicion);
        *enBaseDecimal /= *baseDestino;
    }

    return enBaseDecimal;
}

*/

/** Separa la parte entera y la parte fraccionaria del número **/
static void separar(char *p_numero, char *p_parteEntera, char *p_parteFraccionaria){
    // OBS: No veo si tiene 2 comas ó si son todos numeros de la misma base porque eso ya se validó en el "validador.h"
    int size, i, parte;
    size = strlen(p_numero);
    parte = 0; // 0 indica que está leyendo en la parte entera, 1 en la parte fraccionaria
    int contador;
    contador = 0; // Posición de la parte entera o la parte fraccionaria.
    for(i = 0; i < size; i++){
        if(parte == 0) {
            if(*(p_numero+i) == ',') {
                    parte = 1;
                    *(p_parteEntera + (contador+1) ) = '\0';
                    contador = 0;
            } else {
                    *(p_parteEntera+contador) = *(p_numero+i);
                    contador++;
            }
        } else {
            *(p_parteFraccionaria+contador) = *(p_numero+i);
            contador++;
            if(i == (size-1))
                *(p_parteFraccionaria + (contador+1) ) = '\0';
        }
    }
    if(parte == 0)
        *(p_parteEntera + (contador+1) ) = '\0';
}

/** --- Funciones públicas --- **/

void convertir(char *p_numero, int *baseOrigen, int* baseDestino, int *mostrarPasos){
    char parteEntera[PARTE_ENTERA];
    char parteFraccionaria[PARTE_FRACCIONARIA];
    strcpy(parteEntera, "");
    strcpy(parteFraccionaria, "");

    char *p_parteEntera;
    char *p_parteFraccionaria;
    p_parteEntera = parteEntera;
    p_parteFraccionaria = parteFraccionaria;

    if( validar(p_numero, baseOrigen) == 0) { // ¿El número es válido y pertenece a la base? 0=sí
        /** El mayor número representable de una base r contando con 10 dígitos en la parte entera es N = r^10. (En sistema decimal) **/
        /** Base 10 a base r -> se verifica el numero ingresado **/
        /** Base r a base 10 -> se verifica una vez se convirtió el entero **/
        /** Base r a base d -> se verifica una vez se convirtió el entero de base r a base 10 (cuando se usa la base 10 de auxiliar) <- COMPLETAR ESTE **/

        /** Si la bases son iguales, es el mismo número **/
        if(*baseOrigen == *baseDestino){
            if(*mostrarPasos == 1)
                printf("[convertir] Las bases son iguales, por ende el número no se convierte.");
            // agregar excepción si supera los limites permitidos.
        }

        /** Hace una conversión de base 10 a base r **/
        else if(*baseOrigen == 10 && *baseDestino != 10){
            separar(p_numero, p_parteEntera, p_parteFraccionaria);
            decimalADestino(p_parteEntera, baseDestino);
            printf("Parte entera convertida (decimal a destino): %s\n", parteEntera);
            // Falta hacer la parte fraccionaria y unir en el numero original.
                if(strlen(parteFraccionaria) > 0){
                        // Tiene parte fraccionaria, hago la conversión.
                }
        }

        /** Hace una conversión de base r a base 10 **/
        else if(*baseOrigen != 10 && *baseDestino == 10){
            separar(p_numero, p_parteEntera, p_parteFraccionaria);
            origenADecimal(p_parteEntera, baseOrigen);
           printf("Parte entera convertida (origen a destino): %s\n", parteEntera);
           // Falta hacer la parte fraccionaria y unir en el numero original.
           if(strlen(parteFraccionaria) > 0){
                        // Tiene parte fraccionaria, hago la conversión.
                }
        }

        /** Base origen r y base destino d diferentes a 10. Entonces, se utiliza como auxiliar la base 10 para hacer la conversión. **/
        else {
            /** Conversión de base r a base 10. **/

            /** Conversión de base 10 a base d **/

        }
    } else exit(EXIT_FAILURE);
}

#endif // CONVERTIDOR_H_INCLUDED
