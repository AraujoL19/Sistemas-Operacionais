#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUMERO_THREADS 10
#define INCREMENTOS 1000

int contadorIncrementos = 0;
pthread_mutex_t mutex;

void* incrementarContador(void* arg){
    for(int i=0;i<INCREMENTOS;i++){
        pthread_mutex_lock(&mutex);
        contadorIncrementos++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    pthread_t threads[NUMERO_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<NUMERO_THREADS; i++){
        pthread_create(&threads[i], NULL, incrementarContador, NULL);
    }

    for(int i=0; i<NUMERO_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    
    printf("Valor final do contador (com mutex): %d\n", contadorIncrementos);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}