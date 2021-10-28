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
	
	char s[100], *format = "%A, %d de %B de %Y, %R";
	strftime(s, 100, format,t);
	
	printf("%s\n",s);
	return 0;
}
