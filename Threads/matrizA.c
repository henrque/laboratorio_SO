#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matriz.c"
#define N 1


FILE *pontArq;
FILE *pontMatriz;
struct dataChunk{
    int **matriz;
    int coluna;
    int posInicio;
    int posFinal;
    float *vetor;
};

void *mediaAritmeticaMatriz(void *ptr){
    struct dataChunk *dados = ptr;
    //printf("Thread id: %ld, Posicao inicio: %d, Posicao final: %d\n",pthread_self(), dados->posInicio, dados->posFinal);
    for(int i = dados->posInicio; i<=dados->posFinal;i++){
            float soma = 0;
            for (int j = 0; j < dados->coluna; j++){
                soma += dados->matriz[i][j];
            }
        dados->vetor[i] = soma/dados->coluna;
    }
    return NULL;
}


int main(){
    clock_t tempo;
    tempo = clock();
    int linhas = 4;
    int colunas = 4;
    int **m;
    m = create_matrix(linhas,colunas);
    generate_elements(m,linhas,colunas,100);
    
    pontMatriz = fopen("Matriz.in","w");
    if(pontMatriz == NULL){
        printf("Erro na abertura do arquivo\n");
        return 1;
    }
    fprintf(pontMatriz,"%dx%d\n",linhas,colunas);
    for(int i = 0; i<linhas; i++){
        for (int j = 0; j<colunas; j++){
            fprintf(pontMatriz,"%d\t",m[i][j]);
        }
        fprintf(pontMatriz,"\n");
    }
    fclose(pontMatriz);
    m = read_matrix_from_file("Matriz.in",&linhas,&colunas);
    
    float vetor[linhas];
    struct dataChunk dados[N];

    int tamParte = (linhas)/N;
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < N; p++) {
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].matriz= m;
        dados[p].coluna = colunas;
        dados[p].vetor= vetor;
        iniParte = fimParte +1;
        fimParte += tamParte;
    }
    dados[N-1].posFinal = linhas-1;

    pthread_t t[N];

	for (int i=0; i < N; i++){
        pthread_create(&t[i], NULL, mediaAritmeticaMatriz, &dados[i]);
	}

	for(int i=0; i<N; i++){
		pthread_join(t[i], NULL);
	}
    pontArq = fopen("media_aritmetica.txt","w");
    if(pontArq == NULL){
        printf("Erro na abertura do arquivo\n");
        return 1;
    }

    for(int i = 0; i < linhas; i++){
        fprintf(pontArq,"Media aritmetica da coluna %d: %.2f \n",i,vetor[i]);
    }


    fclose(pontArq);
    tempo = clock() - tempo;
    printf("Tempo de Execução %.2lfms\n",((double)tempo)/1000);
    return 0;
}