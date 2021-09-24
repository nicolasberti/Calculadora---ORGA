#include "convertidor.h"

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "convertidores.h"
#include "constantes.h"
#include "auxiliares.h"

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
