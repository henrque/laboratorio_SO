/*
Descrição: Neste programa o usuário define a quantidade de threads do tipo Ping e Pong, e elas alternam printando "ping" e "pong". Cada thread de cada tipo 
    disputa o processador para printar (Ping se você é um thread do tipo Ping ou Pong, se você é uma thread do tipo Pong). Neste programa Ping e Pong serão printados 
    alternadamente infinitamente, podendo usar "CTRL+C" para interromper sua execução.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 05/04/2021
Data de modificação: 07/04/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>          /*Inclui a função sched_yield*/
#include <unistd.h>

int flag = 0;               /*Flag para marcar se será printado ping ou pong*/
int contPing, contPong;     /*Quantidade de threads do tipo ping e pong que serão usadas*/

pthread_mutex_t mutex;      /*variável mutex*/

void *ping(void *ptr){                  /*Função que printa a palavra Ping*/
    while(1){                           /*while infinito*/
        pthread_mutex_lock(&mutex);     /* Inicio da Seção Critica, passando como parâmetro o mutex */
        if(flag == 0){                  /*Se a flag for igual a zero, devemos printar "Ping"*/
            printf("Ping \n");          /*Printa Ping*/
            flag = 1;                   /*Muda a flag para 1, para que possa ser printado Pong na próxima execução de uma thread*/
            sleep(1);                   /*Executa um sleep para que possa ser possível ver "Ping" ser printado*/
        }
        pthread_mutex_unlock(&mutex);   /*saida da Seção Critica*/
        sched_yield();                  /*Yield é usado para dar a oportunidade de outro processo ocupar o processador*/
    }
    pthread_exit(0);                    /*Finaliza a execução da thread*/
}

void *pong(void *ptr){                  /*Função que printa a palavra Pong*/
    while(1){                           /*while infinito*/
        pthread_mutex_lock(&mutex);     /* Inicio da Seção Critica, passando como parâmetro o mutex */
        if(flag == 1){                  /*Se a flag for igual a um, devemos printar "Pong"*/ 
            printf("Pong \n");          /*Printa Pong*/
            flag = 0;                   /*Muda a flag para 0, para que possa ser printado Ping na próxima execução de uma thread*/
            sleep(1);                   /*Executa um sleep para que possa ser possível ver "Pong" ser printado*/
        }
        pthread_mutex_unlock(&mutex);   /*saida da Seção Critica*/
        sched_yield();                  /*Yield é usado para dar a oportunidade de outro processo ocupar o processador*/
    }                                    
    pthread_exit(0);                    /*Finaliza a execução da thread*/
}


int main(){
    pthread_mutex_init(&mutex, NULL);                       /*Esta chamada é usada para inicializar um mutex e seus atribuitos*/
    printf("Digite o numero de threads para pings: ");      
    scanf("%d",&contPing);                                  /*Recebe a quantidade de threads do tipo Ping que serão criadas*/
    printf("Digite o numero de threads para pongs: ");
    scanf("%d",&contPong);                                  /*Recebe a quantidade de threads do tipo Pong que serão criadas*/
        
    pthread_t tping[contPing];                              /*Vetor de threads do tipo Ping*/
    pthread_t tpong[contPong];                              /*Vetor de threads do tipo Pong*/

    for(int i=0; i<contPing; i++){
        pthread_create(&tping[i], NULL, ping, NULL);        /*Cria individualmente cada thread do tipo Ping, passando como parâmetro o endereço da thread e a função que será executada*/
    }
    
    for(int i=0; i<contPong; i++){
        pthread_create(&tpong[i], NULL, pong, NULL);        /*Cria individualmente cada thread do tipo Pong, passando como parâmetro o endereço da thread e a função que será executada*/
    }

    for(int i=0; i<contPong; i++){                          /*Espera a junção das threads do tipo Pong*/
		pthread_join(tpong[i], NULL);
	}

    for(int i=0; i<contPing; i++){                          /*Espera a junção das threads do tipo Ping*/
	    pthread_join(tping[i], NULL);
	}
    pthread_mutex_destroy(&mutex);                          /*Destrói o mutex referenciado*/
}