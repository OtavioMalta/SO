#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Nome: Otávio Malta Borges
// Matrícula: 12011BSI291

main () {
    char origem[50]; 
    char destino[50];
    FILE* arq;
    char v[200];
    int p = 1;

    while(p != 0){  
        printf("Origem: ");
        scanf("%s",&origem);

        printf("Destino: ");
        scanf("%s",&destino); 

        arq = fopen(origem, "r");

        if(origem == NULL || destino == NULL){
             printf("ERRO: Arquivos nulos!\n");
        }else if (arq == NULL ){
            printf("ERRO: Arquivo nao encontrado!\n");
        } else {
            sprintf(v,"cp %s %s", origem, destino); 
            system(v);
            printf("Arqivos copiados com sucesso!\n");
            p=0;
        }
    }
}