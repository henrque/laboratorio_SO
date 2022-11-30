Descrição: Um programa que lê atributos de configuração de inicialização de um arquivo e, ao receber o signal 1 (SIGHUP), refaz a leitura desse arquivo e modifica as variáveis internas. Para provar que funciona, faça um menu com a opção para imprimir os atributos carregados na leitura.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação: 31/03/2021
Data de atualização: 01/04/2021

Compilação: Para compilar o código, esteja na pasta "ex2" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Execute o programa com o comando "./ex02", com o programa iniciado, aperte 1 para ver os valores das variáveis internas do arquivo "arquivo.txt" ou 0 para fechar. Utilizando o comando "kill SIGHUP <pid>", onde <pid> é o PID do processo passado pelo programa, é feita a releitura do arquivo. 

Bibliotecas: unistd.h - Fornece acesso à API do sistema operacional POSIX.
	     signal.h - Utilizado para função de SIGHUP