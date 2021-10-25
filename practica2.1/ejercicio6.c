#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main() {
	printf("Longitud máxima argumentos: %ld\nNúmero máximo de hijos: %ld\nNúmero máximo de ficheros %ld\n", sysconf(_SC_ARG_MAX), sysconf(_SC_CHILD_MAX), sysconf(_SC_OPEN_MAX));
	return 0;

}
