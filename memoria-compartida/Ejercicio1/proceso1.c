#include <stdio.h>
#include <sys/mman.h>	//Librería para memoria compartida
#include <fcntl.h>		//Librería para memoria compartida
#include <unistd.h>
#include <string.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


struct configuracion
{
    char color[20];
};


struct configuracion  strConfig;
void *addr;

void cambiarColor()
{
    char rojo[20] = "ROJO";
    char amarillo[20] = "AMARILLO";
    char verde[20] = "VERDE";
    char azul[20] = "AZUL";


    if (strcmp(strConfig.color, rojo) == 0)
    {
        strcpy(strConfig.color, amarillo);
    }
    else 
    {
        if (strcmp(strConfig.color, amarillo) == 0)
        {
            strcpy(strConfig.color, verde);
        }
        else
        {
            if (strcmp(strConfig.color, verde) == 0)
            {
                strcpy(strConfig.color, azul);
            }
            else
            {
                if (strcmp(strConfig.color, azul) == 0)
                {
                    strcpy(strConfig.color, rojo);
                }
            }
        }           
    }
}


int main(int argc, char const *argv[])
{
    int fd;
    int len;
    int res;
    pid_t pid;
	

    // crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open("configuracion", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		perror("Error proceso1.c: shm_open");
		return 10;
	}

	// Fija el tamaño del objeto de memoria compartida.
	res = ftruncate(fd, sizeof(strConfig) ); // --> Si queremos crear un int --> sizeof(len) 
	if (res == -1)
	{
		perror("Error proceso1.c: ftruncate");
		return 20;
	}

    // Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, sizeof(strConfig), PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("Error al mapear en proceso1.c: mmap");
		return 30;
	}

    strcpy(strConfig.color, "ROJO");



    len = sizeof(strConfig);
    pid = getpid();

    while (1)
    {

        if (strcmp(strConfig.color, "ROJO") == 0)
        {
            printf(ANSI_COLOR_RED "Hola mundo desde %d con color: %s\n", pid, strConfig.color);
        }

        if (strcmp(strConfig.color, "VERDE") == 0)
        {
            printf(ANSI_COLOR_GREEN "Hola mundo desde %d con color: %s\n", pid, strConfig.color);
        }

        if (strcmp(strConfig.color, "AZUL") == 0)
        {
            printf(ANSI_COLOR_BLUE "Hola mundo desde %d con color: %s\n", pid, strConfig.color);
        }

        if (strcmp(strConfig.color, "AMARILLO") == 0)
        {
            printf(ANSI_COLOR_YELLOW "Hola mundo desde %d con color: %s\n", pid, strConfig.color);
        }

        //Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
	    memcpy(addr, &strConfig, len);
        cambiarColor();
        sleep(4);
    }
        
    // Desmapea el objeto de memoria compartida del espacio de direcciones del proceso llamador (set.exe).
	res = munmap(addr, sizeof(strConfig));
	if (res == -1)
	{
		perror("munmap");
		return 40;
	}

	// shm_unlink: Remueve el segmento de memoria compartida.
	fd = shm_unlink("configuracion");
	if (fd == -1)
	{
		perror("unlink");
		return 100;
	}


    return 0;
}