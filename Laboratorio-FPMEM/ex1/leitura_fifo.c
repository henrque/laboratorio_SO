/*
Exercício: Faça um programa que lê strings digitadas pelo usuário e envia para outro programa que recebe
essas strings e exibe na tela: a string, o tamanho, o número de consoantes, o número de vogais e o
número de espaços.
leitura_fifo.c recebe a os dados enviados pelo outro programa e imprime
 */

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SERVER_FIFO "/tmp/serverfifo"

int main (int argc, char **argv)
{
    int fd, bytes_read;
    char buf [1024];

    /* cria um FIFO se inexistente */
    if ((mkfifo (SERVER_FIFO, 0664) == -1) && (errno != EEXIST)) {
        perror ("mkfifo");
        exit (1);
    }

    /* abre um FIFO */
    if ((fd = open (SERVER_FIFO, O_RDONLY)) == -1)
        perror ("open");


     while (1) {
         /* lê mensagem do FIFO */
         memset (buf, '\0', sizeof (buf));
         if ((bytes_read = read (fd, buf, sizeof (buf))) == -1)
             perror ("read");
         
         if (bytes_read == 0) {
             printf("-- None data...close and reopen fifo --\n");
             close(fd);
             fd = open (SERVER_FIFO, O_RDONLY);
             continue;
         }
 
        /* imprime o que foi recebido */
         if (bytes_read > 0) {
            printf("Recebido: %s\n", buf);
            
        }
     }

     if (close (fd) == -1)
        perror ("close");
         
}
