#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED

/** Procesa el caracter de la posicion actual y devuelve su valor tipo entero equivalente. **/
extern int* pasajeInt(char *posicionActual);

/** Procesa el entero actual y retorna su caracter equivalente **/
extern char* pasajeChar(int* actual);

/** Separa la parte entera y la parte fraccionaria del número **/
extern void separar(char *numero, char *parteEntera, char *parteFraccionaria);

/**
    Valida si el número pasado como parametro pertenece a la base r.
    Pertenece -> retorna 0
    No pertenece -> retorna 1
**/
extern int* validar(char *p_numero, int *r);

#endif // AUXILIARES_H_INCLUDED
