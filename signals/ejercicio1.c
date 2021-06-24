#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

int continuar=1;

void capturar_senal(int iNumSen, siginfo_t *info, void *ni)
{
    printf("\nSe recibió la señal.");
    continuar=0;
}

int main()
{
    time_t rawtime;
    struct tm *timeinfo;
    clock_t tiempo_inicio, tiempo_final;
    double segundos;
    
    
    tiempo_inicio = clock();

    struct sigaction act;              // La estructura que definirá como manejar la señal
    act.sa_sigaction = capturar_senal; // Definimos la rutina.
    sigfillset(&act.sa_mask);          // Bloqueamos todas las señales mientras se ejecuta la rutina.
    act.sa_flags = SA_SIGINFO;         // Es para que la estructura llegue instanciada a la rutina.
    
    sigaction(SIGINT, &act, NULL);     // Establecemos la captura de la señal.

    while (continuar == 1){
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        printf("\nHora Actual:  %s\n", asctime(timeinfo));
        sleep(5);
    }

    tiempo_final = clock();
    segundos = (double)(tiempo_inicio - tiempo_final) / CLOCKS_PER_SEC; 

    printf("Segundos Transcurridos desde el inicio: %f\n", segundos);
       
    return 0;
}
