#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Nome: Otávio Malta Borges
// Matrícula: 12011BSI291

char cmd[100];
char *argv[100];
int pid;
int i;

int main(){
	while(1){
		printf("UnixShell>");
        fgets(cmd, 300, stdin);

        if ((strlen(cmd) > 0)){
            cmd[strlen (cmd) - 1] = '\0';
        }

        if(strcmp("exit", cmd) == 0) {
            break;
        }else if(strcmp("ls", cmd) == 0){
            system(cmd);
        }else{
            char *ptr;
            i = 0;

            ptr = strtok(cmd, " ");
            while(ptr != NULL){
                argv[i] = ptr;
                i++;
                ptr = strtok(NULL, " ");
            }

            pid = fork();
            if(-1 == pid){
                printf("ERRO: Falha ao criar o filho\n");
            }
            else if(0 == pid){
                execvp(argv[0], argv);
            }else{ 
                wait();
            } 
        }
    }
}
