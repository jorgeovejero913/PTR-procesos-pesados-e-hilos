#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define STORAGE_ID "/COLORS" //Nombre del objeto memoria compartida
#define STORAGE_SIZE 8       //Tamaño de la memoria compartida
#define DATA "\x1b[31m"      //Prototipo de lo que queremos "almacenar" en la memoria compartida

struct auxiliar
{
    int id;
};
int main(int argc, char *argv[])
{
    //variables ejercicio
    pid_t proceso1;
    pid_t proceso2;
    pid_t proceso3;

    proceso1 = fork();
    if (proceso1 == 0)
    {
        int res;
        int fd;
        int len;
        void *addr;
        int aux = 1;
        char color[STORAGE_SIZE];

        while (1)
        {
            switch (aux)
            {
            case 1:
                strcpy(color, ANSI_COLOR_RED);
                break;
            case 2:
                strcpy(color, ANSI_COLOR_BLUE);
                break;
            case 3:
                strcpy(color, ANSI_COLOR_YELLOW);
                break;
            case 4:
                strcpy(color, ANSI_COLOR_GREEN);
                aux = 0;
                break;
            default:
                break;
            }
            printf("%s", color);
            printf("¡Hola mundo - Proceso 1!\n");
            printf(ANSI_COLOR_RESET);

            // crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
            fd = shm_open(STORAGE_ID, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            if (fd == -1)
            {
                perror("Error set.c: shm_open");
                return 10;
            }

            // Fija el tamaño del objeto de memoria compartida.
            res = ftruncate(fd, STORAGE_SIZE);
            if (res == -1)
            {
                perror("Error set.c: ftruncate");
                return 20;
            }

            // Mapea el objeto de memoria compartida en el espacio de direccionamiento.
            addr = mmap(NULL, STORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
            if (addr == MAP_FAILED)
            {
                perror("Error al mapear en set.c: mmap");
                return 30;
            }

            // Obtengo el largo de la cadena de caracteres data
            len = strlen(color) + 1;

            //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
            memcpy(addr, color, len);
            //printf("PID %d: Escribio en memoria compartida: \n", proceso1);

            // Espera 20 segundos a que alguien lea la memoria compartida.
            sleep(4);

            // Desmapea el objeto de memoria compartida del espacio de direcciones del proceso llamador (set.exe).
            res = munmap(addr, STORAGE_SIZE);
            if (res == -1)
            {
                perror("munmap");
                return 40;
            }

            // shm_open: Remueve el segmento de memoria compartida.
            fd = shm_unlink(STORAGE_ID);
            if (fd == -1)
            {
                perror("unlink");
                return 100;
            }

            aux++;
        }
        return 0;
    }

    proceso2 = fork();
    if (proceso2 == 0)
    {
        int res;
        int fd;
        void *addr;
        char color[STORAGE_SIZE];

        while (1)
        {
            // Obtengo el file descriptor de la memoria compartida.
            fd = shm_open(STORAGE_ID, O_RDONLY, S_IRUSR | S_IWUSR);
            if (fd == -1)
            {
                perror("Error get.c shm_open");
                return 10;
            }

            /* 
        Mapeamos la memoria compartida al espacio de dirección 
        de memoria del proceso
    */
            addr = mmap(NULL, STORAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
            if (addr == MAP_FAILED)
            {
                perror("Error shm_open mmap");
                return 30;
            }

            /*
        En la variable 'data' copiamos lo que tenemos en la dirección de memoria (un largo de STOREGE_SIZE).
    */
            memcpy(color, addr, STORAGE_SIZE);

            printf("%s", color);
            printf("¡Hola mundo - Proceso 2!\n");
            printf(ANSI_COLOR_RESET);

            sleep(3);
        }

        return 0;
    }

    proceso3 = fork();
    if (proceso3 == 0)
    {
        int res;
        int fd;
        void *addr;
        char color[STORAGE_SIZE];

        while (1)
        {
            // Obtengo el file descriptor de la memoria compartida.
            fd = shm_open(STORAGE_ID, O_RDONLY, S_IRUSR | S_IWUSR);
            if (fd == -1)
            {
                perror("Error get.c shm_open");
                return 10;
            }

            /* 
        Mapeamos la memoria compartida al espacio de dirección 
        de memoria del proceso
    */
            addr = mmap(NULL, STORAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
            if (addr == MAP_FAILED)
            {
                perror("Error shm_open mmap");
                return 30;
            }

            /*
        En la variable 'data' copiamos lo que tenemos en la dirección de memoria (un largo de STOREGE_SIZE).
    */
            memcpy(color, addr, STORAGE_SIZE);

            printf("%s", color);
            printf("¡Hola mundo - Proceso 3!\n");
            printf(ANSI_COLOR_RESET);

            sleep(3);
        }

        return 0;
    }

    waitpid(proceso1, NULL, 0);
    waitpid(proceso2, NULL, 0);
    waitpid(proceso3, NULL, 0);

    return 0;
}