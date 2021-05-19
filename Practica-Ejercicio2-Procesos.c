#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct dato
{
    int DNI;
    char CUIL[20];
    int IVA;
    float MONTO;
};

struct dato cliente;

void informarAFIP();
void grabarFactura();
void capturarDatos();
void imprimirFactura();

int main(int argc, char const *argv[])
{

    pid_t pidHijo1;
    pid_t pidHijo2;

    capturarDatos();

    pidHijo1 = fork();

    if (pidHijo1 == 0)
    {
        /* Código del hijo 1 */
        informarAFIP();
    }
    else
    {
        /* Código del proceso principal*/
        pidHijo2 = fork();
        if (pidHijo2 == 0)
        {
            /* Código del hijo 2 */
            grabarFactura();
        }
        else
        {
            /* Código del proceso principal */
            waitpid(pidHijo1, NULL, 0);
            waitpid(pidHijo2, NULL, 0);

            //Acá debemos informar la factura
            imprimirFactura();
        }
    }

    //printf("Línea 19 PADRE %d HIJO %d\n", getppid(), getpid());
    return 0;
}

void grabarFactura()
{
    sleep(3);

    printf("Factura grabada (PADRE: %d - HIJO: %d) \n", getppid(), getpid());
}

void informarAFIP()
{
    sleep(2);

    printf("Informando a la AFIP.... (PADRE: %d - HIJO: %d)\n", getppid(), getpid());
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
    printf("\n\n\n\n\n\n\nIMPRIMIR FACTURA.... (PADRE: %d - HIJO: %d)\n", getppid(), getpid());
}