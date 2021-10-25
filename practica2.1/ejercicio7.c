#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
	printf("Número máximo de enlaces: %ld\nTamaño máximo de ruta: %ld\nTamaño máximo de nombre: %ld\n", 
		pathconf("/",_PC_LINK_MAX), pathconf("/",_PC_PATH_MAX), pathconf("/",_PC_NAME_MAX));
	return 0;
}
