#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Especifique la ruta del fichero!\n");
		return -1;
	}

	struct stat buf;

	if (stat(argv[1], &buf) != 0)
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;	
	}


	if(!S_ISREG(buf.st_mode))
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;
	}

	char* rig = malloc(sizeof(char) * (5 + strlen(argv[1])));
	char* sim = malloc(sizeof(char) * (4 + strlen(argv[1])));
	strcpy(rig, argv[1]);
	strcpy(sim, argv[1]);
	strcat(rig, ".hard");
	strcat(sim, ".sym") ;

	if (link(argv[1], rig) != 0)
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;
	}

	if (symlink(argv[1], sim) != 0)
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;
	}
	return 0;
}
