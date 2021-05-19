#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


#define CANTIDAD_CABALLOS 6
#define CANTIDAD_DE_METROS_PISTA 20

int gNumeroDeCaballoGanador = -1;


void realizarCarreraFavoritos(int pPosicion)
{
    //rand () % (N-M+1) + M;   // Este está entre M y N
    int pasos = (rand() % (3 - 2 + 1) + 2);
    int posicion = pPosicion;
    int avance = pasos;

    //Salto del caballo
    while (avance < CANTIDAD_DE_METROS_PISTA)
    {
        sleep(1);
        pasos = (rand() % (3 - 2 + 1) + 2);
        if ((avance + pasos) < CANTIDAD_DE_METROS_PISTA)
        {
            avance += pasos;
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", getpid(), (posicion + 1), pasos, avance);
        }
        else
        {
            avance += pasos;
            if (gNumeroDeCaballoGanador == -1)
            {
                gNumeroDeCaballoGanador = pPosicion + 1;
            }
            

            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", getpid(), (posicion + 1), pasos, avance);
            printf("El caballo %d terminó la carrera\n", (posicion + 1));
        }
    }
}

void realizarCarreraComunes(int pPosicion)
{
    //rand () % (N-M+1) + M;   // Este está entre M y N
    int pasos = (rand() % (3 - 2 + 1) + 2);
    int posicion = pPosicion;
    int avance = pasos;

    //Salto del caballo
    while (avance < CANTIDAD_DE_METROS_PISTA)
    {
        sleep(1);
        pasos = (rand() % (3 - 2 + 1) + 2);
        if ((avance + pasos) < CANTIDAD_DE_METROS_PISTA)
        {
            avance += pasos;
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", getpid(), (posicion + 1), pasos, avance);
        }
        else
        {
            avance += pasos;
            if (gNumeroDeCaballoGanador == -1)
            {
                gNumeroDeCaballoGanador = pPosicion + 1;
            }
            printf("%d - Caballo # %d avanza %d (total hasta el momento: %d)\n ", getpid(), (posicion + 1), pasos, avance);
            printf("El caballo %d terminó la carrera\n", (posicion + 1));
        }
    }
}

int main(int argc, char const *argv[])
{
    gNumeroDeCaballoGanador = -4;
    pid_t caballos[CANTIDAD_CABALLOS];
    int i = 0;

    caballos[0] = fork();

    if (caballos[0] == 0)
    {
        realizarCarreraFavoritos(0);

        return 0;
    }

    gNumeroDeCaballoGanador = -3;
    if (caballos[0] == -1)
    {
        printf("Error no pudo crear el proceso hijo\n");
    }


    caballos[1] = fork();

    if (caballos[1] == 0)
    {
        realizarCarreraComunes(1);

        return 0;
    }
    if (caballos[1] == -1)
    {
        printf("Error no pudo crear el proceso hijo\n");
    }

    caballos[2] = fork();

    if (caballos[2] == 0)
    {
        realizarCarreraComunes(2);

        return 0;
    }
    if (caballos[2] == -1)
    {
        printf("Error no pudo crear el proceso hijo\n");
    }


    caballos[3] = fork();

    if (caballos[3] == 0)
    {
        realizarCarreraComunes(3);

        return 0;
    }
    if (caballos[3] == -1)
    {
        printf("Error no pudo crear el proceso hijo\n");
    }

    caballos[4] = fork();

    if (caballos[4] == 0)
    {
        realizarCarreraFavoritos(4);

        return 0;
    }
    if (caballos[4] == -1)
    {
        printf("Error no pudo crear el proceso hijo\n");
    }

    caballos[5] = fork();

    if (caballos[5] == 0)
    {
        realizarCarreraComunes(5);

        return 0;
    }
    if (caballos[5] == -1)
    {
        printf("Error no pudo crear el proceso hijo\n");
    }


    for (i = 0; i < CANTIDAD_CABALLOS; i++)
    {
        waitpid(caballos[i], NULL, 0);
    }
    
    printf("El caballo ganador fue: %d\n", gNumeroDeCaballoGanador);

    return 0;
}
