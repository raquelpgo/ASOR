#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("Especifique la ruta del fichero!\n");
		return -1;	
	}

	mode_t m = umask(027); 
//para el usuario todos los permisos 7-7=0, para el grupo rx 7-5=2 y para otros ninguno 7-0=7

	if (open(argv[1], O_CREAT | O_TRUNC, 0777) == -1) 
	{
		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;
	}

	return 0;

}
