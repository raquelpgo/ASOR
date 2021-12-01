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
		
		char buf;
		while (read(pipefd[0], &buf, 1) > 0){}
		close(pipefd[0]);


		if (system(&buf) == -1)
		{
			printf("ERROR %i - %s\n", errno, strerror(errno));
			return -1;	
		}

	}

	else 
	{

		close(pipefd[0]);
		dup2(pipefd[1], 1);

		int long_cmd = 3 + strlen(argv[3]) + strlen(argv[4]);
		char *cmd = malloc(sizeof(char)*long_cmd);
  		cmd = "";

		strcat(cmd, argv[3]);
    		strcat(cmd, " ");
		strcat(cmd, argv[4]);
	
		write(pipefd[1], cmd, long_cmd);

		close(pipefd[1]);
		
		int long_cmd2 = 3 + strlen(argv[1]) + strlen(argv[2]);
		char *cmd2 = malloc(sizeof(char)*long_cmd2);
  		cmd2 = "";

		strcat(cmd2, argv[1]);
    		strcat(cmd2, " ");
		strcat(cmd2, argv[2]);

		if (system(cmd2) == -1)
		{
			printf("ERROR %i - %s\n", errno, strerror(errno));
			return -1;	
		}

	}

	return 0;

}
