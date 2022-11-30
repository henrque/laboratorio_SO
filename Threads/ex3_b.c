/*
Descrição: Neste programa dado um arquivo que contém uma matrix, é possível calcular uma
média harmonica de suas colunas, dividindo a matrix em partes iguais de colunas, na qual cada parte será 
executada por diferentes threads. Ao final, as médias harmonicas de suas colunas serão escritas no arquivo 
media_harmonica.txt.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 16/03/2021
Data de modificação: 17/03/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matriz.c"     /*Inclui funções para manipulação da matriz, como por exemplo (create_matrix, generate_elements,read_matrix_from_file)*/
#include <time.h>       /*Incui a função para calcular o tempo de execução*/

#define NUM_THREADS 1

FILE *pontArq;  //Ponteiro para escrever no Arquivo que guarda média harmonica
FILE *pontMatriz;   //Ponteiro para escrever a matriz criada no arquivo

struct dataChunk{   /*Data Chunk que guardará as colunas que cada thread deve percorrer*/
    int **matriz;
    int linha;
    int coluna;
    int posInicio;
    int posFinal;
    double *vetor;
};
    /* Função que calcula a média Harmonica de cada coluna da matriz*/
void *mediaHarmonicaMatriz(void *ptr){
    struct dataChunk *dados = ptr;
    for(int i = dados->posInicio; i<=dados->posFinal;i++){  /*A thread percorre algumas colunas específica da matriz. Quais colunas ela vai percorrer foi determinada na main*/
            double soma = 0;             /*Variável soma que guarda a soma de uma (1/cada elemento da coluna) inteira.*/
            for (int j = 0; j < dados->linha; j++){
                soma +=  (1 / (double)dados->matriz[j][i]); /*Soma é incrementado, somando o valor de 1/próximo elemento da coluna*/
            }
        dados->vetor[i] =  dados->linha / soma; /*A média harmonica é guardada no vetor*/
    }
    return NULL;            /*Encerra a execução da função*/
}

int main(){
    clock_t tempo;      /*Variável do tipo clock é criada para poder determinar o tempo de execução*/
    int linhas=4;       /*Quantidade de linhas*/
    int colunas=4;      /*Quantidade de colunas*/
    int **m;             /*Ponteiro de ponteiro que guarda a matrix*/
       m = create_matrix(linhas,colunas);       /*Cria uma matriz, passando como parâmetro a quantidade de linhas e colunas*/
    generate_elements(m,linhas,colunas,100);    /*Gera aleatóriamente os elementos, passando como parâmetro a matriz, quantidade de linhas e colunas*/
    
    pontMatriz = fopen("Matriz.in","w");        /*Abre o arquivo e escreve a matriz*/
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
    fclose(pontMatriz);                         /*Fecha o arquivo*/
    m = read_matrix_from_file("Matriz.in",&linhas,&colunas);    /*Lê a matrix do arquivo, passando como parâmetro o nome do arquivo, o endereço da variável de linhas e colunas*/
    
    double vetor[colunas];                  /*Cria o vetor que guarda as médias harmonicas com um tamanho igual a quantidade de colunas*/
    struct dataChunk dados[NUM_THREADS];    /*É criado um Data Chunk para cada Thread*/
    
    /*É dividido a quantidade de colunas que cada thread vai executar*/
    int tamParte = (colunas)/NUM_THREADS;
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < NUM_THREADS; p++) {   /*Escrevemos no data chunk em qual coluna a thread começa e para de executar, passando também a própra matriz*/
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].matriz= m;
        dados[p].linha = linhas;
        dados[p].coluna = colunas;
        dados[p].vetor= vetor;
        iniParte = fimParte +1;
        fimParte += tamParte;
    }
    dados[NUM_THREADS-1].posFinal = colunas-1;  /*Atribui a posição final , que nesse caso é igual a última coluna, para o data Chunk da última thread criada*/
    
    pthread_t t[NUM_THREADS];   /*Um vetor de threads é criado*/

    tempo = clock();    /*Começa a contar o tempo*/    
	for (int i=0; i < NUM_THREADS; i++){    /*Usamos o pthread_create para criar as N threads*/
        pthread_create(&t[i], NULL, mediaHarmonicaMatriz, &dados[i]);   /*Cada thread executa a função mediaHarmonicaMatriz*/
	}

	for(int i=0; i<NUM_THREADS; i++){   /*Espera a junção das threads*/
		pthread_join(t[i], NULL);
	}
    tempo = clock() - tempo;    /*Faz uma subtração do tempo inicial com o tempo final , resultando no tempo final de execução*/
    pontArq = fopen("media_harmonica.txt","w");  /*Abre o arquivo media_aritmetica.txt*/
    if(pontArq == NULL){
        printf("Erro na abertura do arquivo\n");
        return 1;
    }

    for(int i = 0; i < colunas; i++){/*Escreve as médias harmonicas de cada coluna em um arquivo media_aritmetica.txt*/
        fprintf(pontArq,"Media harmonica da linha %d: %.2lf \n",i,vetor[i]);
    }
    fclose(pontArq);            /*Fecha o arquivo*/
    printf("Tempo de Execução %.4lfms\n",(((double)tempo)/(CLOCKS_PER_SEC/1000)));   /*Retorna o tempo de execução*/
    return 0;           /*Encerra a execução do programa*/
}   



