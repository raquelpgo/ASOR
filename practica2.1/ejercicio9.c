#include <pwd.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main() 
{
	printf("UID Real: %d\nUID Efectivo: %d\n",getuid(), geteuid());

	struct passwd * psw = getpwuid(getuid());
	printf("Nombre usuario: %s\nDirectorio Home: %s\nDescripción del usuario: %s\n",
		psw->pw_name, psw->pw_dir, psw->pw_gecos);
	return 0;
}
