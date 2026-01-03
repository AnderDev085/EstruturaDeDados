//
// Created by gmllb on 13/12/2025.
//

#include <stdio.h>
#include "pet.h"
#include <stdlib.h>
#include <string.h>

void inserir_pet(NoPet **inicio, Pet novoPet) {
    NoPet *aux = (NoPet*)malloc(sizeof(NoPet));
    if (aux == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }
    aux->dados = novoPet;
    aux->prox = NULL;
    aux->ant = NULL;

    if ((*inicio) == NULL) {
        (*inicio) = aux;
    } else {
        NoPet *aux2 = *inicio;
        while (aux2->prox != NULL) {
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
        aux->ant = aux2;
    }
}

int remover_pet(NoPet **inicio, int codigo_alvo) {
    NoPet *aux = *inicio;
    while (aux && aux->dados.codigo != codigo_alvo) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        return 0;
    }

    if (aux->ant == NULL) {
        *inicio = aux->prox;
    } else {
        aux->ant->prox = aux->prox;
    }

    if (aux->prox != NULL) {
        aux->prox->ant = aux->ant;
    }
    free(aux);
    return 1;
}

NoPet *buscar_pet(NoPet *inicio, int codigo_alvo) {
    NoPet *aux = inicio;
    while (aux) {
        if (aux->dados.codigo == codigo_alvo) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void salvar_arquivo_pet(NoPet *inicio) {
    FILE *arq = fopen("pet.bin", "wb");
    if (!arq) {
        printf("Erro ao abrir arquivo");
        return;
    }

    NoPet *aux = inicio;
    while (aux != NULL) {
        fwrite(&aux->dados, sizeof(Pet), 1, arq);
        aux = aux->prox;
    }

    fclose(arq);
}

void carregar_arquivo_pet(NoPet **inicio) {
    FILE *arq = fopen("pet.bin", "rb");
    if (!arq) {
        return;
    }

    Pet temp;
    while (fread(&temp, sizeof(Pet), 1, arq) == 1) {
        inserir_pet(inicio, temp);
    }
    fclose(arq);
}


