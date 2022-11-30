/*
Descrição: Neste programa uma quantidade de threads Escritoras e Leitoras é definida. Os dois tipos de threads concorrem pelo 
    acesso da variável dadosCompartilhados, com o objetivo de escrever ou ler. Porém temos que seguir algumas condições, o acesso à escrita é
    exclusivo, ou seja, quando uma thread estiver escrevendo , nenhuma outra thread pode ler ou escrever nessa variável. Se considerarmos que uma thread de Leitura está
    executando, outras threads podem ler também, mas a thread de Escrita não pode escrever. 
        Se uma thread de Escrita solicitar acesso à variável dadosCompartilhados enquanto outras threads Leitoras estiverem executando, devemos priorizar a thread Escritora, 
não permitindo que nenhuma nova thread Leitora tente acessar a variável compartilhada, esperando que todas as threads de Leitura que já estavam na seção crítica terminem
de executar, para que em seguida, seja possível executar a thread de Escrita.  
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 17/04/2021
Data de modificação: 21/04/2021
*/

#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <pthread.h>    /* POSIX Threads */
#include <semaphore.h>  /* Semaphore */
#include <sched.h>      /*Utiliza a função sched_yield*/

#define  ESCRITORES 2   /*Quantidade de threads Escritores*/
#define  LEITORES 6     /*Quantidade de threads Leitores*/

int dadosCompartilhados = 0;    /* Variável compartilhada entre as threads*/
int qtd_leitores = 0;           /* Número de threads leitores executando*/
int qtd_escritores = 0;         /* Número de threads Escritores executando */
int escritoresEsperando = 0;    /* Número de Escritores esperando para escrever */
pthread_mutex_t mutex;          /* Declaração de um mutex*/
pthread_cond_t cond_esc, cond_leit; /* Duas variáveis condicionais são criadas. cond_esc - */

void *leitura(void *ptr){    /*Função do Leitor que recebe NULL como parâmetro*/
    while (1){              /*Leitores sempre ficam tentando ler*/
        /*Bloqueia o mutex*/
        pthread_mutex_lock(&mutex);     /*Início da seção crítica*/
        while (qtd_escritores > 0 || escritoresEsperando > 0){  /*Enquanto houver escritores escrevendo ou tentando escrever*/
            printf("Tentando ler \n");      /*Printa que os leitores estão tentando ler*/
            pthread_cond_wait(&cond_leit, &mutex);  /*Bloqueia as threads Leitoras*/
        }              
        qtd_leitores++;     /*Incrementa a quantidade de leitores*/
        /*Desbloqueia o mutex*/
        pthread_mutex_unlock(&mutex);   /*Saída da seção crítica*/
        /* Leitura */
        printf("Tipo de Thread: Leitora - ThreadId: %ld Leu: %d\n",pthread_self(), dadosCompartilhados);
        /*Bloqueia o mutex*/
        pthread_mutex_lock(&mutex);     /*Início de uma seção crítica*/
        qtd_leitores--; /*Decrementa a quantidade de escritores*/
        if (qtd_leitores == 0 && escritoresEsperando > 0){  /*Se não houver nenhum leitor e mais de um escritor tentando escrever*/
            pthread_cond_signal(&cond_esc); /*Manda um sinal para a cond_escr, permitindo a escrita */
            printf("Ultima thread de leitura finalizou\n"); /*Sinaliza que a última thread de leitura terminou, antes de outra Escritora começar a escrever*/
        }
        /*Desbloqueia o mutex*/
        pthread_mutex_unlock(&mutex);   /*Saída da seção crítica*/
        sched_yield();  /*Yield é usado para dar a oportunidade de outro processo ocupar o processador*/
        sleep(2);   /*Um sleep é executado para que um Ecritor tente escrever*/
    }
}

void *escrita(void *ptr){    /*Função do Escritor, que recebe NULL como parâmetro*/
    while (1){              /*Escritores sempre ficam tentando escrever*/
        /*Bloqueia o mutex*/
        pthread_mutex_lock(&mutex); /*Início da seção crítica*/
        escritoresEsperando++;  /*Incrementa a quantidade de Escritores esperando para escrever*/
        while (qtd_leitores > 0 || qtd_escritores > 0){ /*Caso ainda hajam escritores tentando escrever*/
            printf("Tentado escrever \n");  /*Sinaliza que a thread Escritora está tendo escrever*/
            pthread_cond_wait(&cond_esc, &mutex);   /*Bloqueia a thread Escritora*/
        }
        escritoresEsperando--;  /*Decrementa a quantidade de Escritores que estão esperando para escrever*/
        qtd_escritores++;       /*Incrementa a quantidade de Escritores escrevendo*/
        /*Desbloqueia o mutex*/
        pthread_mutex_unlock(&mutex); /*Saída da seção crítica*/
        //Escreve na variável compartilhada
        dadosCompartilhados++;          

        printf("Tipo de Thread: Escritora ThreadId: %ld Escreveu: %d\n",pthread_self() ,dadosCompartilhados);
        /*Bloqueia o Mutex*/
        pthread_mutex_lock(&mutex); /*Início da seção crítica*/
        qtd_escritores--;           /*Decrementa a quantidade de escritores executando*/
        printf("Thread escrita finalizou \n");
        if (escritoresEsperando > 0){       /*Se houver um ou mais threads Escritoras esperando*/
            pthread_cond_signal(&cond_esc); /*Bloqueia as threads escritoras, para que só as que já estão executando terminem de ler. Não permitindo que outra thread leitora faça uma leitura*/

        }
        else    /*Manda um sinal para que todas as threads Leitoras que estavam esperando , executem*/
            pthread_cond_broadcast(&cond_leit);
        
        /*Desbloqueia o mutex*/
        pthread_mutex_unlock(&mutex);   /*Saída da seção crítica*/
        sched_yield();  /*Saída da seção crítica*/
        sleep(2);   /*Um sleep é executado para que um Leitor tente ler*/
    }
}

int main(){
    /*Cria o mutex*/
    pthread_mutex_init(&mutex, NULL);      
    
    pthread_t w[ESCRITORES];    /*Declaração de um vetor de threads escritores, com o tamanho igual a ESCRITORES*/
    pthread_t r[LEITORES];      /*Declaração de um vetor de threads leitoras, com o tamanho igual a LEITORES*/
    
    //Criar as threads leitores e escritores
        /*Cria todas as threads Leitoras, passando como parâmetro a função leitura*/
    for(int j=0; j<LEITORES; j++){
        pthread_create(&r[j], NULL, leitura, NULL);

    }
        /*Cria todas as threads Escritores, passando como parâmetro a função escrita*/
    for(int i=0; i<ESCRITORES; i++){
        pthread_create(&w[i], NULL, escrita, NULL);

    }
    /*Espera todas as threads Escritoras*/
    for(int i=0; i < ESCRITORES; i++){
        pthread_join(w[i], NULL);
    }

    /*Espera todas as threads Leitoras*/
    for(int j=0; j < LEITORES; j++){
        pthread_join(r[j], NULL);

    }

return 0;
}