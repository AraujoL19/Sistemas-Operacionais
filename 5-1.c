#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//inclusão da biblioteca


int main() {
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            printf("Filho %d criado\n", getpid());
            return 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    //espera os tres filhos terminarem
    
    printf("Pai finalizado\n");
    return 0;
}
