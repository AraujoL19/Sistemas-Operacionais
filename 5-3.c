#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t empty, full;
int buffer[5], index = 0;

//O deadlock ocorre porque o produtor está esperando o semáforo full e ninguém o incrementa, fazendo o produtor travar

void produtor() {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        buffer[index++] = i;
        printf("Produzido: %d\n", i);
        sem_post(&full);
    }
    return NULL;
}
