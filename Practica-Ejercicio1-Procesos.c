#include <stdio.h>
#include <math.h>
#include <sys/types.h> // Se define el tipo de dato pid_t
#include <sys/wait.h>  //Se define la funci�n waitpid(pid_t pid)
#include <unistd.h>
#include<stdlib.h>
#include<ctype.h>

struct Lis
{
    int proceso;
    struct Lis *Sig;
};

void Ingresa(struct Lis **, pid_t);
void EsperarProcesos(struct Lis **);

int main()
{
    pid_t proceso=0;
    int opcion;
	struct Lis *Inicio=NULL;
    char *newargv[] = {"/bin/ping", "-c 4", "8.8.8.8", NULL};
    char *memoria[] = {"/bin/free", "-h", NULL};
    char *disco[] = {"/bin/df", "-h", NULL};
	char *newenviron[] = { NULL };

    do
    {
        printf("Escoja una opcion:\n");
        printf("0: Finalizar proceso principal\n");
        printf("1: Indicar la memoria utilizada y escribir en memoria.log\n");
        printf("2: Hacer un ping a 8.8.8.8, agregando esa info al archivo ping.log\n");
        printf("3: Informar el espacio en disco utilizado, agregando esa info al archivo disco.log\n");
        printf("Opcion seleccionada:");
        scanf("%d", &opcion);
        printf("\n\n");

	    proceso=fork();
        
        if(proceso != 0){
            //PADRE
        }else{
            switch (opcion)
            {
            case 1:
                freopen("memoria.log", "a+", stdout); 
                execve(memoria[0], memoria,  newenviron);
                Ingresa(&Inicio, getpid());
                break;
            case 2:
                freopen("ping.log", "a+", stdout); 
                execve(newargv[0], newargv,  newenviron);
                Ingresa(&Inicio, getpid());
                break;
            case 3:
                freopen("disco.log", "a+", stdout); 
                execve(disco[0], disco,  newenviron);
                Ingresa(&Inicio, getpid());
                break;
            default:
                break;
            }
            return 0;
        }

    } while (opcion != 0);

    EsperarProcesos(&Inicio);
    return 0;
}

void Ingresa(struct Lis **Principio, int proceso)
{
    struct Lis *Actual,*Nuevo,*Anterior;
    if(!(Nuevo=(struct Lis *)malloc(sizeof(struct Lis))))
    {
        printf("\n\nNo hay memoria disponible\n");
        printf("\n\nPresione una tecla para continuar\n");
        return;
    }
    Nuevo->proceso=proceso;
    if(!*Principio)
    {
        *Principio=Nuevo;
        Nuevo->Sig=NULL;
        return;
    }
    Anterior=*Principio;
    Actual=*Principio;
    while((Actual->proceso>Nuevo->proceso)&&Actual)
    {
        Anterior=Actual;
        Actual=Actual->Sig;
    }
    if(!Actual)
    {
        Anterior->Sig=Nuevo;
        Nuevo->Sig=NULL;
        return;
    }
    if(Anterior==Actual)
    {
        *Principio=Nuevo;
        Nuevo->Sig=Anterior;
        return;
    }
    Anterior->Sig=Nuevo;
    Nuevo->Sig=Actual;
}

void EsperarProcesos(struct Lis **Principio)
{
    struct Lis *Actual=*Principio;

    while(Actual)
    {
        printf("Proceso con pid: %d \n", Actual->proceso);
        waitpid(Actual->proceso, NULL, 0);
        Actual=Actual->Sig;
    }
}
