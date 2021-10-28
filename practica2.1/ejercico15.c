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
	
  char *s, *format = "%A, %d de %B de %Y, %R";
	size_t m = 100:
	strftime(s, m, format,t);
	
	printf("%s\n",s);
	return 0;
}
