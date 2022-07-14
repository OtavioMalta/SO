#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define FILESQ ((numFil + 1) % 5)
#define FILDIR ((numFil - 1) % 5)

//Aluno: Otávio Malta Borges
// Matrícula: 12011BSI291

sem_t mutex;
pthread_t filosofos[5];

void pensar(int numFil) {
    int tempo = (rand() % 5);  
    printf("Filósofo %d esta pensando - %d segundos\n", numFil, tempo); 
    sleep(tempo);
}

void comer(int numFil) {
    int tempo = (rand() % 5);
    printf("Filósofo %d esta comendo - %d segundos\n", numFil, tempo);
    sleep(tempo);
}

void pegar(int numFil) {
    sem_wait(&mutex);
}

void soltar(int numFil) {
    sem_post(&mutex);
}

void *filosofo(void *arg) {
    int *num = (int *)(arg);

    while(1) {
        pensar(*num);
        pegar(*num);
        comer(*num);
        soltar(*num);
    }
    pthread_exit((void*) 0);
}

int main(void) {   
    int filo[5] = {0, 1, 2, 3, 4};
    sem_init(&mutex, 0, 1);

    for(int i = 0; i < 5; i++) {
        pthread_create(&filosofos[i], NULL, filosofo, &filo[i]);
    }
     for(int i = 0; i < 5; i++) {
        pthread_join(filosofos[i], NULL);
     }
    sem_destroy(&mutex);
    return 0;
}   