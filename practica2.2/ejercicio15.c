#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Especifique la ruta del fichero!\n");
		return -1;
	}

	int fd;
	if ((fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
	{
		printf("ERROR %d - %s", errno, strerror(errno));
		return -1;
	}


	int leng = lseek(fd, 0, SEEK_END);
	if(lockf(fd, F_TEST, leng) != 0)
	{
		printf("Cerrojo previamente bloqueado\n");
		close(fd);
		return 0;
	}

	if(lockf(fd, F_LOCK, leng) == -1)
	{
		printf("Error creando el cerrojo!\n");
		close(fd);
		return -1;
	}

	time_t aux = time(NULL);
	struct tm *tm = localtime(&aux);
	char buf[20];
	sprintf (buf, "Hora: %d:%d\n", tm->tm_hour, tm->tm_min);
	write(fd, &buf, strlen(buf));

	sleep(30);

	lockf(fd, F_ULOCK, leng);
	close(fd);

	return 0;
	
}
