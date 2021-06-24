#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STORAGE_ID "/SHM_TEST"               //Nombre del objeto memoria compartida
#define STORAGE_SIZE 32                      //Tamaño de la memoria compartida
#define DATA "Hola Mundo! Desde PID %d"     //Prototipo de lo que queremos "almacenar" en la memoria compartida

int main(int argc, char *argv[])
{
	int res;
	int fd;
	int len;
	pid_t pid;
	void *addr;
	char data[STORAGE_SIZE];

	pid = getpid();
	sprintf(data, DATA, pid);  //Si el pid es 15... en data tendremos = "Hola Mundo! Desde PID 15"

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
	len = strlen(data) + 1;

	//Copiamos en la dirección de memoria que nos devolvió el mapeo, lo que tenemos en data, y con len le indicamos el largo a copiar
	memcpy(addr, data, len);
    printf("PID %d: Escribio en memoria compartida: \n", pid);

	// Espera 20 segundos a que alguien lea la memoria compartida.
	sleep(20);

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

    printf("PID %d: Termina: \n", pid);

	return 0;
}