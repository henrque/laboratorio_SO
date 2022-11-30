/*
Descrição: O código recebe um comando Linux como parâmetro e então cria um filho para executar o comando Linux
           o processo pai fica em espera até a finalização do processo filho.
Autores: Guilherme Vasco da Silva, Henrique Moura Bini, Juan Felipe da Silva Rangel
Data da criação: 09/03/2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>

void Executar(char comando[50]){
    char* argv[100]; //Representa cada argumento da linha de comando
    pid_t pid;      //Armazena o id do processo
    int status;     //variavel para verificar o status dos processos filhos

   //separar o token
    char* token;

    token = strtok(comando," ");    //separa o token por espaços
    argv[0] = token;                //Recebe o primeiro argumento do comando


    int i=1;                        //guarda o valor das posições de argv

    do{
        token = strtok('\0', " ");  /*a pesquisa começa do inicio da ponteiro anterior,
                                                    procurando por espaços em branco*/

        if(token){                  //Verifica se o token já não acabou de percorrer todos os argumentos
            argv[i] = token;        //Os argumentos separados são guardados em diferentes posições de argv    
            i++;                    //incrementa a posição após a inserção
        }   
    } while(token);                 //O loop continua até o token percorrer todos os argumentos


    argv[i] = token;                //Posição final de argv recebe NULL

    //criar os processos filhos
    pid = fork();

    if(!pid){ //trecho executado pelo filho
        execvp(argv[0], argv);        //Executa o comando
    }
    else{ 
        //Processo pai
        wait(&status);                 //O processo pai espera até que todos os filhos terminem sua execução
    }
    exit(0);
}

int main(){
    char comando[50]; //Uma string que guadará o comando
    int len;    //Tamanho do comando digitado
    //pega o comando e manda como parâmetro para ser executado
    fgets(comando, 50, stdin);
    len = strlen(comando);

        /*retira o '\n' do final da string e substitui por '\0' */
    if(comando[len-1] == '\n'){ 
        comando[len-1] = '\0';
    }   

    Executar(comando);

return 0;
}