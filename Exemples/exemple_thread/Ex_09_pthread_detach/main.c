#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void * thread_1_fct(void * arg);
void * thread_2_fct(void * arg);
int erreur_1;
int erreur_2;

int main(void)
{
	pthread_t thread_1;
	pthread_t thread_2;

	fprintf(stdout, "Process PID %d\n", getpid());

	if (pthread_create(&thread_1, NULL, thread_1_fct, NULL) != 0) {
		fprintf(stderr, "erreur pthread_create\n");
		exit(EXIT_FAILURE);
	}
	pthread_detach(thread_1);

	if (pthread_create(&thread_2, NULL, thread_2_fct, (void *)42) != 0) {
		fprintf(stderr, "erreur pthread_create\n");
		exit(EXIT_FAILURE);
	}
	//pthread_detach(thread_2);

	fprintf(stdout, "Thread main attend Thread 1 (?)\n");
	erreur_1 = pthread_join(thread_1, NULL);
    printf("Erreur 1 : %d\n", erreur_1);

    fprintf(stdout, "Thread main attend Thread 2 (?)\n");
    erreur_2 = pthread_join(thread_2, NULL);
    printf("Erreur 2 : %d\n", erreur_2);

	fprintf(stdout, "Thread main sortie\n");
	// return EXIT_SUCCESS;
	pthread_exit(EXIT_SUCCESS);
}

void * thread_1_fct(void * arg)
{
	for (int i = 0; i < 3; i++) {
		fprintf(stdout, "Thread 1 (argument = %ld)\n", (long)arg);
		sleep(4);
	}
	return NULL;
}

void * thread_2_fct(void * arg)
{
	for (int i = 0; i < 3; i++) {
		fprintf(stdout, "Thread 2 (argument = %ld)\n", (long)arg);
		sleep(4);
	}
	return NULL;
}


