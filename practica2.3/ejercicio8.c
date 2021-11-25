#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	if (argc < 2)
	{
		printf("Por favor introduzca el comando a ejecutar!\n");
		return -1;
	}

	pid_t pid = fork();

	if (pid == -1)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		return -1;
	}


	else if (pid == 0) // -> hijo
	{
		pid_t sid = setsid();
		printf("\n\nPROCESO HIJO\n\n");
		print_info();
		
		int fd = open("/tmp/daemon.out",O_CREAT | O_RDWR, 00777);
      		int fd_err = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
      		int fd_null = open("/dev/null", O_CREAT | O_RDWR, 00777);

      		dup2(fd,2);
      		dup2(fd_err, 1);
      		dup2(fd_null, 0);

		printf("\n\nFIN PROCESO HIJO\n\n");

		if (execvp(argv[1], argv + 1) == -1) 
		{
        		printf("ERROR %i - %s \n", errno, strerror(errno));
			return -1;
      		}
		
	}

	else // -> padre
	{
		sleep(10);
		printf("\n\nPROCESO PADRE\n\n");
		print_info();
		printf("\n\nFIN PROCESO PADRE\n\n");
	}


	return 0;
}
