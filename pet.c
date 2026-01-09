//
// Created by gmllb on 13/12/2025.
//

#include <stdio.h>
#include "pet.h"
#include "validacoes.h"
#include "pessoa.h"
#include "pet.h"
#include "tipo_pet.h"
#include "comando.h"
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

int validar_pet(Pet pet) {
    if (pet.codigo <= 0) {
        return 0;
    }

    if (pet.codigo_pes <= 0) {
        return 0;
    }

    if (strlen(pet.nome) == 0) {
        return 0;
    }

    if (pet.codigo_tipo <= 0) {
        return 0;
    }

    return 1;
}

int codigo_pet_existe(NoPet *inicio, int codigo) {
    return (buscar_pet(inicio, codigo) != NULL);
}

int pessoa_tem_pets(NoPet *inicio, int codigo_pessoa) {
    NoPet *aux = inicio;
    while (aux != NULL) {
        if (aux->dados.codigo_pes == codigo_pessoa) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

NoArvorePet* inserir_pet_na_arvore_por_nome(NoArvorePet *raiz, Pet pet) {
    if (raiz == NULL) {
        NoArvorePet *novo = (NoArvorePet*)malloc(sizeof(NoArvorePet));
        if (novo == NULL) {
            printf("Erro ao alocar memória para árvore\n");
            return NULL;
        }
        novo->dados = pet;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int comparacao = strcmp(pet.nome, raiz->dados.nome);

    if (comparacao < 0) {
        raiz->esquerda = inserir_pet_na_arvore_por_nome(raiz->esquerda, pet);
    } else {
        raiz->direita = inserir_pet_na_arvore_por_nome(raiz->direita, pet);
    }

    return raiz;
}

NoArvorePet* construir_arvore_pet_por_nome(NoPet *inicio) {
    NoArvorePet *raiz = NULL;
    NoPet *atual = inicio;

    while (atual != NULL) {
        raiz = inserir_pet_na_arvore_por_nome(raiz, atual->dados);
        atual = atual->prox;
    }

    return raiz;
}

void percorrer_em_ordem_pet(NoArvorePet *raiz) {
    if (raiz != NULL) {
        percorrer_em_ordem_pet(raiz->esquerda);
        imprimir_pet(raiz->dados);
        percorrer_em_ordem_pet(raiz->direita);
    }
}

void liberar_arvore_pet(NoArvorePet *raiz) {
    if (raiz != NULL) {
        liberar_arvore_pet(raiz->esquerda);
        liberar_arvore_pet(raiz->direita);
        free(raiz);
    }
}

void listar_pets_por_nome(NoPet *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("\n Pets Ordenados por Nome \n");

    NoArvorePet *arvore = construir_arvore_pet_por_nome(inicio);
    percorrer_em_ordem_pet(arvore);
    liberar_arvore_pet(arvore);
}

int alterar_pet(NoPet *inicio, int codigo_alvo, int *codigo_pes, char *nome, int *codigo_tipo) {
    NoPet *no = buscar_pet(inicio, codigo_alvo);

    if (no == NULL) {
        return 0;
    }

    if (codigo_pes != NULL) {
        no->dados.codigo_pes = *codigo_pes;
    }

    if (nome != NULL) {
        strncpy(no->dados.nome, nome, 99);
        no->dados.nome[99] = '\0';
    }

    if (codigo_tipo != NULL) {
        no->dados.codigo_tipo = *codigo_tipo;
    }

    return 1; // Sucesso
}

void imprimir_pet(Pet pet) {
    printf("Código: %d\n", pet.codigo);
    printf("Código Pessoa (Dono): %d\n", pet.codigo_pes);
    printf("Nome: %s\n", pet.nome);
    printf("Código Tipo: %d\n", pet.codigo_tipo);
}

void listar_pets(NoPet *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NoPet *aux = inicio;
    while (aux != NULL) {
        imprimir_pet(aux->dados);
        aux = aux->prox;
    }
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


