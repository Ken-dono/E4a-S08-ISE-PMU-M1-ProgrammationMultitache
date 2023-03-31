#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_FILS 10

void race()
{
    int tour = 0;
    srand((long)getpid()); // Initialisation du générateur de nombres aléatoires
    int n_tours = rand() % 5001 + 5000; // Nombre aléatoire de tours entre 5000 et 10000

    printf("Fils %ld : %d tours à faire\n", (long)getpid(), n_tours);

    for (int i = 0; i < n_tours; i++) {
        tour++;
    }
    printf("Fils %ld : terminé les %d tours\n", (long)getpid(), tour);
}

int main(void)
{
    pid_t pid_fils[NUM_FILS];
    int classement[NUM_FILS];


    for (int i = 0; i < NUM_FILS; i++) {
        pid_fils[i] = fork();
        if (pid_fils[i] == -1) { // Erreur lors de la création du processus enfant
            perror("Erreur lors de la création du processus enfant.");
            exit(EXIT_FAILURE);
        } else if (pid_fils[i] == 0) { // Code exécuté par le processus enfant
            race();
            exit(i); // Le fils retourne son numéro d'ordre d'activation
        } else { // Code exécuté par le processus père
            continue;
        }
    }

    /* attente fin d'exécution des fils et récupération de leur numéro d'ordre d'activation */
    for (int i = 0; i < NUM_FILS; i++) {
        int status;
        classement[i] = (long)wait(&status); // Stockage de l'ordre d'arrivée
    }

    printf("Course terminée !\n");
    printf("Classement :\n");
    for (int i = 0; i < NUM_FILS; i++) {
        printf("Fils %d : %dème\n", classement[i], i + 1);
    }

    return EXIT_SUCCESS;
}
