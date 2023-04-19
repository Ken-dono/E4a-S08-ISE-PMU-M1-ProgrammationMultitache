#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "watchdog.h"

void notify_function(watchdog_t * watchdog)
{
	time_t current_time;

	time(&current_time); 
	fprintf(stdout, "watchdog expire à %s\n", ctime(&current_time));
}

int main(void)
{
	time_t current_time;

	watchdog_t * my_watchdog = watchdog_create(4, notify_function);

	time(&current_time); 
	fprintf(stdout, "lancement watchdog à : %s\n", ctime(&current_time));

	watchdog_start(my_watchdog);

	for (int i = 0; i < 6; i++) {
		fprintf(stdout, "main travaille...\n");
		sleep(1);
	}

	watchdog_destroy(my_watchdog);

	fprintf(stdout, "main quitte\n");
	return 0;
}

