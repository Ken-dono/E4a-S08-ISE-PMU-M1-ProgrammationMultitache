#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

#include <errno.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <signal.h>

static int run = 1;

void signal_sigint_handler(int )
{
	fprintf(stdout, "\nSIGINT intercepté (PID %d)\n", getpid());
	run = 0;
}

void signal_sigchld_handler(int )
{
	fprintf(stdout, "SIGCHLD intercepté (PID %d)\n", getpid());
	wait(NULL);
}

int main(void)
{
	struct sigaction action;

	/* interception du Ctrl+C pour sortie propre */
	action.sa_handler = signal_sigint_handler;
	sigemptyset(&(action.sa_mask));
	action.sa_flags = SA_RESTART;

	sigaction(SIGINT, &action, NULL);

	/* interception de SIGCHLD pour suppression de zombis à tout moment */
	action.sa_handler = signal_sigchld_handler;
	sigemptyset(&(action.sa_mask));
	action.sa_flags = SA_RESTART | SA_NOCLDSTOP; // SA_NOCLDSTOP : seulement quand un fils se termine (pas quand il est juste arrêté)

	sigaction(SIGCHLD, &action, NULL);


	pid_t pid_fils;

	pid_fils = fork();

	if (pid_fils == -1) {
		fprintf(stderr, "fork() impossible, errno = %d\n", errno);
		exit(EXIT_FAILURE);
	}

	if (pid_fils == 0) {
		/* processus fils */
		fprintf(stdout, "Fils : PID = %ld, PPID = %ld\n", (long)getpid(), (long)getppid());

		/* lancement d'un programme dans le processus fils */
		char * argv[3];

		argv[0] = "xclock";
		argv[1] = "-digital";
		argv[2] = (char *) NULL;

		fprintf(stdout, "Fils : lancement de %s %s\n", argv[0], argv[1]);
		fflush(stdout);

		execv("/usr/bin/xclock", argv);

		fprintf(stderr, "erreur exec\n");
		fflush(stderr);
		exit(EXIT_FAILURE);

	} else {
		/* processus père */
		fprintf(stdout, "Père : PID = %ld, PPID = %ld, PID fils = %ld\n", (long)getpid(), (long)getppid(), (long)pid_fils);
		
		/* exécution du traitement */
		while (run) {
			fprintf(stdout, "Père : exec.\n");
			sleep(1);
		}

		fprintf(stdout, "Père : exit\n");
		exit(EXIT_SUCCESS);
	}
}


