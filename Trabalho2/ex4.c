#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    int pid;
    printf("Processo: %d \n",getpid());
    pid = fork();
    
    if (pid< 0){ //erro ao criar
        printf("[ERRO] Não foi possivel criar o processo filho \n");
    }
    else if(pid == 0){ //filho
        printf("Processo filho: %d \n", getpid());
        exit(0);
    }
    else { //pai 
        sleep(10); //esperando o filho
        printf("Processo encerrado\n");
        return 0;
    }
}