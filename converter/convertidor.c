#include "convertidor.h"

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "convertidores.h"
#include "constantes.h"
#include "auxiliares.h"


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

    /** Comprueba si la cadena ingresada pertenece a la base. (Retorna 0 si pertenece) **/
    validador = validar(numero, baseOrigen);

    if( *validador == 0) {

        /** Separación de la parte fraccionaria y la parte entera **/
        separar(numero, parteEntera, parteFraccionaria);

        // OBS: Si bien, se comprobó que el numero no tenga longitud mayor a 16 puede tener una longitud en alguna de sus divisiones (entera y fraccionaria) que si exceda.
        if( strlen(parteEntera) > MAX_PARTEENTERA || strlen(parteFraccionaria) > MAX_PARTEFRACC) {
            *retorno = 1; // La parte entera o la parte fraccionaria supera el máximo de digitos permitidos.
        } else {

            /** -- Inicio convertidores -- **/

                /** Si la bases son iguales, es el mismo número **/
                if(*baseOrigen == *baseDestino){
                    if(*mostrarPasos == 1)
                        printf("[convertir] Las bases son iguales, por ende el número no se convierte.");
                }

                /** Hace una conversión de base 10 a base r **/
                else if(*baseOrigen == 10 && *baseDestino != 10){
                    decimalADestino(parteEntera, baseDestino, mostrarPasos);
                    strcpy(numero, parteEntera);
                    if(strlen(parteFraccionaria) > 0){
                            decimalADestinoFrac(parteFraccionaria, baseDestino, mostrarPasos);
                            strcat(numero, ",");
                            strcat(numero, parteFraccionaria);
                    }
                }

                /** Hace una conversión de base r a base 10 **/
                else if(*baseOrigen != 10 && *baseDestino == 10){
                    origenADecimal(parteEntera, baseOrigen, mostrarPasos);
                    strcpy(numero, parteEntera);

                    if(*mostrarPasos)
                        printf("= %d \n", *numero);

                    if(strlen(parteFraccionaria) > 0){
                            /** testear **/
                            origenADecimalFrac(parteFraccionaria, baseOrigen, mostrarPasos);
                            strcat(numero, ",");
                            strcat(numero, parteFraccionaria);
                    }
                }

                /** Base origen r y base destino d diferentes a 10. Entonces, se utiliza como auxiliar la base 10 para hacer la conversión. **/
                else {

                    /** Conversión de la parte entera **/
                        /** Conversión de base r a base 10 **/
                        origenADecimal(parteEntera, baseOrigen, mostrarPasos);
                        /** Conversión de base 10 a base d **/
                        decimalADestino(parteEntera, baseDestino, mostrarPasos);
                        strcpy(numero, parteEntera);

                    /** Una vez que ya se convirtió, ahora se convierte la parte fraccionaria si es que tiene **/
                    if(strlen(parteFraccionaria) > 0){
                            /** Conversión de base r a base 10 **/
                            origenADecimalFrac(parteFraccionaria, baseOrigen, mostrarPasos);
                            /** Conversión de base 10 a base d **/
                            decimalADestinoFrac(parteFraccionaria, baseDestino,mostrarPasos);
                            strcat(numero, ",");
                            strcat(numero, parteFraccionaria);
                    }
                }

            /** -- Fin convertidores -- **/
        }
    } else *retorno = 2;

    /** Liberación de memoria **/
    free(parteEntera); free(parteFraccionaria); free(validador);

    return retorno;
}
