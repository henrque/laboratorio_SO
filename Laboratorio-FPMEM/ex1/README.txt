Descrição: Um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação: 28/03/2021
Data de atualização: 01/04/2021

Compilação: Para compilar o código, esteja na pasta "ex1" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Execute primeiro o programa de leitura, utilizando o comando no terminal "./leitura_fifo", em seguida, abra outra aba do terminal e execute o programa de escrita com o comando "./escrita_fifo". Digite a(s) string(s) desejada(s) e pressione Enter para enviar, o resultado será impresso no programa de leitura na outra aba do terminal.

Bibliotecas: unistd.h - Fornece acesso à API do sistema operacional POSIX.
	     sys/stat.h - Utilizada para operações em FIFO
	     fcntl.h - Utilizada para operações em FIFO