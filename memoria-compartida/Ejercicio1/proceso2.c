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




int main(int argc, char const *argv[])
{
    int fd;
    int len;
    int res;
    pid_t pid;
	void *addr;

    // crea y abre un objeto de memoria compartida nuevo, o abre una objeto existente.
	fd = shm_open("configuracion", O_RDONLY, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		perror("Error proceso2.c: shm_open");
		return 10;
	}

    // Mapea el objeto de memoria compartida en el espacio de direccionamiento.
	addr = mmap(NULL, sizeof(strConfig), PROT_READ, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("Error al mapear en proceso2.c: mmap");
		return 30;
	}


    len = sizeof(strConfig);
    pid = getpid();

    while (1)
    {
        memcpy(&strConfig, addr, len);
        
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
        
        
        sleep(3);
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