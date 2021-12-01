#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		printf("Para ejecutar el programa aseguresé de seguir la estructura comando1");
		printf(" argument1 comando2 argumento2\n");
		return -1;	
	}

	int pipefd[2];
	if (pipe(pipefd) != 0)
	{
		printf("ERROR %i - %s\n", errno, strerror(errno));
		return -1;	
	}

	pid_t pid;
	pid = fork();

	if (pid == -1)
	{
		printf("ERROR %i - %s\n", errno, strerror(errno));
		return -1;	
	}

	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0],0);
		close(pipefd[0]);

		if (execlp(argv[3], argv[3], argv[4], NULL) == -1)
		{
			printf("ERROR %i - %s\n", errno, strerror(errno));
			return -1;	
		}
	}

	else 
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		
		if (execlp(argv[1], argv[1], argv[2], NULL) == -1)
		{
			printf("ERROR %i - %s\n", errno, strerror(errno));
			return -1;	
		}
	}
	
	return 0;
}
