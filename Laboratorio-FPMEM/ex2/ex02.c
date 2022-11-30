/*
Descrição: Um programa que lê um arquivo contendo configurações de inicialização
e guarda os valores contidos nesse arquivo em variaveis internas, ao receber 
o sinal SIGHUP o programa abre o arquivo novamente e atualiza os valores do 
arquivo nas variaveis internas.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação:   31/03/2021
Data de atualização: 01/04/2021
*/


#include <stdio.h>
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

FILE *pont_arq; /*Ponteiro de arquivo*/

int flag = 0; /*Flag para ver o que o usuário deseja fazer no menu*/
char str[100]; /*Recebe o tipo do atributo contido no arquivo*/
char background[30], qtde[20], cor[30]; /**/

/*Função que trata o sinal recebido, que tem como parametro de entrada o sinal*/
void sig_handler(int signo){
	if (signo == SIGHUP){
		printf("received SIGHUP\n");
        pont_arq = fopen("arquivo.txt", "r");
        if(pont_arq == NULL){
            printf("Erro arquivo vazio");
        }
        else{
            
        }
        /*Recebe os valores do arquivo e altera as variaveis internas */
        fscanf(pont_arq,"%s %s\n", str, background);            
        fscanf(pont_arq,"%s %s\n", str, qtde);            
        fscanf(pont_arq,"%s %s\n", str, cor); 
        fclose(pont_arq);
     
    }  
}


int main(void){
    char ch;
    /*Abre o arquivo "arquivo.txt"*/
    pont_arq = fopen("arquivo.txt", "r");
        if(pont_arq == NULL){
            printf("Erro");
        }
        /*Recebe os valores do arquivo e altera as variaveis internas*/
        fscanf(pont_arq,"%s %s\n", str, background);            
        fscanf(pont_arq,"%s %s\n", str, qtde);            
        fscanf(pont_arq,"%s %s\n", str, cor); 

    fclose(pont_arq);
    /* Associa a função sig_handler para tratar os sinais recebidos, verificando se foi possivel receber o sinal*/
    if (signal(SIGHUP, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGHUP\n");
        
        printf("My PID is %d.\n", getpid());/**/


    /* Laço de repetição infinito mostrando o menu */
    while(1){
        printf("Digite 1 - Ver atualizações no arquivo: \n");
        printf("Digite 0 - Encerrar a execução do processo: \n");
        scanf("%d", &flag);
        switch(flag){   /*A flag determina se o usuário deseja ver os valores dos atributos do arquivo ou encerrar a execução*/
            case 1:
                printf("Backgorund:%s Qtde:%s Cor:%s\n",background, qtde, cor); /*Mostra no terminal a valor atualizado dos atributos no arquivo*/
                break;
            case 0:
                return 0;
                break;
            default:
                break;
        }
    }
    
    return 0;
}



