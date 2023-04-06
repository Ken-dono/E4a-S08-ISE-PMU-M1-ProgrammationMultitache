#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_ITERATIONS 100000

int compteur = 0;
pthread_mutex_t mutex_compteur;

void* thread_inc() {
    int i;
    for (i = 0; i < NB_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex_compteur);
        compteur++;
        pthread_mutex_unlock(&mutex_compteur);
    }
    return NULL;
}

int main() {
    pthread_t thread_1;
    pthread_t thread_2;

    if (pthread_mutex_init(&mutex_compteur, NULL) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation du mutex.\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread_1, NULL, thread_inc, NULL) != 0) {
        fprintf(stderr, "erreur pthread_create\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread_2, NULL, thread_inc, NULL) != 0) {
        fprintf(stderr, "erreur pthread_create\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    pthread_mutex_destroy(&mutex_compteur);

    printf("Compteur final : %d\n", compteur);

    return EXIT_SUCCESS;
}
