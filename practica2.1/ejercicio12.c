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
	time_t t;
	time(&t);
	printf("Segundos desde el Epoch: %lld\n", (long long)t);
	return 0;
}
