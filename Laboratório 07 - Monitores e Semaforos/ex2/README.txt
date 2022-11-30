Descrição: Neste programa temos o problema de uma barbearia, que consiste de uma sala de espera com N cadeiras e a sala do barbeiro com 1 
	 cadeira de barbearia. Se não há clientes para atender, o barbeiro dorme. Se um cliente entra na barbearia e todas as cadeiras estão
	 ocupadas, então o cliente vai embora. Caso o barbeiro esteja ocupado, mas há cadeiras na sala de espera, o cliente senta em uma cadeira.
	 Caso o barbeiro esteja dormindo, o cliente acorda o barbeiro e é atendido. Esse problema é conhecido como problema da barbearia ou do barbeiro dorminhoco.
	 É implementada uma solução para o problema do barbeiro dorminhoco usando semáforos de forma a ser justo com ordem de chegada dos clientes.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação: 16/04/2021
Data de atualização: 21/04/2021

Compilação: Para compilar o código, esteja na pasta "ex2" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Execute o programa com o comando "./ex2"  ao executar o programa será exibido no terminal as ações que a thread barbeiro e as threads
	clientes estão executando quando não houver mais clientes para ser atendido os barbeiro irá finalizar a sua execução e irá finalizar a 
	execução do programa. 

Bibliotecas: 	<unistd.h>    Constantes simbólicas
 		<sys/types.h> Tipos primitivos
 		<errno.h>     Para erros
		<stdio.h>     Para comandos de entrada e saída
 		<pthread.h>   POSIX threads
		<semaphore.h> Semáforos
 		<stdlib.h>    Para uso de srand()