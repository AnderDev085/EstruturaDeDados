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



int ler_linha(FILE *f, no_comando **fila_comando) {
    int c;
    comando comando;
    comando.ordem[0] = '\0';
    int i = 0;

    while ((c = fgetc(f)) != EOF) {
        comando.ordem[i++] = c;

        if (c == ';') {              // terminou um comando
            comando.ordem[i] = '\0'; // finaliza string
            push_fila_de_comando(fila_comando, comando);  // adiciona o comando na fila de comando   
            return 1;                // comando lido
        }
    }


    return 0;
}