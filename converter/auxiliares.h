#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED

/** Procesa el caracter de la posicion actual y devuelve su valor tipo entero equivalente.
    posicionActual: es la caracter a pasar a int.
    retorna el entero equivalente.
**/
extern int* pasajeInt(char *posicionActual);

/** Procesa el entero actual y retorna su caracter equivalente
    actual: es el entero a pasar a char.
    retorna el char equivalente.
**/
extern char* pasajeChar(int* actual);

/** Separa la parte entera y la parte fraccionaria del número
    numero: es el número que se separará.
    parteEntera: cadena que contendrá la parte entera del número.
    parteFraccionaria: cadena que contendrá la parte fraccionaria del número.
**/
extern void separar(char *numero, char *parteEntera, char *parteFraccionaria);

/**
    Valida si el número pasado como parametro pertenece a la base r.
    numero: numero a comprobar.
    r: base del numero.
    Si pertenece retorna 0, caso contrario, 1.
**/
extern int* validar(char *numero, int *r);

#endif // AUXILIARES_H_INCLUDED
