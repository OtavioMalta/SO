#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

//Aluno: Otávio Malta Borges
// Matrícula: 12011BSI291

sem_t mutexGarfo[5];
pthread_t filosofos[5];

void pegar(int numGarfo) {
    sem_wait(&mutexGarfo[numGarfo]);
}

void soltar(int numGarfo) {
    sem_post(&mutexGarfo[numGarfo]);
}

void pensar(int idFil) {
    int time = (rand() % 5);  
    printf("Filósofo %d esta pensando - %d segs\n", idFil, time); 
    sleep(time);
}

void comer(int idFil) {
    int time = (rand() % 5);
    printf("Filósofo %d esta comendo  - %d segs\n", idFil, time);
    sleep(time);
}

void *filosofo(void *arg) {
    int *num = (int *)(arg);

    while(1) {
        pensar(*num);
        pegar(*num);
        pegar((*num+1)%5);
        comer(*num);
        soltar(*num);
        soltar((*num+1)%5);
    }
    pthread_exit((void*) 0);
}

int main(void) {   
    int filo[5] = {0, 1, 2, 3, 4};

    for(int i = 0; i < 5; i++) {
        sem_init(&mutexGarfo[i], 0, 0);
    }

    for(int i = 0; i < 5; i++) {
        pthread_create(&filosofos[i], NULL, filosofo, &filo[i]);
    }
     for(int i = 0; i < 5; i++) {
        pthread_join(filosofos[i], NULL);
     }

    for(int i = 0; i < 5; i++) {
        sem_destroy(&mutexGarfo[i]);
    }
    return 0;
}   