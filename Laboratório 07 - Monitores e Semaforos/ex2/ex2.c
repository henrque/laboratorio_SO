/*
Descrição: Neste programa teremos dois tipos de threads, a thread Barbeiro e as threads Clientes. A sala de
barbearia contém apenas uma cadeira do barbeiro, e 3 cadeiras para que os clientes possam sentar e esperar o barbeiro 
terminar de cortar o cabelo de alguém que esteja sendo atendido. Se não houver ninguém na barbearia para ser atendido, 
o barbeiro dorme, porém, se houver alguém na barbearia, o barbeiro atenderá os clientes na ordem de chegada.
    Se um cliente chegar na barbearia e todas as cadeira de espera estiverem ocupadas, o cliente vai embora e não volta mais.
    Ao final do dias, depois de atender todos os clientes, o babeiro fecha a loja, definindo a variável fimDoExpediente como 0.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 17/04/2021
Data de modificação: 21/04/2021
*/

#include <unistd.h>    
#include <sys/types.h> /*Tipos primitivos */
#include <errno.h>     /*Para erros */
#include <stdio.h>     /*Para comandos de entrada e saída*/
#include <pthread.h>   /*POSIX Threads */
#include <semaphore.h> /* Para a utilização de semáforos */
#include <stdlib.h>    /*Para a utilização da função "srand()" */

#define N 3     /*Número de cadeiras*/
#define K 10    /*Número de thread clientes*/
#define B 1     /*Número de barbeiro*/

/* semáforo declarado como global */
sem_t barbeiroSem;      /*Semaforo do barbeiro*/
sem_t mutex;            /* Semaforo do cliente */
sem_t filaDeEspera;     /* atua como um mutex */

/*Posições inicial e final da fila declarada com tamanho N+1 pois inclui a cadeira do barbeiro*/
int inicioFila = 0, fimFila = 0, fila[N + 1];
int qtdClientesEsperando = 0;   /*Quantidade de clientes esperando para ser atendido*/
int fimDoExpediente = 1;        /*Flag que define quando todos os clientes foram atendidos. fimDoExpediente = 1 - não atendeu todos os clientes --> fimDoExpediente =  0 - atendeu todos os clientes*/

void *cliente(void *ptr){       /*Função Cliente que recebe como parâmetro o id da thread*/
    int id = *(int *) ptr;      /*Faz o casting do parâmetro recebido de ponteiro de void para inteiro*/
    srand(time(NULL));   

    /*Bloqueia o semaforo mutex*/
    sem_wait(&mutex);           /*Seção crítica de mutex*/
    if(qtdClientesEsperando < N + 1){   /*Se a quantidade de clientes esperando  for menor do que o número de cadeiras*/
        if(qtdClientesEsperando == 0){  /*Caso não tenho nenhum cliente na barbearia, o cliente acorda o barbeiro*/
            printf("Cliente %d acorda o barbeiro e começa a ser atendido \n", id);
        }else                           /*Se já houver um cliente sendo atendido, o cliente que acabou de chegar espera a sua vez*/
            printf("Cliente %d entra na sala de espera \n", id);

        /*Bloqueia o semáforo filaDeEspera*/
        sem_wait(&filaDeEspera);
        fila[fimFila] = id;                 /*O final da fila recebe o id da última thread que chegou*/
        fimFila = (fimFila + 1) % (N + 1);  /*Atualiza o valor do final da fila, podendo ter no máximo N+1 clientes, um sendo atendido e os outros esperando para ser atendidos*/
        qtdClientesEsperando++;             /*Incrementa a variável que guarda a quantidade de clientes que estão esperando*/
        sem_post(&barbeiroSem);             /*Desbloqueia o semáforo barbeiroSem para que o barbeiro possa começar a atender os clientes*/
        sem_post(&filaDeEspera);            /*Libera o semáforo filaDeEspera quando o cliente terminar de ser atendido*/
    }else{  
        /*Caso a quantidade de clientes seja maior do que N+1 então o cliente vai embora*/
        printf("Todas as cadeiras estavam ocupadas, o cliente %d foi embora.\n", id);
    }
    sem_post(&mutex);                       /*Libera o mutex depois que o cliente foi atendido ou foi embora*/
    pthread_exit(0);                        /*Termina a execução de uma thread cliente*/
}

void cortarCabelo(int cliente){             /*Função que simula o barbeiro cortando o cabelo e recebe como parâmetro o id do ciente*/
    sleep(rand() % 2 + 1);                  /*Um sleep aleatório é executado para simular o o tempo de terminar o cabelo*/
    printf("O barbeiro terminou de cortar o cabelo do cliente %d \n", cliente);
}

void *barbeiro(void *ptr){                  /*Função do barbeiro, que recebe NULL como parâmetro*/
    while(1){                               /*Executa até que a flag fimDoExpediente seja igual a zero*/
        sem_wait(&barbeiroSem);             /*Bloqueia o semáforo do barbeiro*/
        if(qtdClientesEsperando > 0){       /*Se houver algum cliente esperando*/
            sem_wait(&filaDeEspera);        /*Bloqueia o semáforo filaDeEspera para que seja possível atender o cliente*/
            int cliente = fila[inicioFila];             /*A variável cliente recebe o id do cliente que está no início da fila, ou seja, o cliente que será atendido*/
            inicioFila = (inicioFila + 1) % (N + 1);    /*Atualiza a posição inicial da fila*/
            cortarCabelo(cliente);                      /*Chama a função que simula o barbeiro cortando cabelo, mandando como parâmetro o id do cliente que será atendido*/
            qtdClientesEsperando--;                     /*Decrementa a variável clienteEsperando*/
            printf("Quantidade de cliente esperando é %d \n", qtdClientesEsperando);
            sem_post(&filaDeEspera);                    /*Libera o semáforo filaDeEspera para que o próximo cliente possa ser atendido*/
            if(qtdClientesEsperando == 0){              /*Se não houver nenhum cliente esperando para ser atendido, o barbeiro volta a dormir*/
                printf("Não há clientes para ser atendido, barbeiro volta a dormir \n");
                if(fimDoExpediente == 0){               /*Se a flag fimDoExpediente for igual a 0 , quer dizer que todos os clientes já foram atendidos*/
                    /*O barbeiro vai embora*/
                    printf("O expediente chegou ao fim. O barbeiro foi embora\n");
                    pthread_exit(0);                    /*Términa a execução da thread Barbeiro*/
                }
            }else{                      /*Se ainda houver clientes esperando, o barbeiro atende o próximo cliente*/
                printf("Cliente %d começa a ser atendido pelo barbeiro  \n", fila[inicioFila]);
            }
        }else{                          /*O barbeiro começa a dormindo pois a quantidade de clientes esperando é igual a zero */
            printf("Barbeiro dormindo\n");
        }
    }
}


int main(){
    pthread_t threadBarbeiro;       /*Uma thread Barbeiro é criada*/
    pthread_t thread[K];            /*Um vetor de thread Clientes , com tamanho igual a K é criado*/
    srand(time(NULL));

    /* Inicia os semáforos */

    sem_init(&mutex, 0, 1);         /* Inicializa o semáforo binário mutex como 1 */
                                 
    sem_init(&filaDeEspera, 0, K);  /* Inicializa o semáforo filaDeEspera - o semaforo possui o valor de K que simboliza o tamanho da sala de espera */
                                    
    sem_init(&barbeiroSem, 0, 1);   /* Inicializa o semáforo binário barbeiroSem como 1 */
                                   

    /* criar as threads */
        /*Cria a thread Barbeiro*/
    pthread_create(&threadBarbeiro, NULL, (void *) &barbeiro, NULL);
        /*Cria K threads Clientes*/
    for (int i=0; i < K; i++) {
        sleep(rand() % 1 + 1);      /*Faz um sleep aleatório , de no máximo dois segundos*/
        pthread_create (&thread[i], NULL, (void *) &cliente, (void *) &i);
    }
        /*Espera a junção de todas as threads Clientes */
    for (int i=0; i < K; i++) {
        pthread_join(thread[i], NULL);
    }
        /*Depois que todas as threads forem executadas, a flag fimDoExpediente é definida como 0*/
    fimDoExpediente = 0;
        /*Espera a thread Barbeiro terminar de executar*/
    pthread_join(threadBarbeiro, NULL);

    /*Destrói todos os semáforos criados*/
    sem_destroy(&mutex);
    sem_destroy(&filaDeEspera);
    sem_destroy(&barbeiroSem);

return 0;
} 