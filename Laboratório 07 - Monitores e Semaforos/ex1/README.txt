Descrição: No programa ex1 considera-se um arquivo que é acessado para leitura e escrita por diferentes threads de forma concorrente.
	 Se o arquivo estiver sendo lido, diferentes threads podem fazer o acesso simultaneamente. Se o arquivo estiver sendo escrito, nenhuma
	 outra thread pode ler ou escrever no arquivo, isto é, o acesso à escrita deve ser exclusivo. Esse padrão de problema é conhecido como
	 o problema dos leitores-escritores. É implementada uma solução para o problema dos leitores-escritores usando variáveis de condição e
	 mutex do padrão POSIX. A solução que evita a postergação indefinida das threads, isto é, se chegar uma thread para escrita, ela terá
	 preferência sobre as próximas threads leitoras.



Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel

Data de criação: 16/04/2021
Data de atualização: 21/04/2021

Compilação: Para compilar o código, esteja na pasta "ex1" no terminal e digite "make" (tendo a biblioteca make já instalada no sistema e o gcc).

Execução: Execute o programa com o comando "./ex1" ao executar o programa as threads de escrita e as threads de leitura irão começar a exibir
        no terminal os que elas estão fazendo no momento o programa irá executar até que o usuario finaliza o programa.
        É recomendado utilizar "CTRL+C" para interromper sua execução. 

Bibliotecas: 
<pthread.h> - POSIX threads
<semaphore.h> - Semáforos
<sched.h> - Escalonamento
<stdlib.h> - Para uso de srand()
<errno.h> - Para erros
<sys/types.h> - Tipos primitivos
<unistd.h> - Constantes simbólicas