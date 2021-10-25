#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	if (setuid(0) == -1)
	{
		printf("%s\n", strerror(errno));
	}
	return 0;
}
