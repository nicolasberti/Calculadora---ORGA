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

/** Separa la parte entera y la parte fraccionaria del n�mero
    numero: es el n�mero que se separar�.
    parteEntera: cadena que contendr� la parte entera del n�mero.
    parteFraccionaria: cadena que contendr� la parte fraccionaria del n�mero.
**/
extern void separar(char *numero, char *parteEntera, char *parteFraccionaria);

/**
    Valida si el n�mero pasado como parametro pertenece a la base r.
    numero: numero a comprobar.
    r: base del numero.
    Si pertenece retorna 0, caso contrario, 1.
**/
extern int* validar(char *numero, int *r);

#endif // AUXILIARES_H_INCLUDED
