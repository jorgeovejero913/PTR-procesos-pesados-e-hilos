#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CANTIDAD_MAXIMA 10000
#define CANTIDAD_DE_HILOS 10
void crearArchivo();

unsigned long int saldos = 0;
sem_t unSemaforo;

void * funcionLeeArchivo(void * args)
{
    //sleep(5);
    int numeroDeHilo = *(int *)args;

    printf("Número de hilo es: %d\n", numeroDeHilo + 1);

    FILE * archivo = fopen("saldos.txt", "r");

    int desde = numeroDeHilo * 1000 + 1;
    int hasta = desde + 999;
    char valorDelArchivo [10];

    for (int numeroDeRegistro = 1; numeroDeRegistro <= CANTIDAD_MAXIMA; numeroDeRegistro++)
    {
        fgets(valorDelArchivo, 10, archivo);
        if (numeroDeRegistro >= desde && numeroDeRegistro <= hasta)
        {

            sem_wait(&unSemaforo);
            /*Sección crítica INICIO */
            saldos = saldos + (unsigned long int) atoi(valorDelArchivo);
            /*Sección crítica FIN */
            sem_post(&unSemaforo);

        }
        
    }

}

int main(int argc, char const *argv[])
{
    int i = 0;
    //crearArchivo();

    sem_init(&unSemaforo, 0, 1);
    
    clock_t tiempo_inicio, tiempo_final;
    double segundos;

    tiempo_inicio = clock();

    pthread_t hilos[CANTIDAD_DE_HILOS];
    int parametros[CANTIDAD_DE_HILOS];
    for (i = 0; i < CANTIDAD_DE_HILOS; i++)
    {
        parametros[i] = i;
        pthread_create(&hilos[i], NULL, funcionLeeArchivo, &parametros[i]);
    }

    i = 0;
    while (i < CANTIDAD_DE_HILOS)
    {
        pthread_join(hilos[i], NULL);
        i++;
    }

    printf("El valor del saldo es: %ld\n", saldos);
    sem_destroy(&unSemaforo);
    tiempo_final = clock();
    segundos = (double)(tiempo_inicio - tiempo_final) / CLOCKS_PER_SEC; /*según que estes midiendo el tiempo en segundos es demasiado grande*/

    printf("Segundos EJERCICIO 2: %f\n",segundos);

    return 0;
}

void crearArchivo()
{
    FILE *archivo = NULL;
    int numero = 0; 

    archivo = fopen("saldos.txt", "w");

    for (int i = 0; i < CANTIDAD_MAXIMA; i++)
    {
        //rand () % (N-M+1) + M;   // Este está entre M y N
        numero = (rand() % (100));
        fprintf(archivo, "%d\n", numero);

    }
    
    fclose(archivo);
}