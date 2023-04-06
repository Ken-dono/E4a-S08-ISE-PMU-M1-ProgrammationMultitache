//
// Created by buryhugo on 27/03/23.
//
//

// \file main.c
//
// \brief Source code example for Alambix programming.
//

#include "alambix.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_t alambix_client0_thread;
pthread_t alambix_client1_thread;
pthread_mutex_t alambix_mutex = PTHREAD_MUTEX_INITIALIZER;

void * alambix_client_thread_fct(void * arg);

void * alambix_client_thread_fct(void * arg)
{
    char * drink;

    while ((drink = alambix_choose_drink()) != NULL)
    {
        pthread_mutex_lock(&alambix_mutex);
        alambix_order_drink(drink);
        pthread_mutex_unlock(&alambix_mutex);
    }
}

void alambix_init()
{
    // TODO: Insert initialization code here.
}

void alambix_help()
{
    char* help_path = alambix_help_html();
    pid_t pid_fils = fork(); // Création d'un nouveau processus enfant

    if (pid_fils == -1) { // Erreur lors de la création du processus enfant
        perror("Erreur lors de la création du processus enfant.");
        exit(EXIT_FAILURE);
    } else if (pid_fils == 0) { // Code exécuté par le processus enfant
        execlp("firefox", "firefox", help_path, NULL); // Lancement de Firefox avec le chemin de la documentation d'aide en argument
        exit(EXIT_SUCCESS);
    }
}

void alambix_start() {
    //Thread alambix_client0_thread
    if (pthread_create(&alambix_client0_thread, NULL, alambix_client_thread_fct, NULL) != 0) {
        fprintf(stderr, "erreur pthread_create\n");
        exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_client0_thread);
    //Thread alambix_client1_thread
    if (pthread_create(&alambix_client1_thread, NULL, alambix_client_thread_fct, NULL) != 0) {
        fprintf(stderr, "erreur pthread_create\n");
        exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_client1_thread);
}

int main(int argc, char * argv[])
{
    alambix_open();
    alambix_help(); // Launch the Alambix help documentation in a browser.
    // TODO: Insert cleanup code here.

    int ret = alambix_close();
    pthread_mutex_destroy(&alambix_mutex);
    return ret;
}
