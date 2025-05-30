#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

sem_t clientes, barbeiro, mutex;
int cadeiras_livres = 5;

void* cliente(void* arg) {
    sem_wait(&mutex);
    if (cadeiras_livres > 0) {
        cadeiras_livres--;
        sem_post(&clientes);
        sem_post(&mutex);
        sem_wait(&barbeiro);
        printf("Cliente sendo atendido\n");
    } else {
        sem_post(&mutex);
        printf("Cliente foi embora (sem cadeira)\n");
    }
    return NULL;
}

void* barbeiro_func(void* arg) {
    while (1) {
        sem_wait(&clientes);
        sem_wait(&mutex);
        cadeiras_livres++;
        sem_post(&barbeiro);
        sem_post(&mutex);
        printf("Barbeiro cortando cabelo\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t b, c[10];
    sem_init(&clientes, 0, 0);
    sem_init(&barbeiro, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&b, NULL, barbeiro_func, NULL);
    for (int i = 0; i < 10; i++) {
        pthread_create(&c[i], NULL, cliente, NULL);
        usleep(200000); // tempo entre clientes
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(c[i], NULL);
    }

    pthread_cancel(b);
    return 0;
}
