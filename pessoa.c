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

NoPessoa *buscar_pessoa(NoPessoa *inicio,int codigo_alvo) {
    NoPessoa *aux = inicio;
    while (aux) {
        if (aux->dados.codigo == codigo_alvo) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}



int alterar_pessoa(NoPessoa *inicio, int codigo_alvo, char *nome, char *fone, char *data_nascimento, char *endereco) {
    NoPessoa *no = buscar_pessoa(inicio, codigo_alvo);

    if (no == NULL) {
        return 0;
    }


    if (nome != NULL) {
        strncpy(no->dados.nome, nome, 99);
        no->dados.nome[99] = '\0';
    }

    if (fone != NULL) {
        strncpy(no->dados.fone, fone, 99);
        no->dados.fone[99] = '\0';
    }

    if (data_nascimento != NULL) {
        strncpy(no->dados.data_nascimento, data_nascimento, 10);
        no->dados.data_nascimento[10] = '\0';
    }

    if (endereco != NULL) {
        strncpy(no->dados.endereco, endereco, 99);
        no->dados.endereco[99] = '\0';
    }

    return 1;
}

int validar_pessoa(Pessoa pessoa) {
    if (pessoa.codigo <= 0) {
        return 0;
    }

    if (strlen(pessoa.nome) == 0) {
        return 0;
    }

    if (strlen(pessoa.fone) == 0) {
        return 0;
    }

    if (strlen(pessoa.data_nascimento) == 0) {
        return 0;
    }

    if (strlen(pessoa.endereco) == 0) {
        return 0;
    }

    return 1;
}

int codigo_pessoa_existe(NoPessoa *inicio, int codigo) {
    return (buscar_pessoa(inicio, codigo) != NULL);
}

void liberar_lista_pessoa(NoPessoa **inicio) {
    NoPessoa *aux = *inicio;
    NoPessoa *temp;

    while (aux != NULL) {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    *inicio = NULL;
}

void imprimir_pessoa(Pessoa pessoa) {
    printf("Código: %d\n", pessoa.codigo);
    printf("Nome: %s\n", pessoa.nome);
    printf("Fone: %s\n", pessoa.fone);
    printf("Data Nascimento: %s\n", pessoa.data_nascimento);
    printf("Endereço: %s\n", pessoa.endereco);
}

NoArvorePessoa* construir_arvore_por_nome(NoPessoa *inicio) {
    NoArvorePessoa *raiz = NULL;
    NoPessoa *atual = inicio;

    while (atual != NULL) {
        raiz = inserir_na_arvore_por_nome(raiz, atual->dados);
        atual = atual->prox;
    }

    return raiz;
}

NoArvorePessoa* inserir_na_arvore_por_nome(NoArvorePessoa *raiz, Pessoa pessoa) {
    if (raiz == NULL) {
        NoArvorePessoa *novo = malloc(sizeof(NoArvorePessoa));
        if (novo == NULL) {
            printf("Erro ao alocar memória para a árvore\n");
            return NULL;
        }

        novo->dados = pessoa;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    int comparacao = strcmp(pessoa.nome, raiz->dados.nome);

    if (comparacao < 0) {
        raiz->esquerda = inserir_na_arvore_por_nome(raiz->esquerda, pessoa);
    } else {
        raiz->direita = inserir_na_arvore_por_nome(raiz->direita, pessoa);
    }

    return raiz;
}

void percorrer_em_ordem_pessoa(NoArvorePessoa *raiz) {
    if (raiz != NULL) {
        percorrer_em_ordem_pessoa(raiz->esquerda);
        imprimir_pessoa(raiz->dados);
        percorrer_em_ordem_pessoa(raiz->direita);
    }
}

void listar_pessoas_por_nome(NoPessoa *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("\n Pessoas Ordenadas por Nome \n");

    NoArvorePessoa *arvore = construir_arvore_por_nome(inicio);

    percorrer_em_ordem_pessoa(arvore);

    liberar_arvore_pessoa(arvore);
}

void liberar_arvore_pessoa(NoArvorePessoa *raiz) {
    if (raiz != NULL) {
        liberar_arvore_pessoa(raiz->esquerda);
        liberar_arvore_pessoa(raiz->direita);
        free(raiz);
    }
}


void listar_pessoas(NoPessoa *inicio) {
    if (inicio == NULL) {
        printf("Lista vazia\n");
        return;
    }

    NoPessoa *aux = inicio;
    while (aux != NULL) {
        imprimir_pessoa(aux->dados);
        aux = aux->prox;
    }
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
        return;
    }

    Pessoa temp;

    while (fread(&temp, sizeof(Pessoa), 1, arq) == 1) {
        inserir_pessoa(inicio, temp);
    }
    fclose(arq);

}