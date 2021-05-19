#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void crearDescendencia(int profundidad, int anchura);
int main (int argc, char *argv[]){
    int i;
    int profundidad, anchura;
    if (argc != 3) {
        printf("Debe ingresar 2 parametros\n");
        exit(0);
    }
    profundidad = atoi(argv[1]); /* profundidad */
    anchura = atoi(argv[2]); /* anchura */

    printf("Prof: %d / anchura: %d\n", profundidad, anchura);

    crearDescendencia(profundidad, anchura);
    
    return 0;
}

void crearDescendencia(int profundidad, int anchura)
{
    pid_t hijos[anchura];
    
    printf("Soy el proceso %d y mi padre es %d\n", getpid(), getppid());
    
    if (profundidad > 1)
    {
        /*Acá creo los hijos*/
        for (int i = 0; i < anchura; i++)
        {
            hijos[i] = fork();
            if (hijos[i] == 0)
            {
                //Primer hijo
                if( i == 0 )
                {
                    crearDescendencia((profundidad-1), anchura);
                }
                else{
                    sleep(5);
                }
                exit(0);
            }   
        }
        /*Acá espero a los hijos*/
        for (int i = 0; i < anchura; i++)
        {
            waitpid(hijos[i], NULL, 0);
        }
    }    
}

