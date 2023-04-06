#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_lecture_fct();
void *thread_affichage_fct();
char lettre_a_trouver;
char lettre_condition_sortie = 'q';

int main(void)
{
    pthread_t thread_lecture;
    pthread_t thread_affichage;

    if (pthread_create(&thread_lecture, NULL, thread_lecture_fct, &lettre_a_trouver) != 0) {
        fprintf(stderr, "Erreur pthread_create pour le thread lecture\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread_affichage, NULL, thread_affichage_fct, &lettre_a_trouver) != 0) {
        fprintf(stderr, "Erreur pthread_create pour le thread affichage\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_lecture, NULL);
    pthread_join(thread_affichage, NULL);

    printf("Threads terminés\n");

    return EXIT_SUCCESS;
}

void *thread_lecture_fct()
{
    while (lettre_a_trouver != lettre_condition_sortie) {
        scanf(" %c", &lettre_a_trouver);
        printf("Lettre lue : %c\n", lettre_a_trouver);
    }
    printf("Arrêt du thread de lecture\n");
    return NULL;
}

void *thread_affichage_fct()
{
    while (lettre_a_trouver != lettre_condition_sortie) {
        if (lettre_a_trouver != 0) {
            printf("Lettre affichée : %c\n", lettre_a_trouver);
            lettre_a_trouver = 0;
        }
        sleep(1);
    }
    printf("Arrêt du thread d'affichage\n");
    return NULL;
}
