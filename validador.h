#include <stdio.h>
#include <string.h>

#ifndef VALIDADOR_H_INCLUDED
#define VALIDADOR_H_INCLUDED

/**
    Funci�n: validar
    Descripci�n: Valida si la cadena ingresada como parametro es un n�mero de la base r. Admite numeros fraccionarios.
    Parametros:
                char *p_numero: Puntero a la cadena.
                int *r: Puntero a la base a la cual se validar� la cadena.
    Retorna 0 si es un numero de la base r.
    Retorna 1 en caso contrario. (ya sea que no es de la base r o no es un numero)
**/
int validar(char *p_numero, int *r){
    int size, retorno, contador, i;
    size = strlen(p_numero); // Tama�o del n�mero.
    retorno = 0;
    contador = 0;
    char caracteres[25] = "";
    switch(*r){
            case 16: strcat(caracteres, "Ff");
            case 15: strcat(caracteres, "Ee");
            case 14: strcat(caracteres, "Dd");
            case 13: strcat(caracteres, "Cc");
            case 12: strcat(caracteres, "Bb");
            case 11: strcat(caracteres, "Aa");
            case 10: strcat(caracteres, "9");
            case 9: strcat(caracteres, "8");
            case 8: strcat(caracteres, "7");
            case 7: strcat(caracteres, "6");
            case 6: strcat(caracteres, "5");
            case 5: strcat(caracteres, "4");
            case 4: strcat(caracteres, "3");
            case 3: strcat(caracteres, "2");
            case 2: strcat(caracteres, "01");
    }
    if(size == 1 && *(p_numero) == ',') // Si el usuario ingresa simplemente una coma, no es un n�mero v�lido.
        retorno = 1;
    else if(*(p_numero+size-1) == ',') // Si el usuario ingresa un n�mero que termina con una coma, no es un n�mero v�lido.
        retorno = 1;
    else {
        for(i = 0; i < size && retorno == 0; i++){
            int igual;
            igual = 1;
            if(*(p_numero+i) == ',') { // Si el caracter es una coma, la cuenta ya que si contiene m�s de 1, es inv�lido.
                    contador++;
                    igual = 0;
            } else {
                for(int j = 0; j < strlen(caracteres) && igual==1; j++){
                    if(*(p_numero+i) == caracteres[j])
                        igual = 0;
                }
            }
            retorno = igual;
            if(contador > 1)
                retorno = 1;
        }
    }
    return retorno;
}


#endif // VALIDADOR_H_INCLUDED