#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/** Macros **/

    /** Macro para el argumento -h **/
    #define mostrarUsoCorrecto   printf("Usa: %s -n <numero> [-s <base_origen>] [-d <base_destino>] [-v] [-h]\n", *argv)

    /** Lee el argumento A **/
    #define LEER(A) if( strcmp(*(argv+*i), A) ==0)

    /** Cantidad máxima de digitos del número (incluyendo el separador) **/
    #define MAXNUM 16

/** Constantes **/

    #define SEPARADOR ','           // Indica el separador que se utilizará. Según nuestra región, usaremos la coma.

    #define MAX_PARTEENTERA     10
    #define MAX_PARTEFRACC      5

    #define PARTE_ENTERA        40 // El número FFFFFFFFFF (base 16) a base 2 ocupa 40 digitos. Entonces ese el máximo de la parte entera.
    #define PARTE_FRACCIONARIA  40
    #define PRECISION           5


#endif // CONSTANTES_H_INCLUDED
