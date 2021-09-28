#ifndef CONVERTIDORES_H_INCLUDED
#define CONVERTIDORES_H_INCLUDED

/** Convierte la parte entera de un n�mero de base 10 a un numero de base destino. **/
extern void origenADecimal(char* parteEntera, int* baseOrigen);

/** Convierte la parte entera de un n�mero de base 10 a un n�mero de base destino. **/
extern void decimalADestino(char* parteEntera, int* baseDestino);

/** Convierte la parte fraccionaria de un n�mero de base 10 a un n�mero de base destino. **/
extern void decimalADestinoFrac(char* parteFraccionaria, int* baseDestino);

/** Convierte la parte fraccionaria de un n�mero de base 10 a un numero de base destino. **/
extern void origenADecimalFrac(char* parteFrac, int* baseOrigen);

#endif // CONVERTIDORES_H_INCLUDED
