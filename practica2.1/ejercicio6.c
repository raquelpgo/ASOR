#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main() {
	printf("Longitud máxima argumentos: %ld\n Número máximo de hijos: %ld\n Número máximo de ficheros %ld\n", sysconf(ARG_MAX), sysconf(CHILD_MAX), sysconf(OPEN_MAX));
	return 0;

}
