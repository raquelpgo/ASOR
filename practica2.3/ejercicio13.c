#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int int_count = 0;
volatile int tstp_count = 0;

void manejador (int sig){
	if (sig == SIGINT)
	{
		int_count++;
	}
 	
	if (sig == SIGTSTP)
	{
		tstp_count++;
	}
}

int main(int argc, char* argv[])
{

	struct sigaction handler;

	if (sigaction(SIGINT, NULL, &handler) == -1)
	{
		printf("No se ha podido conseguir el manejador de SIGNINT\n");
		return -1;
	}

  	handler.sa_handler = manejador;

	if (sigaction(SIGINT, &handler, NULL) == -1)
	{
		printf("No se ha podido modificar el manejador de SIGNINT\n");
		return -1;
	}

	if (sigaction(SIGTSTP, NULL, &handler) == -1)
	{
		printf("No se ha podido conseguir el manejador de SIGTSTP\n");
		return -1;
	}
  
 
  	handler.sa_handler = manejador;

	if (sigaction(SIGTSTP, &handler, NULL) == -1)
	{
		printf("No se ha podido modificar el manejador de SIGTSTP\n");
		return -1;
	}

	sigset_t masc;
	sigemptyset(&masc);

	while (int_count + tstp_count < 10)
	{
		sigsuspend(&masc);
	}

	printf("Número de SIGINT capturados: %i\n", int_count);
	printf("Número de SIGTSTP capturados: %i\n", tstp_count);


  return 0;
}
