#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

struct dato
{
    int DNI;
    char CUIL[20];
    int IVA;
    float MONTO;
};

struct dato cliente;

void *informarAFIP();
void *grabarFactura();
void capturarDatos();
void imprimirFactura();

int main(int argc, char const *argv[])
{

    pthread_t hilos[2];

    capturarDatos();

	pthread_create(&hilos[0], NULL, informarAFIP, NULL);
	pthread_create(&hilos[1], NULL, grabarFactura, NULL);

    for(int i=0;i<2;i++){
		pthread_join(hilos[i], NULL);
	}
    imprimirFactura();


    //printf("Línea 19 PADRE %d HIJO %d\n", getppid(), getpid());
    return 0;
}

void *grabarFactura()
{
    sleep(3);

    printf("Factura grabada (HILO: %d) \n", pthread_self());
}

void *informarAFIP()
{
    sleep(2);

    printf("Informando a la AFIP.... (HILO: %d) \n", pthread_self());
}

void capturarDatos()
{
    printf("Ingrese DNI\n");
    scanf("%d", &cliente.DNI);
    printf("Ingrese CUIL\n");
    scanf("%s", cliente.CUIL);
    printf("Ingrese si aplica IVA (1 = Si / 0 = No)");
    scanf("%d", &cliente.IVA);
    printf("Ingrese monto final");
    scanf("%f", &cliente.MONTO);
}

void imprimirFactura()
{
    printf("FACTURA ---- DATOS CLIENTE:\n");
    printf("Datos del cliente:\n");
    printf("\tDNI: %d", cliente.DNI);
    printf("\tCUIL: %s", cliente.CUIL);
    printf("\tIVA: %d", cliente.IVA);
    if (cliente.IVA == 1)
    {
        printf("\tMONTO FINAL: %f\n", cliente.MONTO * 1.21);
    }
    else
    {
        printf("\tMONTO FINAL: %f\n", cliente.MONTO);
    }
    printf("\n\n\n\n\n\n\nIMPRIMIR FACTURA.... (HILO: %d)\n", pthread_self());
}