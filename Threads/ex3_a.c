/*
Descrição: Neste programa dado um arquivo que contém uma matrix, é possível calcular uma
média aritmética de suas linhas, dividindo a matrix em partes iguais, na qual cada parte será 
executada por diferentes threads. Ao final as médias aritméticas de suas linhas serão escritas no arquivo 
media_aritmetica.txt.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 16/03/2021
Data de modificação: 17/03/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>   /*Incui a função para calcular o tempo de execução*/
#include "matriz.c" /*Inclui funções para manipulação da matriz, como por exemplo (create_matrix, generate_elements,read_matrix_from_file)*/

#define NUM_THREADS 1 /*Número de threads*/


FILE *pontArqMedia; //Ponteiro para escrever no Arquivo que guarda média aritmética
FILE *pontMatriz; //Ponteiro para escrever a matriz criada no arquivo

struct dataChunk{   /*Data Chunk que guardará as linhas que cada thread deve percorrer*/
    int **matriz;
    int coluna;
    int posInicio;
    int posFinal;
    float *vetor;
};
    /* Função que calcula a média Aritmética de cada linha da matriz*/
void *mediaAritmeticaMatriz(void *ptr){ /*Recebe como parâmetro o data chunk de cada thread*/
    struct dataChunk *dados = ptr;
    for(int i = dados->posInicio; i<=dados->posFinal;i++){  /*A thread percorre algumas linhas específica da matriz. Quais linhas ela vai percorrer foi determinada na main*/
            float soma = 0;                             /*Variável soma que guarda a soma de uma linha inteira.*/
            for (int j = 0; j < dados->coluna; j++){
                soma += dados->matriz[i][j];            /*Soma é incrementado, somando o valor do próximo elemento da linha*/
            }
        dados->vetor[i] = soma/dados->coluna;           /*A média Aritmetica da linhas é guardada no vetor*/
    }
    return NULL;        /*Encerra a execução da função*/
}


int main(){
    clock_t tempo;      /*Variável do tipo clock é criada para poder determinar o tempo de execução*/
    int linhas = 4;     /*Quantidade de linhas*/
    int colunas = 4;    /*Quantidade de colunas*/
    int **m;            /*Ponteiro de ponteiro que guarda a matrix*/
    m = create_matrix(linhas,colunas);      /*Cria uma matriz, passando como parâmetro a quantidade de linhas e colunas*/
    generate_elements(m,linhas,colunas,100);    /*Gera aleatóriamente os elementos, passando como parâmetro a matriz, quantidade de linhas e colunas*/
    
    pontMatriz = fopen("Matriz.in","w");    /*Abre o arquivo e escreve a matriz*/
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
    fclose(pontMatriz);         /*Fecha o arquivo*/
    m = read_matrix_from_file("Matriz.in",&linhas,&colunas); /*Lê a matrix do arquivo, passando como parâmetro o nome do arquivo, o endereço da variável de linhas e colunas*/
    
    float vetor[linhas];        /*Cria o vetor que guarda as médias com um tamanho igual a quantidade de linhas*/
    struct dataChunk dados[NUM_THREADS]; /*É criado um Data Chunk para cada Thread*/

    /*É dividido a quantidade de linhas que cada thread vai executar*/
    int tamParte = (linhas)/NUM_THREADS;
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < NUM_THREADS; p++) { /*Escrevemos no data chunk em qual linha a thread começa e para de executar, passando também a própra matriz*/
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].matriz= m;
        dados[p].coluna = colunas;
        dados[p].vetor= vetor;
        iniParte = fimParte +1;
        fimParte += tamParte;
    }
    dados[NUM_THREADS-1].posFinal = linhas-1; /*Atribui a posição final , que nesse caso é igual a última linha, para o data Chunk da última thread criada*/

    pthread_t t[NUM_THREADS]; /*Um vetor de threads é criado*/

    tempo = clock();    /*Começa a contar o tempo*/
	for (int i=0; i < NUM_THREADS; i++){    /*Usamos o pthread_create para criar as N threads*/
        pthread_create(&t[i], NULL, mediaAritmeticaMatriz, &dados[i]); /*Cada thread executa a função mediaAritmeticaMatriz*/
	}

	for(int i=0; i<NUM_THREADS; i++){ /*Espera a junção das threads*/
		pthread_join(t[i], NULL);
	}

    tempo = clock() - tempo;        /*Faz uma subtração do tempo inicial com o tempo final , resultando no tempo final de execução*/
    pontArqMedia = fopen("media_aritmetica.txt","w"); /*Abre o arquivo media_aritmetica.txt*/
    if(pontArqMedia == NULL){               /*Verifica se conseguiu abrir o arquivo*/
        printf("Erro na abertura do arquivo\n");
        return 1;
    }

    for(int i = 0; i < linhas; i++){ /*Escreve as médias de cada linha em um arquivo media_aritmetica.txt*/
        fprintf(pontArqMedia,"Media aritmetica da coluna %d: %.2f \n",i,vetor[i]);
    }


    fclose(pontArqMedia);           /*Fecha o arquivo*/
    printf("Tempo de Execução %.2lfms\n",(((double)tempo)/(CLOCKS_PER_SEC/1000))); /*Retorna o tempo de execução*/
    return 0;               /*Encerra a execução do programa*/
}   