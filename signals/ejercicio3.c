#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

void capturar_senal(int iNumSen, siginfo_t *info, void *ni)
{
    printf("Se recibió la señal.\n");
}

//Cuerpo de la función
int contarVocales(char *cadena){
	int vocales = 0;
    int indice;
	// Recorrer toda la cadena
	for (indice=0; cadena[indice] != '\0'; ++indice){

		// Obtener el char de la posición en donde está el índice
		// y por otro lado convertirla a minúscula

		// Así no importa si ponen 'A' o 'a', ambas letras serán convertidas a 'a'
		char letraActual = tolower(cadena[indice]);


		if (
			letraActual == 'a' || 
			letraActual == 'e' || 
			letraActual == 'i' || 
			letraActual == 'o' || 
			letraActual == 'u'
			)
		{
			vocales++;
		}
	}
	return vocales;
}

void leerYMostrar(char texto[20] ){
    char valorDelArchivo [50];
    FILE * archivo;
    int cantidadVocales=0;

    archivo=fopen(texto, "r");
    while (fgets(valorDelArchivo, 50, archivo) != NULL){
        printf("%s \n", valorDelArchivo);
        cantidadVocales=cantidadVocales+contarVocales(valorDelArchivo);
    }
    printf("Cantidad de vocales: %i \n\n", cantidadVocales);
    cantidadVocales=0;
    pause();
}

int main()
{
    struct sigaction act;              // La estructura que definirá como manejar la señal
    act.sa_sigaction = capturar_senal; // Definimos la rutina.
    sigfillset(&act.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGUSR1, &act, NULL);     // Establecemos la captura de la señal.

    leerYMostrar("cadena1.txt");
    leerYMostrar("cadena2.txt");
    leerYMostrar("cadena3.txt");
    leerYMostrar("cadena4.txt");
    leerYMostrar("cadena5.txt");
    
    printf("\nTermino \n");
    return 0;
}

