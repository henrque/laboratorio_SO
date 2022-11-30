/*
Descrição: O código recebe cria um prompt para o usuário enviar comandos do shell do sistema, ao receber
           um comando é criado um processo filho para a execução do comando após a finalização do processo 
           e retornado a tela do prompt, caso o comando seja executado em segundo plano através do símbolo "&"
           o usuario retorna para a tela do prompt podendo executar outros comandos enquando é executado o 
           comando em segundo plano.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 09/03/2021
*/

// Execução dos passos que devem ser executados após receber o comando
// 1. Verificar se o tamanho não é nulo
// 2. Separar: Separar e quebrar o comando em palavras individuais e strings
// 3. Checar por caracteres especiais (Segundo plano)
// 4. Checar se comandos integrados são solicitados
// 6. Criar o fork() um filho e chamando o execvp
// 7. Perguntar pelo pŕoximo input

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAXCOM 30 //tamanho máximo do comando

int executa_Comando(char ComandoString[MAXCOM]); //executa e faz o parser do comando recebido

int executa_Comando(char ComandoString[MAXCOM]){
    //Comando não foi feito o parser
    char* Args[MAXCOM]; // Representa cada argumento da linha de comando
    char* token; // O token guarda uma parte do comando de cada vez
    int proc_segundo_plano = 1; //uma flag para verificar se o comando está sendo executado em segundo plano
    pid_t pid;  //guarda o pid do processo 
    int status; //variavel para verificar o status dos processos filhos

    token = strtok(ComandoString, " "); //separa o primeiro argumento do comando
    Args[0] = token;    //o argumento vai para a posição inicial de Args
    
    int i=1; //guarda o valor das posições de Args
    do{
        token = strtok('\0', " "); /*a pesquisa começa do inicio da ponteiro anterior,
                                                    procurando por espaços em branco*/
            if(token != NULL){      //Verifica se o token já não acabou de percorrer todos os argumentos
                if(strcmp(token, "&") == 0){    //Compara os argumentos com "&"
                    proc_segundo_plano = 0;     //Caso não encontre, deixa a flag para execução em segundo plano como zero
                }
                else{
                    Args[i] = token;            //Os argumentos separados são guardados em diferentes posições de Args
                    i++;                        //incrementa a posição após a inserção
                }
            }
    }while(token);      //O loop continua até o token percorrer todos os argumentos

    Args[i] = token;    //A última posição recebe NULL

    pid = fork();       //Cria o processo filho

    if(!pid){           //Caso seja o processo filho
        if(execvp(Args[0], Args) != -1){    //Verifica se o comando existe
            execvp(Args[0], Args);          //Executa o comando
        }
        else{       //Se o comando não existir
            printf("Commando %s não encontrado \n", Args[0]);
            return 0;
        }
    }
    else{
        /*o pai espera o processo filho acabar, e os processos são executados
                de modo concorrente*/
        if(proc_segundo_plano){
            wait(NULL);     
        }                                   
    
    }
return 0;
}


int main(){
    char ComandoString[MAXCOM]; //variavel que recebe o comando inteiro
    int Cmd_rodando = 1; //flag que indica quando encerrar o programa
    int len;
    
    while(Cmd_rodando){     //loop para continuar rodando
        printf("Dir >");
        fflush(stdout);

        fgets(ComandoString, MAXCOM, stdin); //pega o comando digitado
        len = strlen(ComandoString); //Tamanho do comando
        
        if(ComandoString[len-1] == '\n'){ //retira o '\n' do final da string e substitui por '\0'
            ComandoString[len-1] = '\0';
        }               
                            //Compara o comando exit com o comando digitado
            if(strcmp(&ComandoString[0], "exit") == 0){ 
                printf("Exiting now...");   
                Cmd_rodando = 0;        //Muda a flag para indicar que o programa deve encerrar
            }
            else{       
                    executa_Comando(ComandoString); //Envia o comando que será executado
            }

    }
    return 0;
}
