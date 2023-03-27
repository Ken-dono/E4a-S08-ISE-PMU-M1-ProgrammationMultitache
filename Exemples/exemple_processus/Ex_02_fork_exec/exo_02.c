//
// Created by buryhugo on 27/03/23.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Launch baobab using execl
    child_pid = fork();
    if (child_pid == 0) {
        printf("Launching baobab using execl...\n");
        execl("/usr/bin/baobab", "baobab", (char *)NULL);
    } else {
        wait(NULL);
    }

    // Launch baobab using execv
    child_pid = fork();
    if (child_pid == 0) {
        printf("Launching baobab using execv...\n");
        char *argv[] = {"baobab", NULL};
        execv("/usr/bin/baobab", argv);
    }

    // Launch baobab using execvp
    child_pid = fork();
    if (child_pid == 0) {
        printf("Launching baobab using execvp...\n");
        char *argv[] = {"baobab", NULL};
        execvp("baobab", argv);
    } else {
        wait(NULL);
    }

    return 0;
}
