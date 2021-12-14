#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main (int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Introduzca el host y el puerto como argumentos!\n");
		return -1;
	}

	struct addrinfo hints, *res;

	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_DGRAM;

	int success = getaddrinfo(argv[1], argv[2], &hints, &res);

	if(success != 0)
	{
		printf("ERROR %i - %s \n", success, gai_strerror(success));
		return -1;
	}

	int udp_sd = socket(res->ai_family, SOCK_DGRAM, res->ai_protocol);

	if (udp_sd == -1) {
		printf("No se pudo abrir el socket!\n");
		return -1;
	}


	if (bind(udp_sd, res->ai_addr, res->ai_addrlen)) {
		perror("No se pudo hacer el bind!\n");
		return -1;
	}

	freeaddrinfo(res);

	char cmmd[2] = "";
	struct sockaddr_storage input_addr;
	socklen_t input_len = sizeof(input_addr);

	while (cmmd[0] != 'q') 
	{
		int readsz = recvfrom(udp_sd, &cmmd, 2, 0,(struct sockaddr *) &input_addr, &input_len);

		if (readsz == -1)
 		{
			printf("Error en la lectura!\n");
			close(udp_sd);
			return -1;
		}

		else if (readsz == 0) {
			printf("El cliente ha apagado\n");
			cmmd[0] = 'q';
		}

		else 
		{
			char host[NI_MAXHOST];
			char port[NI_MAXSERV];

			if (getnameinfo((struct sockaddr *)&input_addr, input_len, host, NI_MAXHOST, port, NI_MAXSERV, 0)) 
			{
				printf("ERROR %i - %s \n", success, gai_strerror(success));
				return -1;
			}

			printf("%i bytes de %s:%s\n", readsz, host, port);

			if (cmmd[0] == 'd') 
			{
				time_t timet;
				struct tm *localtimet;
				char buffer[256];
				timet =  time(NULL);
				localtimet = localtime(&timet);
				strftime(buffer,256,"%Y-%m-%d", localtimet);
	
				int writesize = sendto(udp_sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);

				if (writesize == -1) 
				{
					printf("No se ha podido comunicar con el cliente\n");
					return -1;
				}
			}

			else if(cmmd[0] == 't') 
			{
				time_t timet;
				struct tm *localtimet;
				char buffer[256];
				timet =  time(NULL);
				localtimet = localtime(&timet);
				strftime(buffer,256,"%r", localtimet);
	
				int writesize = sendto(udp_sd, buffer, strlen(buffer), 0, (struct sockaddr *)&input_addr, input_len);

				if (writesize == -1) 
				{
					printf("No se ha podido comunicar con el cliente\n");
					return -1;
				}
			}

			else if (cmmd[0] == 'q')
			{			
				printf("Cerrando\n");
			}
			
			else
			{	
				printf("Los comandos soportados son: 'd', 't' y 'q'\n");
			}
		}
	}
	
	close(udp_sd);
	return 0;

}
