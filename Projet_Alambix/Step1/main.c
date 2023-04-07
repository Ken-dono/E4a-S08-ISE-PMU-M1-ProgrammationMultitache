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
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>

#define ALAMBIX_BARTENDER_MQ_NAME "/alambix_bartender_mq"
#define ALAMBIX_BARTENDER_MQ_MSG_MAX (10)
#define ALAMBIX_BARTENDER_MQ_MSG_SIZE (48)

pthread_t alambix_client0_thread;
pthread_t alambix_client1_thread;
pthread_t alambix_waiter_thread;
pthread_t alambix_bartender_thread;

pthread_mutex_t alambix_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t alambix_semaphore;


// configuration de la file de message
mqd_t alambix_bartender_mq;
struct mq_attr alambix_bartender_mq_attr;

void * alambix_client_thread_fct(void * arg);
void * alambix_waiter_thread_fct(void * arg);
void * alambix_bartender_thread_fct(void * arg);

void * alambix_client_thread_fct(void * arg)
{
    char * drink;
    while ((drink = alambix_choose_drink()) != NULL)
    {
        pthread_mutex_lock(&alambix_mutex);
        alambix_order_drink(drink);
        pthread_mutex_unlock(&alambix_mutex);
    }
    sem_post(&alambix_semaphore);
}

void * alambix_waiter_thread_fct(void * arg)
{
    sem_wait(&alambix_semaphore);
    sem_wait(&alambix_semaphore);
    alambix_take_order();

    // transmit the order to the bartender
    char * ordered_drink;
    while ((ordered_drink = alambix_get_ordered_drink()) != NULL)
    {
        // send the ordered drink using the bartender message queue
        if (mq_send(alambix_bartender_mq, ordered_drink, strlen(ordered_drink), 0) == -1) {
            perror("mq_send()");
            exit(EXIT_FAILURE);
        }
    }
}

void * alambix_bartender_thread_fct(void * arg)
{
    // receive the order from the waiter
    do
    {
        // receive the drink order using the bartender message queue
    }
    while (alambix_has_ordered_drink());
}

void alambix_init()
{
    // TODO: Insert initialization code here.
    sem_init(&alambix_semaphore, 0, 0);

    alambix_bartender_mq_attr.mq_maxmsg = ALAMBIX_BARTENDER_MQ_MSG_MAX;
    alambix_bartender_mq_attr.mq_msgsize = ALAMBIX_BARTENDER_MQ_MSG_SIZE;

    // création/ouverture de la file de message
    if ((alambix_bartender_mq = mq_open(ALAMBIX_BARTENDER_MQ_NAME, O_RDWR | O_CREAT | O_EXCL, 0644, &alambix_bartender_mq_attr)) == -1) {
        mq_unlink(ALAMBIX_BARTENDER_MQ);
        alambix_bartender_mq = mq_open(ALAMBIX_BARTENDER_MQ_NAME, O_RDWR | O_CREAT, 0644, &alambix_bartender_mq_attr);
    }
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

    //Thread alambix_waiter_thread
    if (pthread_create(&alambix_waiter_thread, NULL, alambix_waiter_thread_fct, NULL) != 0) {
        fprintf(stderr, "erreur pthread_create\n");
        exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_waiter_thread);

    //Thread alambix_bartender_thread
//    if (pthread_create(&alambix_bartender_thread, NULL, alambix_bartender_thread_fct, NULL) != 0) {
//        fprintf(stderr, "erreur pthread_create\n");
//        exit(EXIT_FAILURE);
//    }
//    pthread_detach(alambix_bartender_thread);
}

int main(int argc, char * argv[])
{
    alambix_open();

    // TODO: Insert cleanup code here.
    mq_unlink(ALAMBIX_BARTENDER_MQ);
    mq_close(alambix_bartender_mq);
    pthread_mutex_destroy(&alambix_mutex);
    sem_destroy(&alambix_semaphore);
    return alambix_close();
}