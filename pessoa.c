//
// Created by gmllb on 13/12/2025.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

void inserir_pessoa(NoPessoa **inicio, Pessoa novaPessoa) {
    NoPessoa *aux = (NoPessoa*)malloc(sizeof(NoPessoa));
    if (aux == NULL) {
        printf("Erro ao alocar memória");
        return;
    }
    aux->dados = novaPessoa;
    aux->prox = NULL;
    aux->ant = NULL;

    if ((*inicio) == NULL) {
        (*inicio) = aux;
        (*inicio)->prox = NULL;
    }else {
        NoPessoa *aux2 = *inicio;
        while (aux2->prox != NULL) {
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
        aux->ant = aux2;
    }

}

int remover_pessoa(NoPessoa **inicio,int codigo_alvo) {
    NoPessoa *aux = *inicio;
    while (aux && aux->dados.codigo != codigo_alvo) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        return 0;
    }

    if (aux->ant == NULL) {
        *inicio = aux->prox;
    }else {
        aux->ant->prox = aux->prox;
    }

    if (aux->prox != NULL) {
        aux->prox->ant = aux->ant;
    }
    free(aux);
    return 1;

}

NoPessoa *buscar_pessoa(NoPessoa **inicio,int codigo_alvo) {
    NoPessoa *aux = *inicio;
    while (aux) {
        if (aux->dados.codigo == codigo_alvo) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

int alterar_pessoa(NoPessoa **inicio,int codigo_alvo,char nome[100],char fone[100], char data_de_nascimento[11],char endereco[100]) {
    NoPessoa *aux = buscar_pessoa(inicio,codigo_alvo);

    if (aux == NULL) {
        printf(" Pessoa nao existe!");
        return 0;
    }

    strcpy(aux->dados.nome , nome);
    strcpy(aux->dados.fone , fone);
    return 1;

}







void salvar_arquivo_pessoa(NoPessoa *inicio) {
    FILE *arq = fopen("pessoa.bin", "wb");
    if (!arq) {
        return;
    }

    NoPessoa *aux = inicio;
    while (aux != NULL) {
        fwrite(&aux->dados,sizeof(Pessoa),1,arq);
        aux = aux->prox;
    }

    fclose(arq);
}

void carregar_arquivo_pessoa(NoPessoa **inicio) {
    FILE *arq = fopen("pessoa.bin", "rb");
    if (!arq) {
        printf("Erro ao abrir arquivo");
        return;
    }

    Pessoa temp;

    while (fread(&temp, sizeof(Pessoa), 1, arq) == 1) {
        inserir_pessoa(inicio, temp);
    }
    fclose(arq);

}