#include <sys/time.h>
#include <time.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() 
{
	time_t aux;
	time(&aux);
	struct tm *t = localtime(&aux);
	printf("Año: %d\n", 1900 + t->tm_year);
	return 0;
}
