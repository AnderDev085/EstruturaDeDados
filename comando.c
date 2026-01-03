#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comando.h"

void iniciar_fila_de_comando(no_comando **fila) {
    *fila = NULL;
}

void push_fila_de_comando(no_comando **fila, comando comando){
    no_comando *aux = malloc(sizeof(no_comando));
    if(aux == NULL) {
        printf("Erro ao alocar memoria\n");
        return;
    }
    aux->comando = comando;
    aux->prox = NULL;
    aux->ant = NULL;
    if(*fila == NULL){
        *fila = aux;
    } else {
        (*fila)->prox = aux;
        aux->ant = *fila;
    }
}

void pull_fila_de_comando(no_comando **fila) {
    if(*fila == NULL) {
        printf("Fila vazia\n");
        return;
    }
    no_comando *aux = *fila;
    *fila = (*fila)->prox;
    free(aux);
    if(*fila != NULL) {
        (*fila)->ant = NULL;
    }
}



void ler_arquivo(FILE *f, no_comando **fila_comando) {

    int c;
    char comando_total[200] = {0};

    while ((c = fgetc(f)) != EOF) {

        char caractere = (char)c;

        // Separador de comandos
        if (caractere == '\n' || caractere == ';') {

            if (strlen(comando_total) > 0) {   // evita comandos vazios
                comando comando_novo;
                strcpy(comando_novo.ordem, comando_total);
                push_fila_de_comando(fila_comando, comando_novo);
            }

            memset(comando_total, 0, sizeof(comando_total)); // zera buffer
        }
        else {
            char tmp[2] = { caractere, '\0' };
            strcat(comando_total, tmp);
        }
    }

    // se o arquivo NÃO terminar com ; ou \n
    if (strlen(comando_total) > 0) {
        comando comando_novo;
        strcpy(comando_novo.ordem, comando_total);
        push_fila_de_comando(fila_comando, comando_novo);
    }
}
