// Aluno: Otávio Malta Borges
// Matrícula: 12011BSI29
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int *val = NULL; 
static int tam = 0;

static int med;
static int min;
static int max;

int valores(int argc, char **argv);
void *media(void *p);
void *minimo(void *p);
void *maximo(void *p);

int main(int argc, char **argv){
    pthread_attr_t attr; 
    pthread_t idMedia, idMin, idMax; 
    int aux;

    if (argc == 1){
        printf("%s [lista de valores]\n", *argv);
        return 1;
    }
    if (valores(argc - 1, argv + 1) < 0){
        return -1;
    } 

    if (pthread_attr_init(&attr) != 0) {
        printf("Erro ao iniciar atributos\n");
        return -1;
    }

    // MEDIA
    aux = pthread_create(&idMedia, &attr, media, NULL);
    if (aux != 0) {
        printf("Erro ao criar a thread da média!\n");
        return -1;
    }

    // MAXIMO
    aux = pthread_create(&idMax, &attr, maximo, NULL);
    if (aux != 0){
        printf("Erro ao criar a thread ddo maximo!\n");
        return -1;
    }

    // MINIMO
    aux = pthread_create(&idMin, &attr, minimo, NULL);
    if (aux != 0){
        printf("Erro ao criar a thread do minimo!\n");
        return -1;
    }

    if (pthread_join(idMedia, NULL) == 0){
        printf("O valor médio é %d\n", med);
    }

    if (pthread_join(idMin, NULL) == 0){
        printf("O valor mínimo é %d\n", min);
    }

    if (pthread_join(idMax, NULL) == 0){
        printf("O valor máximo é %d\n", max);
    }

    pthread_attr_destroy(&attr);
    return 0;
}

int valores(int argc, char **argv){
    int i;
    tam = argc;
    
    if (argc <= 0 || argv == NULL){
        return -1;
    }

    val = (int*)malloc(argc * sizeof(*val));

    if (val == NULL){
        printf("Erro ao alocar os valores\n");
        return -1;
    }

    for (i = 0; i < argc; i++){
        val[i] = atoi(argv[i]); 
    }
    return 0;
}

void *media(void *p) {
    if (val && tam > 0){
        int i;
        med = val[0];
        for (i = 1; i < tam; i++){
            med += val[i];
        }
        med /= tam;
    }
    pthread_exit(0); 
}

void *minimo(void *p){
    if (val && tam > 0){
        int i;
        min = val[0];
        for (i = 1; i < tam; i++)
            if (min > val[i]){
                min = val[i];
            }
    }
    pthread_exit(0);
}

void *maximo(void *p){
    if (val && tam > 0){
        int i;
        max = val[0];
        for (i = 1; i < tam; i++)
            if (max < val[i]){
                max = val[i];
            }
    }
    pthread_exit(0);
}