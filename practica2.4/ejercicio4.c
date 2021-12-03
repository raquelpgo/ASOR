#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Por favor pase un argumetno para escribir en la tuberia!\n");
		return -1;
	}

	int fd = open("./pipe", O_WRONLY);
	if (fd == -1)
	{
		printf("ERROR %i - %s\n", errno, strerror(errno));
		close(fd);
		return -1;
	}

	if (write(fd, argv[1], strlen(argv[1])) == -1)
	{
		printf("ERROR %i - %s\n", errno, strerror(errno));
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}
