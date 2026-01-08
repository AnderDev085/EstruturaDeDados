#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipo_pet.h"

void inserir_tipo_pet(NoTipoPet **inicio, TipoPet novoTipoPet) {
    NoTipoPet *aux = (NoTipoPet*)malloc(sizeof(NoTipoPet));
    if (aux == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }
    aux->dados = novoTipoPet;
    aux->prox = NULL;
    aux->ant = NULL;

    if ((*inicio) == NULL) {
        (*inicio) = aux;
    } else {
        NoTipoPet *aux2 = *inicio;
        while (aux2->prox != NULL) {
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
        aux->ant = aux2;
    }
}

int remover_tipo_pet(NoTipoPet **inicio, int codigo_alvo) {
    NoTipoPet *aux = *inicio;
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

NoTipoPet *buscar_tipo_pet(NoTipoPet *inicio, int codigo_alvo) {
    NoTipoPet *aux = inicio;
    while (aux) {
        if (aux->dados.codigo == codigo_alvo) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}


int alterar_tipo_pet(NoTipoPet *inicio, int codigo_alvo, char *descricao) {
    NoTipoPet *no = buscar_tipo_pet(inicio, codigo_alvo);

    if (no == NULL) {
        return 0;
    }


    if (descricao != NULL) {
        strncpy(no->dados.descricao, descricao, 99);
        no->dados.descricao[99] = '\0';
    }

    return 1;
}


int validar_tipo_pet(TipoPet tipoPet) {
    if (tipoPet.codigo <= 0) {
        return 0;
    }

    if (strlen(tipoPet.descricao) == 0) {
        return 0;
    }

    return 1;
}




int codigo_tipo_pet_existe(NoTipoPet *inicio, int codigo) {
    return (buscar_tipo_pet(inicio, codigo) != NULL);
}

NoArvoreTipoPet* inserir_tipo_na_arvore_por_descricao(NoArvoreTipoPet *raiz, TipoPet tipo) {
    if (raiz == NULL) {
        NoArvoreTipoPet *novo = malloc(sizeof(NoArvoreTipoPet));
        if (novo == NULL) {
            printf("Erro ao alocar memória para árvore");
            return NULL;
        }
        novo->dados = tipo;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int comparacao = strcmp(tipo.descricao, raiz->dados.descricao);

    if (comparacao < 0) {
        raiz->esquerda = inserir_tipo_na_arvore_por_descricao(raiz->esquerda, tipo);
    } else {
        raiz->direita = inserir_tipo_na_arvore_por_descricao(raiz->direita, tipo);
    }

    return raiz;
}

NoArvoreTipoPet* construir_arvore_tipo_por_descricao(NoTipoPet *inicio) {
    NoArvoreTipoPet *raiz = NULL;
    NoTipoPet *atual = inicio;

    while (atual != NULL) {
        raiz = inserir_tipo_na_arvore_por_descricao(raiz, atual->dados);
        atual = atual->prox;
    }

    return raiz;
}

void percorrer_em_ordem_tipo(NoArvoreTipoPet *raiz) {
    if (raiz != NULL) {
        percorrer_em_ordem_tipo(raiz->esquerda);
        imprimir_tipo_pet(raiz->dados);
        percorrer_em_ordem_tipo(raiz->direita);
    }
}

void liberar_arvore_tipo(NoArvoreTipoPet *raiz) {
    if (raiz != NULL) {
        liberar_arvore_tipo(raiz->esquerda);
        liberar_arvore_tipo(raiz->direita);
        free(raiz);
    }
}

void listar_tipos_pet_por_descricao(NoTipoPet *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("\n Tipos de Pet Ordenados por Descrição \n");

    NoArvoreTipoPet *arvore = construir_arvore_tipo_por_descricao(inicio);
    percorrer_em_ordem_tipo(arvore);
    liberar_arvore_tipo(arvore);
}



void liberar_lista_tipo_pet(NoTipoPet **inicio) {
    NoTipoPet *aux = *inicio;
    NoTipoPet *temp;

    while (aux != NULL) {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    *inicio = NULL;
}


void imprimir_tipo_pet(TipoPet tipoPet) {
    printf("Código: %d\n", tipoPet.codigo);
    printf("Descrição: %s\n", tipoPet.descricao);
}


void listar_tipos_pet(NoTipoPet *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NoTipoPet *aux = inicio;
    while (aux != NULL) {
        imprimir_tipo_pet(aux->dados);
        aux = aux->prox;
    }
}

void salvar_arquivo_tipo_pet(NoTipoPet *inicio) {
    FILE *arq = fopen("tipo_pet.bin", "wb");
    if (!arq) {
        printf("Erro ao abrir arquivo para escrita\n");
        return;
    }

    NoTipoPet *aux = inicio;
    while (aux != NULL) {
        fwrite(&aux->dados, sizeof(TipoPet), 1, arq);
        aux = aux->prox;
    }

    fclose(arq);
}

void carregar_arquivo_tipo_pet(NoTipoPet **inicio) {
    FILE *arq = fopen("tipo_pet.bin", "rb");
    if (!arq) {
        return;
    }

    TipoPet temp;
    while (fread(&temp, sizeof(TipoPet), 1, arq) == 1) {
        inserir_tipo_pet(inicio, temp);
    }
    fclose(arq);
}