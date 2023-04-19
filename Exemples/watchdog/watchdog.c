#include "watchdog.h"

#include <malloc.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

struct watchdog_t
{
	timer_t timer;
	unsigned int  delay;
	watchdog_callback callback;
};

static void watchdog_function(union sigval val)
{
	
}

watchdog_t * watchdog_create(unsigned int delay, watchdog_callback callback)
{
	//todo	
}

void watchdog_start(watchdog_t * watchdog)
{
	//todo
}

void watchdog_cancel(watchdog_t * watchdog)
{
	//todo
}

void watchdog_destroy(watchdog_t * watchdog)
{
	//todo	
}

