#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/** Macros **/

    /** Macro para el argumento -h **/
    #define mostrarUsoCorrecto   printf("Usa: %s -n <numero> [-s <base_origen>] [-d <base_destino>] [-v] [-h]\n", *argv)

    /** Lee el argumento A **/
    #define LEER(A) if( strcmp(*(argv+*i), A) ==0)

    /** Cantidad m�xima de digitos del n�mero (incluyendo el separador) **/
    #define MAXNUM 16

/** Constantes **/

    #define SEPARADOR ','           // Indica el separador que se utilizar�. Seg�n nuestra regi�n, usaremos la coma.

    #define MAX_PARTEENTERA     10  // M�ximos d�gitos permitidos en la parte entera
    #define MAX_PARTEFRACC      5   // M�ximos d�gitos permitidos en la parte fraccionaria

    #define PARTE_ENTERA        40 // El n�mero FFFFFFFFFF (base 16) a base 2 ocupa 40 digitos. Entonces ese el m�ximo de la parte entera.
    #define PARTE_FRACCIONARIA  40
    #define PRECISION           5  // Presici�n permitida seg�n el enunciado


#endif // CONSTANTES_H_INCLUDED
