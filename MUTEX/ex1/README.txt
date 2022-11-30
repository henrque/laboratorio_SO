Descrição:  Descrição: Neste programa 3 threads são criadas, e todas competem para somar individualmente cada linha da matriz, somando cada linha em outra variável que 
        representa a soma total de todas as linhas da matrix.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação: 05/04/2021
Data de atualização: 07/04/2021

Compilação: Para compilar o código, esteja na pasta "ex1" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Execute o programa com o comando "./ex01" ao executar serão criadas 3 threads que realizarão a soma da matriz cada thread irá somar uma linha da matriz e exibir
	 na tela qual o id da thread e em qual linha ela está executando após todas as threads terminarem de somar toda a matriz será exibido na tela o resultado da soma.


Bibliotecas: unistd.h - Fornece acesso à API do sistema operacional POSIX.
	     sched.h - Permite o uso do comando "sched_yield" para a thread liberar o processador para outra thread utilizar.
	     phtread.h - Fornece acesso a manipulação de threads.
	     matriz.c - Fornece funções basicas de manipulação de matriz