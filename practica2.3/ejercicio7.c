#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

//EXECVP
/*int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Por favor introduzca el comando a ejecutar!\n");
		return -1;
	}

	if (execvp(argv[1], argv + 1) == -1) 
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		return -1;
	}
	
	//EL EXECVP FINALIZA LA EJECUCIÓN POR ESO NO SE MUESTRA
	printf("El comando terminó de ejecutarse.\n");


  	return 0;
}*/

//SYSTEM
int main(int argc, char **argv)
{
	if (argc < 2) 
	{
		printf("Por favor introduzca el comando a ejecutar!\n");
		return -1;
  	}

  	int i, long_cmmd = 1;
  	for (i = 1; i < argc; i++)
	{
		long_cmmd += strlen(argv[i]) + 1;
	}

	char *cmd = malloc(sizeof(char)*long_cmmd);
  	cmd = "";

  	for (i = 1; i < argc; i++)
	{
    		strcat(cmd, argv[i]);
    		strcat(cmd, " ");
  	}

  	if (system(cmd) == -1) 
	{
    		printf("ERROR %i - %s \n", errno, strerror(errno));
		return -1;
  	}

	//EL SYSTEM FINALIZA LA EJECUCIÓN POR ESO NO SE MUESTRA
  	printf("El comando terminó de ejecutarse.\n");


  	return 0;
}
