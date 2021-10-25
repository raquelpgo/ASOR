#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main() 
{
	printf("UID Real: %d\nUID Efectivo: %d\n",getuid(), geteuid());
	return 0;
}
