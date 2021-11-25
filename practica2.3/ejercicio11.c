#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main(int argc, char **argv)
{

	sigset_t masc;

	sigemptyset(&masc);
	sigaddset(&masc, SIGINT);
	sigaddset(&masc, SIGTSTP);

	if (sigprocmask(SIG_BLOCK, &masc, NULL) == -1)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		exit(-1);
	}

	char *sleep_secs = getenv("SLEEP_SECS");

	if (sleep_secs == NULL)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		exit(-1);
	}
	int secs = atoi(sleep_secs);
	sleep(secs);

	sigset_t pending;
	if (sigpending(&pending) == -1) 
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		exit(-1);
	}

	if (sigismember(&pending, SIGINT) == 1) 
	{
		printf("SIGINT\n");
		sigdelset(&masc, SIGINT);
	} 

	if (sigismember(&pending, SIGTSTP) == 1) 
	{
		printf("SIGTSTP\n");
		sigdelset(&masc, SIGTSTP);
	} 
	sigprocmask(SIG_UNBLOCK, &masc, NULL);

	return 0;
}
