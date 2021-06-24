#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

int PANTALLA=1;

void capturar_senal_USR1(int iNumSen, siginfo_t *info, void *ni)
{
    //printf("Se recibió la señal.\n");
    PANTALLA=0;
}

void capturar_senal_USR2(int iNumSen, siginfo_t *info, void *ni)
{
    //printf("Se recibió la señal.\n");
    PANTALLA=1;
}

void escribirEnArchivo(long int numero)
{
    FILE *archivo = NULL;

    archivo = fopen("numeros-ejercicio4.txt", "a+");

    fprintf(archivo, "%ld\n", numero);
    
    fclose(archivo);
}

int main()
{
    int numero;
    struct sigaction act;              // La estructura que definirá como manejar la señal
    act.sa_sigaction = capturar_senal_USR1; // Definimos la rutina.
    sigfillset(&act.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGUSR1, &act, NULL);     // Establecemos la captura de la señal.


    struct sigaction act2;              // La estructura que definirá como manejar la señal
    act2.sa_sigaction = capturar_senal_USR2; // Definimos la rutina.
    sigfillset(&act2.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act2.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    sigaction(SIGUSR2, &act2, NULL);     // Establecemos la captura de la señal.
			

    do{
        printf("Ingrese un numero: ");
        scanf("%d", &numero);

        int i;
        long int factNum=1;
        for(i=2; i <= numero; i++){
            factNum=factNum*i;
        }
        if(PANTALLA == 1){
            printf("\nEl factorial de %i es: %ld \n\n", numero, factNum);
        }else{
            escribirEnArchivo(factNum);
            printf("\n");
        }
    }while (numero != 0);
    
    printf("\nTerminamos\n");
    return 0;
}