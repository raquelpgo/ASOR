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
#include <arpa/inet.h>
#include <netinet/in.h>

int main (int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Introduzca la dirección del servidor, el puerto y el comando como argumentos!\n");
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


	if (sendto(udp_sd, argv[3], strlen(argv[3]) + 1, 0, res->ai_addr, res->ai_addrlen) == -1) {
		perror("Error enviando al servidor!\n");
		return -1;
	}

	char buffer[256];
	int  readsz = recvfrom(udp_sd, buffer, 255, 0, res->ai_addr, &res->ai_addrlen);

	if (readsz == -1)
 	{
		printf("Error en la lectura!\n");
		close(udp_sd);
		return -1;
	}

	buffer[readsz] = '\0';
	printf("%s\n", buffer);

	freeaddrinfo(res);

	printf("Comando %s enviado a %s : %s\n", argv[3], argv[1], argv[2]);
	
	close(udp_sd);
	return 0;

}
