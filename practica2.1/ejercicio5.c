#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main() {
	struct utsname buf;
	if (uname(&buf) != 0)
	{
		printf("ERROR %d - %s", errno, strerror(errno));
		return -1;
	}
	printf("%s, %s, %s, %s, %s\n", buf.sysname, buf.nodename, buf.release, 
		buf.version, buf.machine);
	return 0;	
}
