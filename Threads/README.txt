Como compilar: os códigos é compilado através do comando make
Como executar: os códigos são executados através dos comandos: 
./ex1
./ex2
./ex3_a
./ex3_b
As bibliotecas usadas foram:
stdio.h
stdlib.h : utilizado para as funções "srand" "rand"
pthread.h : utilizado para as funções "pthread_create" e "pthread_join" 
time.h : utilizado para as funções "clock" "time"

Exemplos de uso:
1)ex1.c: é possivel alterar o número de threads que serão criadas mudando o valor 
            no DEFINE de "NUM_THREADS" também é possivel alterar o tamanho do vetor
            ao alterar o valor do DEFINE "VETOR_TAM" e para alterar o valor que será 
            buscado é preciso alterar o valor do DEFINE "ELEMENTO_PROCURADO";

2)ex2.c: é possivel alterar o tamanho do vetor mudando o valor no DEFINE de "VETOR_TAM";

3)ex3_a.c: é possivel alterar o número de threads que serão criados mudando o valor
            no DEFINE de "NUM_THREADS" 

4)ex3_b.c: é possivel alterar o número de threads que serão criados mudando o valor
            no DEFINE de "NUM_THREADS" 