#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	char *err;
	if (setuid(0) == -1)
	{
		perror(err);
	}
	return 0;
}
