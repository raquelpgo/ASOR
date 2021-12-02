#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	int pipe_h_fd[2], h_pipe_fd[2];
	if (pipe(pipe_h_fd) != 0 || pipe(h_pipe_fd) != 0)
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
		close(pipe_h_fd[1]);
		close(h_pipe_fd[0]);

		int i;
		char flag_a_enviar = 'l';
		char buf[256];
		for (i = 0; i < 10; i++) 
		{
			char buf[256];
			int long_m = read(pipe_h_fd[0], buf, 255);

			buf[long_m] = '\0';

			printf("Mensaje recibido por el hijo: %s", buf);
			sleep(1);

			if(i == 9)
			{
				flag_a_enviar = 'q';
			}

			write(h_pipe_fd[1], &flag_a_enviar, 1);
		}

		close(pipe_h_fd[0]);
		close(h_pipe_fd[1]);
		return 0;	
	}

	else 
	{

		close(pipe_h_fd[0]);
		close(h_pipe_fd[1]);

		char flag_recibido = 'l';
		char msg_usuario[256];

		while(flag_recibido != 'q')
		{
			printf("El padre envia un mensaje:\n");
			int long_m = read(0, msg_usuario, 255);
			msg_usuario[long_m] = '\0';
			write(pipe_h_fd[1], msg_usuario, long_m + 1);

			while (flag_recibido != 'l' && flag_recibido != 'q') 
			{
				read(h_pipe_fd[0], &flag_recibido, 1);
			}

		}

		close(pipe_h_fd[1]);
		close(h_pipe_fd[0]);	
		return 0;		
	}

	return 0;

}
