#ifndef CONVERTIDOR_H_INCLUDED
#define CONVERTIDOR_H_INCLUDED

/**
    Convierte la cadena numero de la base baseOrigen a la base destino baseDestino. (Si *mostrarPasos == 1 se mostrar� paso por paso la conversi�n)
    numero: numero a convertir. El n�mero convertido (si fue posible) se copiar� en esta cadena.
    baseOrigen: base del numero.
    baseDestino: base en la cual se convertidor� el n�mero.
    mostrarPasos: variable que contiene si est� activa la impresi�n del algoritmo en la consola.
    Si el numero se pudo convertir retorna 0, en caso contrario, retorna un valor r > 0.
**/
extern int* convertir(char *numero, int *baseOrigen, int* baseDestino, int *mostrarPasos);

#endif // CONVERTIDOR_H_INCLUDED
