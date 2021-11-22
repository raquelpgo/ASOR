#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char* argv[])
{
	int policy = sched_getscheduler(0);
	int prio = getpriority(PRIO_PROCESS, 0);
	int prio_max = sched_get_priority_max(policy);
	int prio_min = sched_get_priority_min(policy);
	char* policy_char = "SCHED_OTHER";
	if (policy == -1)
	{
		printf("ERROR %i - %s \n", errno, strerror(errno));
		return -1;
	}
	if (policy == 1){policy_char = "SCHED_FIFO";}	
	else if (policy == 2){policy_char = "SCHED_RR";}
	else if (policy == 3){policy_char = "SCHED_BATCH";}
	else if (policy == 5){policy_char = "SCHED_IDLE";}

	printf("Protocolo planificación: %s\n", policy_char);
	printf("Prioridad Actual: %i\n", prio);
	printf("Prioridad Máxima: %i\n", prio_max);
	printf("Prioridad mínima: %i\n", prio_min);

	return 0;
}
