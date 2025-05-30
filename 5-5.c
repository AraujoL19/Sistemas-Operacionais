#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

sem_t garfo[5];

void* filosofo(void* arg) {
    int id = *(int*)arg;
    int primeiro = id;
    int segundo = (id + 1) % 5;

    if (id == 4) {
        primeiro = (id + 1) % 5;
        segundo = id;
    }

    while (1) {
        sem_wait(&garfo[primeiro]);
        sem_wait(&garfo[segundo]);

        printf("Filósofo %d comendo\n", id);
        sleep(1);

        sem_post(&garfo[primeiro]);
        sem_post(&garfo[segundo]);

        printf("Filósofo %d pensando\n", id);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t[5];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        sem_init(&garfo[i], 0, 1);
    }

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&t[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(t[i], NULL);
    }

    return 0;
}

//deadlock ocorre porque todos os filósofos pegam o primeiro garfo e depois ficam bloqueados esperando o segundo,criando um ciclo de espera circular