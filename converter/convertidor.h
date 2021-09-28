#ifndef CONVERTIDOR_H_INCLUDED
#define CONVERTIDOR_H_INCLUDED

/**
    Convierte la cadena numero de la base baseOrigen a la base destino baseDestino. (Si *mostrarPasos == 1 se mostrará paso por paso la conversión)

    Si se pudo convertir retorna 0.
    retorna r (r>0) caso contrario.
**/
extern int* convertir(char *numero, int *baseOrigen, int* baseDestino, int *mostrarPasos);

#endif // CONVERTIDOR_H_INCLUDED
