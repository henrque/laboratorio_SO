#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define N 3
#define V 10
#define X 5
struct data_chunk{
	int posInicio;
	int posFinal;
	int *vetor;
	int flagEncontrou;
};

void *buscaVetor(void *ptr){
	struct data_chunk *dados = ptr;
	dados->flagEncontrou = 0;
	printf("Thread id: %ld, Posicao inicio: %d, Posicao final: %d\n",pthread_self(), dados->posInicio, dados->posFinal);
	for(int i = dados->posInicio; i<=dados->posFinal; i++){
		if(dados->vetor[i]== X){
			//printf("Thread id:%ld Valor:%d \n",pthread_self(), dados->vetor[i]);
			dados->flagEncontrou++;
		}
	}
	return NULL;
}

int main(){
	int vetor[V];
	srand(time(NULL));
	for(int i=0; i<V ; i++){
		vetor[i] = rand()%10;
	}
	struct data_chunk dados[N];

    int tamParte = V/N;
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < N; p++) {
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].vetor= vetor;
        iniParte = fimParte + 1;
        fimParte += tamParte;

    }
    dados[N-1].posFinal = V-1;
	
	pthread_t t[N];

	for (int i=0; i < N; i++){
        pthread_create(&t[i], NULL, buscaVetor, &dados[i]);
	}

	for(int i=0; i<N; i++){
		pthread_join(t[i], NULL);
	}
	for(int i=0; i<N; i++){
		if(dados[i].flagEncontrou == 0){
		printf("Não foi encontrado na thread: %ld\n",t[i]);
		}
		else{
			printf("Foram encontrados %d vezes na thread: %ld \n",dados[i].flagEncontrou,t[i]);
		}
	}
	/*
	for(int i = 0; i<V; i++){
		printf("%d, ",vetor[i]);
	}
	printf("\n");
	*/
}