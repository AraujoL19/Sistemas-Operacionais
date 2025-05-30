#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t pid;
    int i;

    for(i=0;i<3;i++){
        pid = fork();
        if(pid<0){
            perror("Erro: fork falhou");
            exit(1);
        }else if(pid==0){
            printf("Processo filho (PID: %d), PID do pai: %d\n", getpid(), getppid());
            exit(0);
        }
    }

    for(i=0;i<3;i++){
        wait(NULL);
    }
    printf("Processo pai finalizado");
    
    return 0;
}