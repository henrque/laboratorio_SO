/*
Descrição: O código recebe o número de processos filhos a ser criado assim como o tamanho do vetor
           após isso o vetor é preenchido com os números desejados, o processo pai cria os processos
           filhos e divide o tamanho do vetor de forma igualitaria para cada filho fazer uma busca do
           valor digitado pelo usuário.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 09/03/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int exec(int *vetor, int n, int m, int filhos);
int start();

int exec(int *vetor, int n, int m, int filhos){
    pid_t pid;          //pid do processo
    int status;         // variavel para verificar o status dos processos filhos
    int inicio= 0;      //guarda o início das partições que serão percorridas
    int encontrou_valor = 0;    //Flag para verificar se o valor foi encontrado
    int particao;               //Posição do tamanho de cada partição que será percorrida

    particao = m/filhos;        //Tenta dividir igualmente o tamanho da partição que será percorrida
    printf("%d", particao);
    for(int i = 0; i < filhos; i++){    //Cada processo filho executa uma busca em uma parte do vetor
        pid = fork();           //Cria um processo filho
        int j;
        if(!pid){       //Se for filho
            for(j = inicio; j <= particao && j < m; j++){ //Percorre o tamanho da partição definida
                if(vetor[j] == n){                      //Verifica se os valores no vetor são iguais ao que estamos procurando
                    /*Retorna o Pid do processo que encontrou o valor
                                e o valor encontrado   */
                    printf("Achei %d\nMeu pid e: %d\n", vetor[j], getpid());    
                    encontrou_valor = 1;
                    break;
                }
            }
        }else{  //Se não encontrar o valor, o processo pai espera os filhos terminarem de executar
            wait(&status);  
            exit(0);        //Encerra o programa
        }
        inicio += particao;     //O início é incrementado 
        particao += particao;
    }

    if(encontrou_valor == 0){
        printf("O numero informado não se encontra no vetor!!\n");
    }
}

int start(){
    int filhos; //Quantidade de filhos
    printf("Digite a quantidade de filhos: ");
    scanf("%d", &filhos);

    int m;  //Tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &m);

    if(filhos < m){ //Verifica se o valor de filhos é menor do que o tamanho do vetor
        int vetor[m];
        printf("Digite os valores:\n"); //Recebe os valores do vetor

        for(int i = 0; i < m; i++){
            scanf("%d", &vetor[i]);
        }

        int n; //Número qu deseja buscar
        printf("\nDigite o numero que deseja buscar: ");
        scanf("%d", &n);

        exec(vetor, n, m, filhos);
        return 0;

    }else{ //Se a quantidade de filhos for maior do que o tamanho do vetor, o programa acaba
        printf("A quantidade de filhos é maior que o tamanho do vetor!!");
    }

}

int main(){
    start();

    return(0);
}