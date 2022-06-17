// Aluno: Otávio Malta Borges
// Matrícula: 12011BSI29#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *primos(void *p);
int ehprimo(int n);

static int pri;

int main(int argc, char **argv){
    pthread_attr_t attr; 
    pthread_t id; 
    int aux;

    if (argc == 1){
            printf("%s [Valor]\n", *argv);
            return 1;
        }

    pri = atoi(argv[1]); 
    if (pri < 0) {
        return 2;
    }

    if (pthread_attr_init(&attr) != 0) {
        printf("Erro ao iniciar atributos\n");
        return -1;
    }

    aux = pthread_create(&id, &attr, primos, NULL);
    if (aux != 0) {
        printf("Erro ao criar a thread!\n");
        return -1;
    }
    pthread_join(id, NULL);

    pthread_attr_destroy(&attr);
    return 0;
}

void *primos(void *p) {
    for (int i = 2; i <= pri; i++) {
        if (ehprimo(i)){
            printf("%d ", i);
        }
    }
    printf("\n");
    pthread_exit(0); 
}

int ehprimo(int n){
    for (int i = 2; i < n; i++)
        if (n % i == 0){
            return 0;
        }
    return 1;
}

   
 
    