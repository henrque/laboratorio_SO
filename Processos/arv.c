/*
Descrição: O código realiza a criação de uma árvore binaria com os processos possuindo 4 niveis.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 09/03/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


void main(){
    pid_t pid_pai; //variavel para guardar o pid do processo
    int status; //representa o status dos filhos criados

    for(int i=0; i<3; i++){
        pid_pai = fork();    //cria um processo filho
        if(pid_pai){       // se ele for pai, entra no if
            pid_pai = fork(); //cria um outro processo processo filho
            if(pid_pai){   //se for pai entra no if para acabar com a execução do pai
                wait(&status); //após criar dois processos filhos, o pai espera o término da execução dos filhos
            }
        }
    }

   sleep(50); //faz o processo dormir por 50 segundos
}