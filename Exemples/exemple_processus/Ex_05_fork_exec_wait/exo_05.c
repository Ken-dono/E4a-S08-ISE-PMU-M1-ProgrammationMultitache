#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_FILS 10

void race(int num_fils)
{
    int tour = 0;
    int n_tours = rand() % 5001 + 5000; // Nombre aléatoire de tours entre 5000 et 10000
    printf("Fils %d : %d tours à faire\n", num_fils, n_tours);
    for (int i = 0; i < n_tours; i++) {
        tour++;
    }
    printf("Fils %d : terminé les %d tours\n", num_fils, tour);
}

int main(void)
{
    pid_t pid_fils[NUM_FILS];
    int ordre_activation[NUM_FILS];

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    for (int i = 0; i < NUM_FILS; i++) {
        pid_fils[i] = fork();

        if (pid_fils[i] == -1) { // Erreur lors de la création du processus enfant
            perror("Erreur lors de la création du processus enfant.");
            exit(EXIT_FAILURE);
        } else if (pid_fils[i] == 0) { // Code exécuté par le processus enfant
            race(i);
            exit(i); // Le fils retourne son numéro d'ordre d'activation
        } else { // Code exécuté par le processus père
            continue;
        }
    }

    /* attente fin d'exécution des fils et récupération de leur numéro d'ordre d'activation */
    for (int i = 0; i < NUM_FILS; i++) {
        int status;
        waitpid(pid_fils[i], &status, 0);
        ordre_activation[WEXITSTATUS(status)] = i; // Stockage de l'ordre d'activation
    }

    /* tri du tableau d'ordre d'activation */
    for (int i = 0; i < NUM_FILS - 1; i++) {
        for (int j = i + 1; j < NUM_FILS; j++) {
            if (ordre_activation[i] > ordre_activation[j]) {
                int temp = ordre_activation[i];
                ordre_activation[i] = ordre_activation[j];
                ordre_activation[j] = temp;
            }
        }
    }

    printf("Course terminée !\n");
    printf("Classement :\n");
    for (int i = 0; i < NUM_FILS; i++) {
        printf("Fils %d : %dème\n", pid_fils[ordre_activation[i]], i + 1);
    }

    return EXIT_SUCCESS;
}
