#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void *avanzarTortuga();
void *avanzarLiebre();

#define CANTIDAD_DE_METROS_PISTA 70

int caminoTortuga=1;
int caminoLiebre=1;

/*
    Ejercicio modificado
    Carrera de la liebre y la tortuga con probabiliades para avanzar o retroceder.
    Cuando termina un animal, el otro tambien termina
*/
void *avanzarTortuga()
{
    while(caminoTortuga < CANTIDAD_DE_METROS_PISTA && caminoLiebre < CANTIDAD_DE_METROS_PISTA){
        // Esto representa 100% de probabilidad 
        int probabilidad = rand () % 10; // esto es entre 0 y 9 (N+1)
        sleep(2);
        printf("Probabilidad: %d\n", probabilidad); //no va
        if(probabilidad >=0 && probabilidad <= 4){
            // probabilidad del 50% - Avance rapido
            caminoTortuga=caminoTortuga + 3;
            printf("Yo la TORTUGA, avance 3 metros.\n");
        }else if(probabilidad >=5 && probabilidad <= 7){
            // probabilidad del 30% - Avance lento
            caminoTortuga=caminoTortuga + 1;
            printf("Yo la TORTUGA, avance 1 metros.\n");
        }else if(probabilidad >=8 && probabilidad <= 9){
            // probabilidad del 20% - Resbalo
            if((caminoTortuga - 6) >= 1){
                caminoTortuga=caminoTortuga -6;
                printf("Yo la TORTUGA, retrocedi 6 metros.\n");
            }else{
                caminoTortuga=1;
                printf("Yo la TORTUGA, volvi a la salida.\n");
            }
        }
                
        printf("Yo la TORTUGA, voy avanzando %d metros.\n\n", caminoTortuga);
    }

    if(caminoLiebre >= CANTIDAD_DE_METROS_PISTA){
        printf("\n\nYo la TORTUGA, PERDI\n");
    }else{
        printf("\n\nYo la TORTUGA, llegue a la META\n");
    }
}

void *avanzarLiebre()
{
        while(caminoLiebre < CANTIDAD_DE_METROS_PISTA && caminoTortuga < CANTIDAD_DE_METROS_PISTA){
        // Esto representa 100% de probabilidad 
        int probabilidad = rand () % 10; // esto es entre 0 y 9 (N+1)
        sleep(2);
        printf("Probabilidad: %d\n", probabilidad); /no va
        if(probabilidad >=0 && probabilidad <= 1){
            // probabilidad del 20% - Duerme
            caminoLiebre=caminoLiebre + 0;
            printf("Yo la LIEBRE, avance 0 metros.\n");
        }else if(probabilidad >=2 && probabilidad <= 3){
            // probabilidad del 20% - Gran salto
            caminoLiebre=caminoLiebre + 9;
            printf("Yo la LIEBRE, avance 9 metros.\n");
        }else if(probabilidad == 4){
            // probabilidad del 10% - Resbalon grande
            if((caminoLiebre - 12) >=1){
                caminoLiebre=caminoLiebre - 12;
                printf("Yo la LIEBRE, retrocedi 12 metros.\n");
            }else{
                caminoLiebre=1;
                printf("Yo la LIEBRE, volvi a la salida.\n");
            }
        }else if(probabilidad >=5 && probabilidad <= 7){
            // probabilidad del 30% - Pequeño salto
            caminoLiebre=caminoLiebre + 1;
            printf("Yo la LIEBRE, avance 1 metros.\n");
        }else if(probabilidad >=8 && probabilidad <= 9){
            // probabilidad del 20% - Resbalon pequeño
            if((caminoLiebre - 2) >=1){
                caminoLiebre=caminoLiebre - 2;
                printf("Yo la LIEBRE, retrocedi 2 metros.\n");
            }else{
                caminoLiebre=1;
                printf("Yo la LIEBRE, volvi a la salida.\n");
            }
        }
        printf("Yo la LIEBRE, voy avanzando %d metros.\n\n", caminoLiebre);

    }

    if(caminoTortuga >= CANTIDAD_DE_METROS_PISTA){
        printf("\n\nYo la LIEBRE, PERDI\n");
    }else{
        printf("\n\nYo la LIEBRE, llegue a la META\n");
    }
}

int main(int argc, char const *argv[])
{

    pthread_t liebre;
    pthread_t tortuga;
    printf("### COMIENZA LA CARRERA ###\n\n\n");
    //CREAMOS
    pthread_create(&liebre, NULL, avanzarLiebre, NULL);
    pthread_create(&tortuga, NULL, avanzarTortuga, NULL);

    //ESPERAMOS
    pthread_join(liebre, NULL);
    pthread_join(tortuga, NULL);

    printf("\n\nTERMINO LA CARRERA\n");
    
    return 0;
}
