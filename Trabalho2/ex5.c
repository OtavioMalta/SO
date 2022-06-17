#include<stdio.h>
#include<malloc.h>
#include<string.h>
int i,j,k,num,mtt,mwt,quantum,ex=0,inicio,fim=0,*btAux;

#define NPROC 5

void rr();
void fcfs();

struct processo{
  char nome[10];
  int bt; // CPU burst
  int tt;// Turn around time
  int wt; // waiting time
  int status;
  int chg; // chegada
  int count;
}p[NPROC];


int main(){
    //system("clear");
    FILE *tf = fopen("tarefas.txt", "r");

    if(tf == NULL){
        printf("[Erro] Nao foi possivel abrir o arquivo!\n");
        return -1;
    }

    btAux = (int*)malloc(NPROC*sizeof(int));

    int i = 0;
    while(!feof(tf)){
        fscanf(tf, "%s %d", p[i].nome, &p[i].bt);
        p[k].status = 0;
        p[k].chg = 0; // Caso o tempo de chegada for diferente, alterar aqui
        fim += p[i].bt;
        btAux[i] = p[i].bt;

        i++;
    }
    fclose(tf);

    printf("Processos informados: ");
    printf("\nnome\tCPU Burst\tStatus\n");

    for(i=0;i<NPROC;i++) {
            printf("%s\t%d\t\t",p[i].nome,p[i].bt);
            printf(p[i].status == 1? "Finalizado\n" : "Pronto\n");
        }
        
    sleep(2);
        printf("\nEscolha um algoritmo:\n 1.FCFS\n 2.ROUND ROBIN\n");
        scanf("%d", &i);
        switch (i){
            case 1:
                fcfs();
                break;
            case 2:
                rr();
                break;
            default:
                printf("[ERRO]");
        }
}

    void fcfs(){
        i=0;
        num=0;
        mtt=0;
        mwt=0;

        for(k=0;k<NPROC;){
                system("clear");
                printf("\nnome\tCPU Burst\tTime Waiting\tTurn around time\tStatus\n");
                p[k].wt=i-p[k].chg; // Caso a chegada fosse diferente de 0

                p[k].status=1;
                i=i+p[k].bt;
                p[k].tt=p[k].wt+p[k].bt;

                for(j=0;j<NPROC;j++){
                    printf("%s\t%d\t\t%d\t\t%d\t\t\t",p[j].nome,p[j].bt,p[j].wt,p[j].tt);
                    printf(p[j].status == 1? "Finalizado\n" : "Pronto\n");
                    
                }
                sleep((p[k].bt)/10);
                mtt+=p[k].tt;
                mwt+=p[k].wt;

                num++;
                k++;
        }
        printf("\nMédia do Turn Around Time: %d", mtt/NPROC);
        printf("\nMédia do Time Waiting: %d\n", mwt/NPROC);
    }

   
    void rr(){
    int nproc = NPROC;
    i = 0;
    p[0].wt = 0;
    printf("\n Quantum: ");
    scanf("%d", &quantum);
    printf("\nInicio\tProcesso\tBurst\tFim\n");

    for(fim=0, k=0; nproc!=0;) {
        inicio = fim;
        if(p[k].count){ // Waiting time
            p[k].wt = inicio;
            p[k].count = 1;
        }
        if(btAux[k] <= quantum && btAux[k] > 0) {
            fim += btAux[k];
            btAux[k] = 0;
            ex = 1;
        }
        else if(btAux[k] > quantum) {
            btAux[k] -= quantum;
            fim += quantum;
        }
        if(btAux[k] == 0 && ex == 1) {
            p[k].tt = fim;
            p[k].status = 1;
            nproc--;
            ex=0;
        }
        if(inicio != fim) {
            printf("|%d\tP%d\t\t%d\t%d\t|\n", inicio, k,btAux[k], fim);
        }
        if(k+1 == NPROC)
            k = 0;
        else
            ++k;
    }
    printf("\nnome\tCPU Burst\tTime Waiting\tTurn around time\tStatus\n");
    for(j=0;j<NPROC;j++){
            printf("%s\t%d\t\t%d\t\t%d\t\t\t",p[j].nome,p[j].bt,p[j].wt,p[j].tt);
            printf(p[j].status == 1? "Finalizado\n" : "Pronto\n");
            mtt+=p[j].tt;
            mwt+=p[j].wt;
        }
                
        printf("\nMédia do Turn Around Time: %d", mtt/NPROC);
        printf("\nMédia do Time Waiting: %d\n", mwt/NPROC);
    
    }




    