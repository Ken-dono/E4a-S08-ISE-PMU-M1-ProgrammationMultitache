#ifndef _WATCHDOG_H
#define _WATCHDOG_H

typedef struct watchdog_t watchdog_t;

typedef void (* watchdog_callback)(watchdog_t * watchdog);


watchdog_t * watchdog_create(unsigned int delay, watchdog_callback callback);

void watchdog_start(watchdog_t * watchdog);

void watchdog_cancel(watchdog_t * watchdog);

void watchdog_destroy(watchdog_t * watchdog);

#endif /* _WATCHDOG_H */

