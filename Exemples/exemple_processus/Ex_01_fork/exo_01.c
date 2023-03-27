//
// Created by buryhugo on 27/03/23.
//
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid_fils;
    int i, j, child_order = -1;

    for (i = 0; i < 5; i++) {
        pid_fils = fork();

        if (pid_fils == -1) {
            fprintf(stderr, "fork() impossible, errno = %d\n", errno);
            return 1;
        }

        if (pid_fils == 0) {
            // processus fils
            child_order = i;
            break;
        }
    }

    if (child_order != -1) {
        // processus fils
        for (j = 0; j < 5; j++) {
            fprintf(stdout, "Fils %d: PID = %ld, PPID = %ld\n", child_order, (long)getpid(), (long)getppid());
        }
        return 0;
    } else {
        // processus père
        fprintf(stdout, "Père : PID = %ld, PPID = %ld\n", (long)getpid(), (long)getppid());
        for (i = 0; i < 5; i++) {
            wait(NULL);
        }
        return 0;
    }
}
