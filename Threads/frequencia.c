#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 2
#define V 15

struct dataChunk{
    int posInicio;
    int posFinal;
    int *vetor;
};

int freq[10] = {0,0,0,0,0,0,0,0,0,0};

void *frequencia(void *ptr){
    struct dataChunk *dados = ptr;
    printf("Thread id: %ld, Posicao inicio: %d, Posicao final: %d\n",pthread_self(), dados->posInicio, dados->posFinal);
    for(int i = dados->posInicio; i<= dados->posFinal; i++){
        freq[dados->vetor[i]]++;
    }
    return NULL;
}

int main(){ 
    int vetor[V];
    srand(time(NULL));
	for(int i=0; i<V ; i++){
		vetor[i] = rand()%10;
	}
    struct dataChunk dados[N];

    int tamParte = (V)/N;
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < N; p++) {
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].vetor= vetor;
        iniParte = fimParte +1;
        fimParte += tamParte;

    }
    dados[N-1].posFinal = V-1;

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, frequencia, &dados[0]);
    pthread_create(&thread2, NULL, frequencia, &dados[1]);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 

    for(int i = 0; i < 10; i++){
        printf("Frequencia de %d : %d\n",i, freq[i]);
    }
    /*
    for(int i = 0; i < V;i++){
        printf("%d, ",vetor[i]);
    }
    */
   return 0;
}
