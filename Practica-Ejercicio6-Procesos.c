#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

    pid_t pidHijo1;
    pid_t pidHijo2;
    pid_t pidHijo3;
    pid_t pidHijo4;
    pid_t pidHijo5;
    pid_t pidHijo6;
    pid_t pidHijo7;
    pid_t pidHijo8;

    printf("Hola soy Mirtha Legrand, mi ID es %d. Nací en 1927. Tengo 94 años\n", getpid());

    pidHijo1 = fork();

    if (pidHijo1 == 0){
        //Daniel Andrés Tinayre (hijo 1)
        printf("Nombre Completo: Daniel Andrés Tinayre\n");
        printf("Mi ID: %d\n", getpid());
        printf("El ID de mi madre es: %d\n", getppid());
        printf("Naci el año 1949\n");
        printf("Mi edad es: 40 años\n\n");
    }else{
        /* Mirtha Madre*/
        pidHijo2 = fork();

        if (pidHijo2 == 0){
             /* Marcela Tinayre (hijo 2) */
            printf("Nombre Completo: Marcela Tinayre\n");
            printf("Mi ID: %d\n", getpid());
            printf("El ID de mi madre es: %d\n", getppid());
            printf("Naci el año 1950\n");
            printf("Mi edad es: 71 años\n\n");

            pidHijo3=fork();
            if(pidHijo3 == 0){
                /* Ignacio Viale (hijo de MARCELA)*/
                printf("Nombre Completo: Ignacio Viale\n");
                printf("Mi ID: %d\n", getpid());
                printf("El ID de mi madre es: %d\n", getppid());
                printf("Naci el año 1981\n");
                printf("Mi edad es: 40 años\n\n");
            }else{
                 /* Marcela Tinayre (hijo 2) */
                 pidHijo4=fork();
                 if(pidHijo4==0){
                     /* Juana Viale (hija de MARCELA)*/
                    printf("Nombre Completo: Juana Viale\n");
                    printf("Mi ID: %d\n", getpid());
                    printf("El ID de mi madre es: %d\n", getppid());
                    printf("Naci el año 1982\n");
                    printf("Mi edad es: 39 años\n\n");
                    pidHijo6=fork();
                    if(pidHijo6==0){
                        /* Ambar de benedictis (hija de Juana)*/
                        printf("Nombre Completo: Ambar de benedictis\n");
                        printf("Mi ID: %d\n", getpid());
                        printf("El ID de mi madre es: %d\n", getppid());
                        printf("Naci el año 2003\n");
                        printf("Mi edad es: 18 años\n\n");
                    }else{
                        /* Juana Viale (hija de MARCELA)*/
                        pidHijo7=fork();
                        if(pidHijo7==0){
                            /* Silvestre VALENZUELA (hijo de Juana)*/
                            printf("Nombre Completo: Silvestre Valenzuela\n");
                            printf("Mi ID: %d\n", getpid());
                            printf("El ID de mi madre es: %d\n", getppid());
                            printf("Naci el año 2008\n");
                            printf("Mi edad es: 13 años\n\n");
                        }else{
                            /* Juana Viale (hija de MARCELA)*/
                            pidHijo8=fork();
                            if(pidHijo8==0){
                                /* Ali Valenzuela (hijo de Juana)*/
                                printf("Nombre Completo: Ali Valenzuela\n");
                                printf("Mi ID: %d\n", getpid());
                                printf("El ID de mi madre es: %d\n", getppid());
                                printf("Naci el año 2011\n");
                                printf("Mi edad es: 12 años\n\n");
                            }else{
                                /* Juana Viale (hija de MARCELA)*/
                                waitpid(pidHijo6, NULL, 0);
                                waitpid(pidHijo7, NULL, 0);
                                waitpid(pidHijo8, NULL, 0);
                            }
                        }
                    }
                 }else{
                     /* Marcela Tinayre (hijo 2) */
                     pidHijo5=fork();
                     if(pidHijo5==0){
                        /* Rocco Viale (hijo de MARCELA)*/
                        printf("Nombre Completo: Rocco Viale\n");
                        printf("Mi ID: %d\n", getpid());
                        printf("El ID de mi madre es: %d\n", getppid());
                        printf("Naci el año 2001\n");
                        printf("Mi edad es: 20 años\n\n");
                    }else{
                        /* Marcela Tinayre (hijo 2) */
                        waitpid(pidHijo3, NULL, 0);
                        waitpid(pidHijo4, NULL, 0);
                        waitpid(pidHijo5, NULL, 0);
                    }
                 }
            }

        }else{
            /* Mirtha madre */
            waitpid(pidHijo1, NULL, 0);
            waitpid(pidHijo2, NULL, 0);
        }
    }

    return 0;
}
