#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define FILESQ ((numFil + 1) % 5)
#define FILDIR ((numFil - 1) % 5)

//Aluno: Otávio Malta Borges
// Matrícula: 12011BSI291

int estado[5];
sem_t mutex;
sem_t mutexGarfo[5]; // de cada filosofo
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

void verifica(int numFil) {
    if((estado[numFil] == 1) && (estado[FILESQ] != 2) && (estado[FILDIR] != 2)) {
        estado[numFil] = 2;
        sem_post(&mutexGarfo[numFil]);
    }
    else {
        printf("O filosofo %d não conseguiu pegar os garfos\n", numFil + 1);
    }
}

void pegar(int numFil) {
    sem_wait(&mutex);
    estado[numFil] = 1;
    verifica(numFil);
    sem_post(&mutex);
    sem_wait(&mutexGarfo[numFil]); 
}

void soltar(int numFil) {
    sem_wait(&mutex);
    estado[numFil] = 0;
    verifica(FILESQ);
    verifica(FILDIR);
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
        sem_init(&mutexGarfo[i], 0, 0);
    }

    for(int i = 0; i < 5; i++) {
        pthread_create(&filosofos[i], NULL, filosofo, &filo[i]);
    }
     for(int i = 0; i < 5; i++) {
        pthread_join(filosofos[i], NULL);
     }
    sem_destroy(&mutex);

    for(int i = 0; i < 5; i++) {
        sem_destroy(&mutexGarfo[i]);
    }
    return 0;
}   