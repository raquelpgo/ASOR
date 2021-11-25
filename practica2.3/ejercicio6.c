#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

void print_info()
{
	pid_t pid = getpid();
	pid_t ppid = getppid();
	pid_t pgid = getpgid(0);
	pid_t sid = getsid(0);
	char* nom_dir = (char*) malloc(150);
	if (getcwd(nom_dir, 150) == NULL)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		exit(-1);
	}

	struct rlimit rlim;

	if (getrlimit(RLIMIT_NOFILE, &rlim) == -1)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		exit(-1);
	}
	int n_files =  rlim.rlim_max;

	printf("PID: %i\nPPID: %i\nPGID: %i\nSID: %i\nNombre dir: %s\nNº max. ficheros: %i\n"
		, pid, ppid, pgid, sid, nom_dir, n_files);

}

int main(int argc, char* argv[])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		return -1;
	}

	else if (pid == 1) // -> padre
	{
		printf("PROCESO PADRE");
		print_info();
	}

	else //if pid == 0 -> hijo
	{
		pid_t sid = setsid();
		chdir("/tmp");
		printf("PROCESO HIJO");
		print_info();
	}


	return 0;
}
