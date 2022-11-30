Descrição: Um programa que soma dois vetores alocados na memoria compartilha a soma é realizado por dois processos filhos que trabalham em partes diferente do vetor para realizar soma, os intervalos em que cada processo irá trabalhar são enviados para o processos filhos pelo processo pai utilizando pipe, o resultado da soma é escrito na memoria compartilhada.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação:   30/03/2021
Data de atualização: 01/04/2021

Compilação: Para compilar o código, esteja na pasta "ex3" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Para executar o programa, estando na pasta "ex3", digite o comando "./ex03" para executar o código. O programa imprimirá os dois vetores gerados aleatoriamente e o resultado da soma deles.

Bibliotecas: unistd.h - Fornece acesso à API do sistema operacional POSIX.
	     time.h - Utilizada para geração de valores aleatórios
	     sys/shm.h - Fornece acesso a serviços de memória compartilhada
	     sys/ipc.h - Fornece acesso a serviços de comunicação de processos
 	     sys/types.h - Utilizado para o PID