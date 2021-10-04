#ifndef CONVERTIDOR_H_INCLUDED
#define CONVERTIDOR_H_INCLUDED

/**
    Convierte la cadena numero de la base baseOrigen a la base destino baseDestino. (Si *mostrarPasos == 1 se mostrará paso por paso la conversión)
    numero: numero a convertir. El número convertido (si fue posible) se copiará en esta cadena.
    baseOrigen: base del numero.
    baseDestino: base en la cual se convertidorá el número.
    mostrarPasos: variable que contiene si está activa la impresión del algoritmo en la consola.
    Si el numero se pudo convertir retorna 0, en caso contrario, retorna un valor r > 0.
**/
extern int* convertir(char *numero, int *baseOrigen, int* baseDestino, int *mostrarPasos);

#endif // CONVERTIDOR_H_INCLUDED
