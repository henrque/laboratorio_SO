/*
Descrição: Neste programa duas threads irão percorrer o vetor, cada thread percorrerá metade, 
contando a frequência que cada elemento aparece e guardando esse resultado em um vetor de frequência.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 16/03/2021
Data de modificação: 17/03/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> /* Biblioteca para calcular o tempo de execução*/

#define NUM_THREADS 2 /*Quantidade de threads*/
#define VETOR_TAM 15 /*Tamanho do vetor*/

struct dataChunk{   /*Data Chunk que guardará as posições que cada thread deve percorrer*/
    int posInicio;
    int posFinal;
    int *vetor;
};

int freq[10] = {0,0,0,0,0,0,0,0,0,0}; //Vetor de frequencia declarado como variável global

void *frequencia(void *ptr){
    struct dataChunk *dados = ptr;
    printf("Thread id: %ld, Posicao inicio: %d, Posicao final: %d\n",pthread_self(), dados->posInicio, dados->posFinal);
    for(int i = dados->posInicio; i<= dados->posFinal; i++){ //A thread percorre uma parte específica do vetor, que foi anteriormente determinada*/
        freq[dados->vetor[i]]++;
    }
    return NULL; /*Acaba a execução da função*/
}

int main(){ 
    int vetor[VETOR_TAM]; //Um vetor é criado
    srand(time(NULL));
	for(int i=0; i<VETOR_TAM ; i++){ //O vetor é populado com valores aleatório de 0 à 10
		vetor[i] = rand()%10;       
	}
    struct dataChunk dados[NUM_THREADS]; /*É criado um Data Chunk para cada Thread*/

    /* A divisão do vetor entre as threads é feita */
    int tamParte = (VETOR_TAM)/NUM_THREADS;
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < NUM_THREADS; p++) {   /*Escreve no Data Chunk a posição inicial, final e o vetor*/
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].vetor= vetor;
        iniParte = fimParte +1;
        fimParte += tamParte;

    }
    dados[NUM_THREADS-1].posFinal = VETOR_TAM-1; /*Atribui a posição final do vetor para o data Chunk da última thread criada*/

    pthread_t thread1, thread2; //Declara uma variável do tipo thread
    pthread_create(&thread1, NULL, frequencia, &dados[0]);/*Cria a thread 1 e executa a função frequencia*/
    pthread_create(&thread2, NULL, frequencia, &dados[1]);/*Cria a thread 2 e executa a função frequencia*/
    
    pthread_join(thread1, NULL);    /*Espera a junção das threads*/
    pthread_join(thread2, NULL);    /*Espera a junção das threads*/

    for(int i = 0; i < 10; i++){    /*Retorna quantas vezes cada elemento foi encontrado no vetor de elementos, 
                                        printando o vetor de frequência*/
        printf("Frequencia de %d : %d\n",i, freq[i]);
    }
    /*   Estas linhas servem para printar o vetor, porém foram comentadas para diminuir a poluição no terminal
         Descomente caso seja necessário verificar os valores contidos no vetor 
    for(int i = 0; i < V;i++){
        printf("%d, ",vetor[i]);
    }
    */
   return 0;
}
