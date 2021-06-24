#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STORAGE_ID "/SHM_TEST" //Nombre del objeto memoria compartida
#define STORAGE_SIZE 32        //Tamaño de la memoria compartida

int main(int argc, char *argv[])
{
	int res;
	int fd;
	char data[STORAGE_SIZE];
	pid_t pid;
	void *addr;

	pid = getpid();

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
	memcpy(data, addr, STORAGE_SIZE);

	printf("PID %d: Leyo desde memoria compartida: \"%s\"\n", pid, data);

    printf("PID %d: Termina: \n", pid);

	return 0;
}