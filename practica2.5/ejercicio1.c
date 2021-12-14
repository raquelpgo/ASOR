#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Introduzca el host como argumetno!\n");
		return -1;
	}

	struct addrinfo hints, *res, *aux;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_flags = AI_PASSIVE;

	int success = getaddrinfo(argv[1], NULL, &hints, &res);

	if(success != 0)
	{
		printf("ERROR %i - %s \n", success, gai_strerror(success));
		return -1;
	}

	aux = res;

	while (aux != NULL)
	{
		char hbuf[NI_MAXHOST];
		success =  getnameinfo(aux->ai_addr, aux->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0, NI_NUMERICHOST);

		if(success != 0)
		{
			printf("ERROR %i - %s \n", success, gai_strerror(success));
			return -1;
		}

		printf("%s\t%i\t%i\n", hbuf, aux->ai_family, aux->ai_socktype);
		aux = aux->ai_next;
	}
	
	freeaddrinfo(res);
	return 0;

}
