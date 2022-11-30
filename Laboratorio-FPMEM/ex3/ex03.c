/*
Descrição: Um programa que soma dois vetores alocados na memoria compartilhada. A soma é realizada
    por dois processos filhos que trabalham em partes diferente do vetor para realizar soma,e os
    intervalos em que cada processo irá trabalhar são enviados para os processos filhos pelo processo
    pai utilizando pipe. Já o resultado da soma é escrito na memoria compartilhada.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação:   30/03/2021
Data de atualização: 01/04/2021
*/

 

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/* Tamanho do segmento compartilhado. */
#define MEMCOMP 32 /* espaço para 32 elementos, onde terá 3 vetores de 10 elementos cada, 
                 /* e mais 2 posições para os filhos informarem o término do trabalho  */

int main(){

    pid_t pid;
	int pipe1[2];
	int pipe2[2];

    int buffer1[4];
    int buffer2[4];

	/* Cria um pipe */
	if (pipe(pipe1)) {
		fprintf(stderr, "Falha ao criar o Pipe 1.\n");
		return EXIT_FAILURE;
	}

    /* Cria o pipe 2. */
	if (pipe(pipe2)) {
		fprintf(stderr, "Falha ao criar o Pipe 2.\n");
		return EXIT_FAILURE;
	}

    /* cria os filhos */
    if (pid = fork()) { 
        /* Esse código será executado pelo pai */
        if (pid = fork()) { ; 
            /* aloca memória compartilhada */
            int shmidParent;
            key_t keyParent;
            int *shmParent, *sParent;

            /* Nome do segmento de memória compartilhada "5678". */
            keyParent = 5678;

            /* Cria o segmento compartilhado. */
            if ((shmidParent = shmget(keyParent, MEMCOMP, IPC_CREAT | 0666)) < 0) {
                perror("Error in creation of segment shm (shmget).");
                exit(1);
            }


            /* Acoplamento do segmento criado ao espaço de dados. */
            if ((shmParent = shmat(shmidParent, NULL, 0)) == (int*)-1) {
                perror
                    ("Error in function shmat.");
                exit(1);
            }

            /* Colocando dados para os outros processo lerem. */
            sParent = shmParent;

            int position;
            srand(time(NULL));
            for(position = 0; position < 20; position++) { /* posição 0 a 9: vetor1, posição 10 a 19, vetor 2 */
                sParent[position] = rand()%10;
            }
            

            /*Exibe o conteudo do vetor 1 e 2 */
            printf("Array 1: ");
            for(position = 0; position <= 9; position++) {
                printf("%d ", sParent[position]);
            }
            printf("\n");

            printf("Array 2: ");
            for(position = 10; position <= 19; position++) {
                printf("%d ", sParent[position]);
            }
            printf("\n");

            

            /* escreve no pipe1 o intervalo em que o primeiro filho ira trabalhar */
            close(pipe1[0]);
            buffer1[0] = 0;
            buffer1[1] = 10;
            buffer1[2] = 20;
            buffer1[3] = 5;
            write(pipe1[1], buffer1, sizeof(buffer1));

            /* escreve no pipe2 o intervalo em que o primeiro filho ira trabalhar */
            close(pipe2[0]);
            buffer2[0] = 5;
            buffer2[1] = 15;
            buffer2[2] = 25;
            buffer2[3] = 5;
            write(pipe2[1], buffer2, sizeof(buffer2));

            /* Aguarda o termino da execução dos filhos*/
            while ((shmParent[30] != -1) && (shmParent[31] != -1))
                sleep(1);
            
            /* Exibe o resultado da soma dos vetores */
            printf("Result array: ");
            int j;
            for (j = 20; j <= 29; j++){
                printf("%d ", shmParent[j]);
            }
            printf("\n");

            /* Desacoplamento da região de memória compartilhada. */
            if (shmdt(shmParent) == -1) {
                perror("Error in function shmdt.");
                exit(1);
            }
            /* Destruição do segmento */
            if (shmctl(shmidParent, IPC_RMID, 0) == -1){
                perror("Error in function shmctl.") ;
                exit(1) ;
            }
            wait(NULL);
            return EXIT_SUCCESS;
        } else { 
            /* Esse código será executado pelo filho 2 */

            close(pipe2[1]);
            /*Espera até receber algo no pipe*/
            read(pipe2[0], buffer2, sizeof(buffer2));
            
            int c2IniV1 = buffer2[0]; /* intervalos de acesso aos vetores */
            int c2IniV2 = buffer2[1];
            int c2IniV3 = buffer2[2];
            int c2gap = buffer2[3];

            /* Acessa a memória compartilhada */
            int shmIdChild2;
            key_t keyFilho2;
            int *shmChild2, *sChild2;

            /* É preciso pegar o segmento nomeado como "5678", criado pelo servidor. */
            keyFilho2 = 5678;

            /* Localizando o segmento (locate). */
            if ((shmIdChild2 = shmget(keyFilho2, MEMCOMP, 0666)) < 0) {
                perror("Error in function shmget.");
                exit(1);
            }

            /* Acoplamento do segmento ao espaço de endereços de dados. */
            if ((shmChild2 = shmat(shmIdChild2, NULL, 0)) == (int*)-1) {
                perror("Error in function shmat.");
                exit(1);
            }

            /* Lendo o que o servidor colocou na região de memória. */
            sChild2 = shmChild2;
            
            int c2i1 = c2IniV1; /* inicio do vetor 1 */
            int c2i2 = c2IniV2; /* inicio do vetor 2 */
            int c2i3 = c2IniV3; /* inicio do vetor 3 */
            /* Realiza a soma dos vetores 1 e 2 e armazena o resultando no vetor 3*/
            while(c2i1 < c2IniV1+c2gap) {
                shmChild2[c2i3] = sChild2[c2i1] + sChild2[c2i2];
                c2i1++;
                c2i2++;
                c2i3++;
            }

            /* Sinaliza que acabou a execução  */
            shmChild2[31] = -1;

            /* Elimina a região de memória compartilhada. */
            if (shmdt(shmChild2) == -1) {
                perror("Error in function shmdt.");
                exit(1);
            }

            fflush(stdout);
            return EXIT_SUCCESS;  
        }
    } else {
        /* Esse código será executado pelo filho 1 */
        
        close(pipe1[1]);
        /*Espera até receber algo no pipe*/
        read(pipe1[0], buffer1, sizeof(buffer1));
        
        int c1IniV1 = buffer1[0]; /* intervalos de acesso aos vetores */
        int c1IniV2 = buffer1[1];
        int c1IniV3 = buffer1[2];
        int c1gap = buffer1[3];

        /* Acessa a memória compartilhada */
        int shmIdChild1;
        key_t keyChild1;
        int *shmChild1, *sChild1;

        /* É preciso pegar o segmento nomeado como "5678", criado pelo servidor. */
        keyChild1 = 5678;

        /* Localizando o segmento (locate). */
        if ((shmIdChild1 = shmget(keyChild1, MEMCOMP, 0666)) < 0) {
            perror("Error in function shmget.");
            exit(1);
        }

        /* Acoplamento do segmento ao espaço de endereços de dados. */
        if ((shmChild1 = shmat(shmIdChild1, NULL, 0)) == (int*)-1) {
            perror("Error in function shmat.");
            exit(1);
        }

        /* Lendo o que o servidor colocou na região de memória. */
        sChild1 = shmChild1;
        
        int c1i1 = c1IniV1; /* inicio do vetor 1 */
        int c1i2 = c1IniV2; /* inicio do vetor 2 */
        int c1i3 = c1IniV3; /* inicio do vetor 3 */
        /* Realiza a soma dos vetores 1 e 2 e armazena o resultando no vetor 3*/
        while(c1i1 < c1IniV1+c1gap) {
            shmChild1[c1i3] = sChild1[c1i1] + sChild1[c1i2];
            c1i1++;
            c1i2++;
            c1i3++;
        }

        /* Sinaliza que acabou a execução  */
        shmChild1[30] = -1;

        /* Elimina a região de memória compartilhada. */
        if (shmdt(shmChild1) == -1) {
            perror("Error in function shmdt.");
            exit(1);
        }

        fflush(stdout);
        return EXIT_SUCCESS;
    }
}