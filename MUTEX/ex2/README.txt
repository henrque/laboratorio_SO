Descrição:  Neste programa o usuário define a quantidade de threads do tipo Ping e Pong, e elas alternam printando "ping" e "pong". Cada thread de cada tipo 
    disputa o processador para printar (Ping se você é um thread do tipo Ping ou Pong, se você é uma thread do tipo Pong). Neste programa Ping e Pong serão printados 
    alternadamente infinitamente, podendo usar "CTRL+C" para interromper sua execução.

Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação: 05/04/2021
Data de atualização: 07/04/2021

Compilação: Para compilar o código, esteja na pasta "ex2" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Execute o programa com o comando "./ex02" ao executar o programa irá solicitar que o usuario digite o número de threads "ping" e o número de threads "pong" 
	que serão criadas após isso o programa irá exibir na tela Ping Pong de forma alternada até o usuario finalizar o programa. É recomendado utilizar "CTRL+C"
	para interromper sua execução. 


Bibliotecas: unistd.h - Fornece acesso à API do sistema operacional POSIX.
	     sched.h - Permite o uso do comando "sched_yield" para a thread liberar o processador para outra thread utilizar.
	     phtread.h - Fornece acesso a manipulação de threads.
	     