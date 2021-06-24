#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t sem1, sem2, sem3, sem4, sem5, sem6;

void *cocinarPanceta();
void *tostarPan();
void *cortarLechuga();
void *prepararMedallon();
void *cocinarMedallon();
void *armarHamburguesa();

void *cocinarPanceta()
{
    while (1)
    {
        sem_wait(&sem1); //sem1=0
        printf("\n1.COCINANDO PANCETA\n");
        sleep(rand() % ((6 + 1) - 1) + 1);
        // sleep(5);//para probar que el orden y concurrencia
        printf("\n1.PANCETA COCINADA\n");
        sem_post(&sem6); //sem6=1
    }
}
void *tostarPan()
{
    while (1)
    {
        sem_wait(&sem2); //sem2=0
        printf("\n2.TOSTANDO PAN\n");
        sleep(rand() % ((6 + 1) - 1) + 1);
        // sleep(5);//para probar que el orden y concurrencia
        printf("\n2.PAN TOSTADO\n");
        sem_post(&sem6); //sem6=2
    }
}
void *cortarLechuga()
{
    while (1)
    {
        sem_wait(&sem3); //sem3=0
        printf("\n3.CORTANDO LECHUGA\n");
        sleep(rand() % ((6 + 1) - 1) + 1);
        // sleep(5);//para probar que el orden y concurrencia
        printf("\n3.LECHUGA CORTADA\n");
        sem_post(&sem6); //sem6=3
    }
}
void *prepararMedallon()
{
    while (1)
    {
        sem_wait(&sem4); //sem4=0
        printf("\n4.PREPARANDO MEDALLON\n");
        sleep(rand() % ((6 + 1) - 1) + 1);
        // sleep(1);//para probar que el orden y concurrencia
        printf("\n4.MEDALLON PREPARADO\n");
        sem_post(&sem5); //sem5=1
    }
}
void *cocinarMedallon()
{
    while (1)
    {
        sem_wait(&sem5); //sem5=0
        printf("\n5.COCINANDO MEDALLON\n");
        sleep(rand() % ((6 + 1) - 1) + 1);
        // sleep(12);//para probar que el orden y concurrencia
        printf("\n5.MEDALLON COCINADO\n");
        sem_post(&sem6); //sem6=4
    }
}
void *armarHamburguesa()
{
    while (1)
    {
        //Al principio vale 0 sem6
        //Cuando otro proceso del 1 al 3 lo incrementa, vale 1

        sem_wait(&sem6); // Se clava, porque ninguno de los procesos se habilito 
        /**
         * Todo
         * aca
         * es codigo ejecutable 
        */
        // sem6=0
        sem_wait(&sem6);
/**
         * Todo
         * aca
         * es codigo ejecutable 
        */
        // sem6=0


        sem_wait(&sem6); //1

        /**
         * Todo
         * aca
         * es codigo ejecutable 
        */
        // sem6=0

        sem_wait(&sem6); //sem=0
        /**
         * Todo
         * aca
         * es codigo ejecutable 
        */
        // sem6=0
        printf("\n6.ARMANDO HAMBURGUESA\n");
        sleep(rand() % ((6 + 1) - 1) + 1);
        printf("\n6.HAMBURGUESA ARMADA :D\n\n");//Hasta aca todos los semaforos estan en 0
        
        sem_post(&sem1); //1
        sem_post(&sem2); //1
        sem_post(&sem3); //1
        sem_post(&sem4); //1
    }
}

void main()
{
    pthread_t hilos[6];

    //INIT SEMAFOROS
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);
    sem_init(&sem3, 0, 1);
    sem_init(&sem4, 0, 1);
    sem_init(&sem5, 0, 0);
    sem_init(&sem6, 0, 0);

    pthread_create(&hilos[0], NULL, cocinarPanceta, NULL);
    pthread_create(&hilos[1], NULL, tostarPan, NULL);
    pthread_create(&hilos[2], NULL, cortarLechuga, NULL);
    pthread_create(&hilos[3], NULL, prepararMedallon, NULL);
    pthread_create(&hilos[4], NULL, cocinarMedallon, NULL);
    pthread_create(&hilos[5], NULL, armarHamburguesa, NULL);

    for (int i = 0; i < 6; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    sem_destroy(&sem4);
    sem_destroy(&sem5);
    sem_destroy(&sem6);
}