/*
Descrição: Neste programa, dado um vetor que foi criado aleatóriamente, criamos várias threads que irão buscar um elemento (ELEMENTO_PROCURADO) no vetor.
	Cada thread procurará este elemento em um pedaço específico, e esta parte do vetor específica é dividida na main. Ao encontrar o elemento retornamos o id da thread
	que o encontrou e quantas vezes ele foi encontrado no vetor.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 17/03/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h> //Biblioteca para que possa ser calculado o tempo de execução

#define NUM_THREADS 3		//Número de Threads
#define VETOR_TAM 10	// Tamanho do vetor que será aleatóriamente criado
#define ELEMENTO_PROCURADO 3		//Elemento que será procurado no vetor

struct data_chunk{	//Data Chunk que guardará as posições que cada thread deve percorrer
	int posInicio;
	int posFinal;
	int *vetor;		
	int flagEncontrou;
};

void *buscaVetor(void *ptr){						/*Recebemos o data Chunk de cada Thread como parâmetro como ponteiro de void*/
	struct data_chunk *dados = ptr;		
	dados->flagEncontrou = 0;						/*Flag que identifica se o número foi encontrado*/
	
	for(int i = dados->posInicio; i<=dados->posFinal; i++){	/*A thread percorre as posições do vetor que foram anteriormente dividas*/
		if(dados->vetor[i]== ELEMENTO_PROCURADO){							/*Compara o elemento de todas as posições do vetor com o elemento que estamos procurando*/
			//printf("Thread id:%ld Valor:%d \n",pthread_self(), dados->vetor[i]);
			dados->flagEncontrou++;							/*Se o elemento é encontrado a flagEncontrou é incrementada*/
		}
	}
	return NULL;									/*Termina a execução da funcão*/
}

int main(){
	int vetor[VETOR_TAM];	//Vetor que será populado
	srand(time(NULL));			
	for(int i=0; i<VETOR_TAM ; i++){	//popula o vetor com valores até 10
		vetor[i] = rand()%10;
	}
	struct data_chunk dados[NUM_THREADS];	//É criado um Data Chunk para cada Thread

	/* A divisão do vetor entre as threads é feita */
    int tamParte = VETOR_TAM/NUM_THREADS;	/*Divide o tamanho que cada thread percorre no vetor*/
    int iniParte = 0;
    int fimParte = tamParte-1;
    for (int p=0; p < NUM_THREADS; p++) {	/*Escreve no Data Chunk a posição inicial, final e o vetor*/
        dados[p].posInicio = iniParte;
        dados[p].posFinal = fimParte;
        dados[p].vetor= vetor;
        iniParte = fimParte + 1;
        fimParte += tamParte;

    }
    dados[NUM_THREADS-1].posFinal = VETOR_TAM-1;	/*Atribui a posição final do vetor para o data Chunk da última thread criada*/
	
	pthread_t t[NUM_THREADS];	//Um vetor de threads é criado

	for (int i=0; i < NUM_THREADS; i++){	//Usamos o pthread_create para criar as N threads
        pthread_create(&t[i], NULL, buscaVetor, &dados[i]);	//Cada thread executa a função buscaVetor
	}

	for(int i=0; i<NUM_THREADS; i++){		/*Espera a junção das threads*/
		pthread_join(t[i], NULL);
	}
	for(int i=0; i<NUM_THREADS; i++){		//
		if(dados[i].flagEncontrou == 0){
		printf("Não foi encontrado na thread: %ld\n",t[i]);
		}
		else{
			printf("Foram encontrados %d vezes na thread: %ld \n",dados[i].flagEncontrou,t[i]);
		}
	}
	/*
	Estas linhas servem para printar o vetor, porém foram comentadas para diminuir a poluição no terminal
    Descomente caso seja necessário verificar os valores contidos no vetor 
	for(int i = 0; i<V; i++){
		printf("%d, ",vetor[i]);
	}
	printf("\n");
	*/
}