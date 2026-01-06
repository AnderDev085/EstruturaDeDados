#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comando.h"

void iniciar_fila_de_comando(no_comando **fila) {
    *fila = NULL;
}

void adicionar_fila_de_comando(no_comando **fila, no_comando comando){
    no_comando *aux = malloc(sizeof(no_comando));
    if(aux == NULL) {
        printf("Erro ao alocar memoria\n");
        return;
    }
    strcpy(aux->ordem, comando.ordem);
    aux->prox = NULL;
    aux->ant = NULL;
    if(*fila == NULL){
        *fila = aux;
    } else {
        (*fila)->prox = aux;
        aux->ant = *fila;
    }
}

void remover_fila_de_comando(no_comando **fila) {
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
        if (caractere == ';') {

            if (strlen(comando_total) > 0) {   // evita comandos vazios
                no_comando comando_novo;
                strcpy(comando_novo.ordem, comando_total);
                adicionar_fila_de_comando(fila_comando, comando_novo);
            }

            memset(comando_total, 0, sizeof(comando_total)); // zera buffer
        }
        else {
            if(caractere != '\n'){
                char tmp[2] = { caractere, '\0' };
                strcat(comando_total, tmp);
            }
        }
    }

    // se o arquivo NÃO terminar com ; ou \n
    if (strlen(comando_total) > 0) {
        no_comando comando_novo;
        strcpy(comando_novo.ordem, comando_total);
        adicionar_fila_de_comando(fila_comando, comando_novo);
    }
}

int validar_comando(no_comando *comando){
    char copia[200];
    strcpy(copia, comando->ordem);

    char *token = strtok(copia, " ");

    if(strcmp(token,"insert")==0){
        return validar_insert(comando->ordem);
    }
    else if(strcmp(token,"update")==0){
        return validar_update(comando->ordem);
    }
    else if(strcmp(token,"delete")==0){
        return validar_delete(comando->ordem);
    }
    else if(strcmp(token,"select")==0){
        return validar_select(comando->ordem);
    }
    else{
        return 0;
    }
}

void validar_fila_comando(no_comando **fila) {

    no_comando *aux = *fila;
    no_comando *nova = NULL;

    while (aux != NULL) {

        no_comando *proximo = aux->prox; 
        int valido = validar_comando(aux);
        if (valido == 1) {
            no_comando comando;
            strcpy(comando.ordem, aux->ordem);
            comando.prox = NULL;
            comando.ant  = NULL;

            adicionar_fila_de_comando(&nova, comando);
            remover_fila_de_comando(fila);
        }
        else{
            remover_fila_de_comando(fila);
        }
        aux = proximo;
    }
    *fila = nova;
}