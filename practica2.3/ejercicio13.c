#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

volatile int stop = 0;

void manejador(int sig)
{
	if (sig == SIGUSR1)
	{
		stop = 1;
	}
}

int main(int argc, char* argv[]) 
{
	if (argc != 2) 
	{
		printf("Por favor introduzca los segundos!\n");
    		return -1;
  	}

	sigset_t mask;
  	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);

  	if (sigprocmask(SIG_UNBLOCK, &mask, NULL))
	{
		printf("No se pudo bloquear SIGUSR1!\n");
		return -1;
	}

  	struct sigaction handler;

  	if (sigaction(SIGUSR1, NULL, &handler) == -1) 
	{
		printf("No se ha podido conseguir el manejador de SIGUSR1!\n");
		return -1;
	} 

  	handler.sa_handler = manejador;
  	if (sigaction(SIGUSR1, &handler, NULL) == -1) 
	{
		printf("No se ha podido modificar el manejador de SIGUSR1!\n");
		return -1;
	}


	sleep(atoi(argv[1]));

	if (stop == 0)
	{
	 	printf("Oh no! programa borrado\n");
	    	unlink(argv[0]);
	}
 
	else
	{
		printf("Has tenido suerte!\n");
	}

  return 0;
}
