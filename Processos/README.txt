Como compilar: os códigos é compilado através do comando make
Como executar: os códigos são executados através dos comandos: 
./arv
./cmd_linux
./vetor_processos
./shell
As bibliotecas usadas foram:
stdio.h
stdlib.h
unistd.h
sys/types.h
sys/wait.h
Exemplos de uso:
1)arv.c: a estrutura da árvore de processos pode ser vista através do comando pstree

2)cmd_linux.c: é possivel utilizar varios comandos linux como por exemplo: "ps aux", "ls"

3)vetor_processos.c: ao executar o código será pedido o número de filhos a ser criado assim
		     como o tamanho do vetor e em seguida será pedido para preencher o vetor
		     com números e então o número que o usuário deseja procurar.

4)shell.c: é possivel utilizar varios comando como por exemplo: "ps aux", "ls", também é possível
	   executar comandos em segundo plano utilizando o símbolo & como por exemplo: "sleep 30 &"
	   para parar o código é possivel utilizar o comando "exit"
