#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

void* iniciaThread(void* id){
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main(){
    pthread_t threads[5];
    int i;

    for(i=0;i<5;i++){
        if(pthread_create(&threads[i], NULL, iniciaThread, NULL) != 0){
            perror("Erro: thread não foi criada");
            exit(1);
        }
    }

    for(i=0;i<5;i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}