//
// Created by buryhugo on 13/04/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

volatile int running = 1;

int main()
{
    pid_t pid_fils;
    pid_fils = fork();

    if (pid_fils == -1) {
        fprintf(stderr, "fork() impossible, errno = %d\n", errno);
        exit(EXIT_FAILURE);
    } else if (pid_fils == 0) {
        // child process
        while(1);
    } else {
        // parent process

        // main loop
        while(running)
        {
            printf("Menu:\n");
            printf("Press 's' to pause the calculation.\n");
            printf("Press 'r' to resume the calculation.\n");
            printf("Press 'q' to exit the program.\n");

            char input;
            scanf(" %c", &input);

            switch(input)
            {
                case 's':
                    printf("SIGTSTP received. Pausing calculation.\n");
                    kill(pid_fils, SIGSTOP);
                    break;
                case 'r':
                    printf("SIGCONT received. Resuming calculation.\n");
                    kill(pid_fils, SIGCONT);
                    break;
                case 'q':
                    printf("SIGINT received. Exiting.\n");
                    kill(pid_fils, SIGINT);
                    running = 0;
                    break;
                default:
                    printf("Unknown command.\n");
                    break;
            }
        }
    }
    return EXIT_SUCCESS;
}
