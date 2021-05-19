#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define CANTIDAD_CABALLOS 6
#define CANTIDAD_DE_METROS_PISTA 20

void *realizarCarreraFavoritos(void *arguments);
void *realizarCarrreraComunes(void *arguments);

int gNumeroCaballo = -1;

int caballos[CANTIDAD_CABALLOS];

void *realizarCarreraFavoritos(void *arguments)
{
    //rand () % (N-M+1) + M;   // Este está entre M y N
    int avance = (rand() % (4 - 3 + 1) + 4);
    int posicion = *(int *)arguments;

    //Salto del caballo
    while (caballos[posicion] < CANTIDAD_DE_METROS_PISTA)
    {
        //Cuanto salta el caballo
        sleep(1);
        avance = (rand() % (4 - 3 + 1) + 4);
        if ((caballos[posicion] + avance) <= CANTIDAD_DE_METROS_PISTA)
        {
            caballos[posicion] += avance;
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", pthread_self(), (posicion + 1), avance, caballos[posicion]);
        }
        else
        {
            if (gNumeroCaballo == -1)
            {
                gNumeroCaballo = posicion + 1;
            }
            
            caballos[posicion] += avance;
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", pthread_self(), (posicion + 1), avance, caballos[posicion]);
            printf("El caballo %d terminó la carrera\n", (posicion + 1));
        }
    }
}

void *realizarCarrreraComunes(void *arguments)
{
    //rand () % (N-M+1) + M;   // Este está entre M y N
    int avance = (rand() % (3 - 2 + 1) + 2);
    int posicion = *(int *)arguments;

    //Salto del caballo
    while (caballos[posicion] < CANTIDAD_DE_METROS_PISTA)
    {
        sleep(1);
        avance = (rand() % (3 - 2 + 1) + 2);
        if ((caballos[posicion] + avance) < CANTIDAD_DE_METROS_PISTA)
        {
            caballos[posicion] += avance;
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", pthread_self(), (posicion + 1), avance, caballos[posicion]);
        }
        else
        {
            if (gNumeroCaballo == -1)
            {
                gNumeroCaballo = posicion + 1;
            }

            caballos[posicion] += avance;
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", pthread_self(), (posicion + 1), avance, caballos[posicion]);
            printf("El caballo %d terminó la carrera\n", (posicion + 1));
        }
    }
}

int main(int argc, char const *argv[])
{

    pthread_t hilos[CANTIDAD_CABALLOS];
    int i = 0;
    gNumeroCaballo = -1;

    while (i < CANTIDAD_CABALLOS)
    {
        caballos[i] = 0;
        if (i == 0 || i == 4) //Si es uno de los favoritos
        {
            pthread_create(&hilos[i], NULL, realizarCarreraFavoritos, &i);
        }
        else
        {
            pthread_create(&hilos[i], NULL, realizarCarrreraComunes, &i);
        }

        i++;
    }

    i = 0;
    while (i < CANTIDAD_CABALLOS)
    {
        pthread_join(hilos[i], NULL);
        i++;
    }

    printf("El primer caballo en llegar a la meta ha sido: %d", gNumeroCaballo);
    

    return 0;
}
