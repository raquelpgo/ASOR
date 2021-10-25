#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main() {
	struct utsname buf;
	uname(&buf);
	printf("%s, %s, %s, %s, %s\n", buf.sysname, buf.nodename, buf.release, 
		buf.version, buf.machine);
	return 0;	
}
