#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char* argv[])
{
	if (argc < 2) {
		perror("Especifique la ruta del fichero!");
		return -1;	
	}

	if (open(argv[1], O_CREAT | O_TRUNC, 00645) == -1) 
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;
	}

	return 0;

}
