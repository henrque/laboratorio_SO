/*
Exercício: Faça um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços.
escrita_fifo.c recebe strings do usuário, realiza as operações e envia ao outro programa
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#define SERVER_FIFO "/tmp/serverfifo"
#define N 10 /* Número de strings que podem ser enviadas */

char buf[1024];

/* declaração da função flush para limpar entradas do teclado */
void flush_in()
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF && ch != '\n'){}
}

/* declaração da função de contagem de vogais */
int vogais(char *frase){
    int cont = 0;
    char carac;
    char vog[5] = {'a','e','i','o','u'};
    for(int i=0; i<strlen(frase); i++){
        carac = tolower(frase[i]);
        for(int j=0; j<5; j++){
            if(carac == vog[j]) cont++;
        }
    }
    return cont;
}

/* declaração da função de contagem de consoantes */
int consoantes(char *frase){
    int cont = 0;
    char carac;
    char conso[22] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z','ç'};
    for(int i=0; i<strlen(frase); i++){
        carac = tolower(frase[i]);
        for(int j=0; j<22; j++){
            if(carac == conso[j]) cont++;
        }
    }
    return cont;
}

/* declaração da função de contagem de espaços */
int espacos(char *frase){
    int cont = 0;
    for(int i=0; i<strlen(frase); i++){
        if(frase[i] == ' '){
            cont++;
        }
    }
    return cont;
}

/* função principal */
int main(int argc, char **argv)
{
    int fd_server;
    char buff[512];

    /* abre o servidor do fifo */
    if ((fd_server = open(SERVER_FIFO, O_WRONLY)) == -1){
        perror("open: server fifo");
        return 1;
    }

    /* cria uma mensagem */
    int value = 0;
    while (value < N){
        value++;

        printf("Enviar: ");
        /* recebe do usuário a string a ser enviada */
        scanf("%[^\n]c", buff);

        /* realização das operações na string */
        sprintf(buf,"%s\n%s%ld\n%s%d\n%s%d\n%s%d\n", buff, "Tamanho: ", strlen(buff), "Nº de consoantes: ",
        consoantes(buff), "Nº de vogais: ", vogais(buff), "Nº de espaços: ", espacos(buff));

        /* limpa o teclado */
        flush_in();

        /* imprime o buffer */
        printf("Recebido: %s\n\n", buf);

        /* envia mensagem para o fifo */
        write(fd_server, buf, strlen(buf));
    }

    if (close(fd_server) == -1){
        perror("close");
        return 2;
    }

    return 0;
}