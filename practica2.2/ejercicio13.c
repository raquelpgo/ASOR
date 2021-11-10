#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
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
    		printf("ERROR %d - %s\n", errno, strerror(errno));
		return -1;	
	}
	
	dup2(fd,1);
	printf("prueba pruebita prueba\n");

  
	dup2(fd,2);
	if (setuid(0) == -1){
		 printf("ERROR %d - %s\n", errno, strerror(errno));
	}

	

  return 1;
}
