#ifndef CONVERTIDORES_H_INCLUDED
#define CONVERTIDORES_H_INCLUDED

/** Convierte la parte entera de un número de base 10 a un numero de base destino.
    parteEntera: cadena que contiene la parte entera que se convertirá. Se copiará en esta cadena la parte convertida.
    baseOrigen: la base origen del numero.
    mostrarPasos: variable que contiene si está activa la impresión del algoritmo en la consola.
**/
extern void origenADecimal(char* parteEntera, int* baseOrigen, int* mostrarPasos);

/** Convierte la parte entera de un número de base 10 a un número de base destino.
    parteEntera: cadena que contiene la parte entera que se convertirá. Se copiará en esta cadena la parte convertida.
    baseDestino: la base destino del número.
    mostrarPasos: variable que contiene si está activa la impresión del algoritmo en la consola.
**/
extern void decimalADestino(char* parteEntera, int* baseDestino, int* mostrarPasos);

/** Convierte la parte fraccionaria de un número de base 10 a un número de base destino.
    parteFraccionaria: cadena que contiene la parte fraccionaria que se convertirá. Se copiará en esta cadena la parte convertida.
    baseDestino: la base destino del número.
    mostrarPasos: variable que contiene si está activa la impresión del algoritmo en la consola.
**/
extern void decimalADestinoFrac(char* parteFraccionaria, int* baseDestino, int* mostrarPasos);

/** Convierte la parte fraccionaria de un número de base 10 a un numero de base destino.
    parteFraccionaria: cadena que contiene la parte fraccionaria que se convertirá. Se copiará en esta cadena la parte convertida.
    baseOrigen: la base origen del numero.
    mostrarPasos: variable que contiene si está activa la impresión del algoritmo en la consola.
**/
extern void origenADecimalFrac(char* parteFrac, int* baseOrigen, int* mostrarPasos);

#endif // CONVERTIDORES_H_INCLUDED
