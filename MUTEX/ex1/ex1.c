/*
Descrição: Neste programa 3 threads são criadas, e todas competem para somar individualmente cada linha da matriz, somando cada linha em outra variável que 
        representa a soma total de todas as linhas da matrix.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 05/04/2021
Data de modificação: 07/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "matriz.c"             /*Inclui funções para manipulação da matriz, como por exemplo (create_matrix, generate_elements,read_matrix_from_file)*/
#include <sched.h>              /*Inclui a função sched_yield*/
#define NUM_THREADS 3           /*Número de threads*/

pthread_mutex_t mutex;          /*variável do tipo mutex*/
int coluna;                     /*variável que define a quantidade de colunas*/
int linha;                      /*variável que define a quantidade de linhas*/
int totalDeLinhas = 1000;       /*Quantidade de linhas*/
int somaLinha;

int **matriz;
                                                        /* Função que calcula a soma de cada linha da matriz*/
void *somaMatriz(void* ptr){                            /*Recebe como parâmetro NULL*/
    while(linha < totalDeLinhas){
        pthread_mutex_lock(&mutex);                     /* Inicio da Seção Critica, passando como parâmetro o mutex */
        linha++;                                        /*A linha que a próxima thread lerá é incrementado*/
        pthread_mutex_unlock(&mutex);                   /*saida da Seção Critica, passando como parâmetro o mutex*/
        pthread_t threadId = pthread_self();    
        printf("THREAD: %ld | LINHA[%d]\n", threadId, linha);
        int soma = 0;                                   /*Variável soma que guarda a soma de uma linha inteira.*/
        for (int j = 0; j < coluna; j++){
            soma += matriz[linha-1][j];                 /*Soma é incrementado, somando o valor do próximo elemento da linha*/
        }
        pthread_mutex_lock(&mutex);                     /* Inicio da Seção Critica, passando como parâmetro o mutex */
        somaLinha += soma;                              /*A soma das linhas é guardada no somaLinha*/
        pthread_mutex_unlock(&mutex);                   /*saida da Seção Critica, passando como parâmetro o mutex*/
        sched_yield();                                  /*Yield é usado para dar a oportunidade de outro processo ocupar o processador*/

    }
    pthread_exit(0);                                    /*Finaliza a execução da thread*/
}
 

int main(){
    pthread_mutex_init(&mutex, NULL);                       /*Esta chamada é usada para inicializar um mutex e seus atribuitos*/
    int colunas = 100;                                      /*Quantidade de colunas*/
    coluna = colunas;
    linha = 0;                                              /*Quantidade de linhas*/
    int **m;                                                /*Ponteiro de ponteiro que guarda a matrix*/
    m = create_matrix(totalDeLinhas,colunas);               /*Cria uma matriz, passando como parâmetro a quantidade de linhas e colunas*/
    generate_elements(m,totalDeLinhas,colunas,100);         /*Gera aleatóriamente os elementos, passando como parâmetro a matriz, quantidade de linhas e colunas*/

    matriz = m;                                             /*Passa o endereço da matriz criada aleatóriamente para o variável do tipo global (matriz)*/                       
    
    pthread_t t[NUM_THREADS];                               /*Um vetor de threads é criado, com a quantidade de THREADS definido anteriormente*/

    for(int i = 0; i<NUM_THREADS; i++){                 
        pthread_create(&t[i], NULL, somaMatriz, NULL);      /*Cria individualmente cada thread, passando como parâmetro o endereço da thread e a função que será executada*/
    }

	for(int i=0; i<NUM_THREADS; i++){ 
		pthread_join(t[i], NULL);                           /*Espera a junção das threads, passando como parametro a thread*/
	}
    printf("Soma dos valores no vetor: %d\n", somaLinha);   /*Mostra no terminal a soma de todas as linhas*/
    pthread_mutex_destroy(&mutex);                          /*Destrói o mutex referenciado*/
}   