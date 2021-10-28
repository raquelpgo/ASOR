#include <sys/time.h>
#include <time.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
	struct timeval antes_tv, despues_tv;
	struct timezone antes_tz, despues_tz;
	gettimeofday(&antes_tv,&antes_tz);
	int i=0;
	while(i<1000000)
	{
		i++;
	}
	gettimeofday(&despues_tv,&despues_tz);

	long int diferencia = despues_tv.tv_usec - antes_tv.tv_usec;
	printf("Microsegundos que tarda el bucle en incrementar 1 millón de veces: %ld\n",
		diferencia);
	return 0;

}
