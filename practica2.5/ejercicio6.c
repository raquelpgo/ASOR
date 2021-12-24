#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Indique el puerto\n");
		return -1;
	}

	struct addrinfo hints, *res;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;


	int success = getaddrinfo("::", argv[1], &hints, &res);

	if (success != 0) {
		printf("Error %s\n", gai_strerror(success));
		return -1;
	}


	int tcp_sd = socket(res->ai_family, SOCK_STREAM, res->ai_protocol);
	if (tcp_sd == -1) {
		perror("NO SE PUDO ABRIR EL SOCKET");
		return -1;
	}


	if (bind(tcp_sd, res->ai_addr, res->ai_addrlen)) {
		perror("NO SE PUDO HACER BIND");
		close(tcp_sd);
		return -1;
	}

	freeaddrinfo(res);

	char buf[257] = "";
	struct sockaddr_storage input_addr;
	socklen_t input_len = sizeof(input_addr);

	if (-1 == listen(tcp_sd, 10)) {
		perror("Error escuchando");
		return -1;
	}

	while (1) {

		int asock = accept(sd, (struct sockaddr*)&input_addr, &input_len);
		if (asock == -1) {
			perror("Error aceptando la conexion");
			return -1;
		}

		char hostname[NI_MAXHOST];
		char port[NI_MAXSERV];
		if (getnameinfo((struct sockaddr*)&input_addr, input_len, hostname, NI_MAXHOST, port, NI_MAXSERV, 0)) {
			perror("Error");
			return -1;
		}
		printf("Connecxion desde %s : %s\n", hostname, port);

		ssize_t readsize;
		do {
			readsize = recv(asock, buf, 256*sizeof(char), 0);
					
			if (readsize == -1) {
				perror("Error");
				close(tcp_sd);
				return -1;
			}
			else if (readsize == 0) {
				printf("Client has performed a shutdown\n");
			}
			else {
				buf[readsize] = '\0';
				ssize_t writesize = send(asock, buf, (readsize + 1)*sizeof(char), 0);
				if (writesize == -1) {
					perror("Error while sending back to client");
					return -1;
				}
			}

		} while (readsize > 0);

		close(asock);
	}

	close(tcp_sd);
	return 0;
}
