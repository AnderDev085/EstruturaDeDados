#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validacoes.h"
#include "pessoa.h"
#include "pet.h"
#include "tipo_pet.h"
#include "comando.h"


void inserir_pessoa(NoPessoa **inicio, valores *valores) {
    Pessoa novaPessoa;
    novaPessoa.codigo = valores->codigo;
    strcpy(novaPessoa.nome,valores->nome);
    strcpy(novaPessoa.fone,valores->fone);
    strcpy(novaPessoa.endereco,valores->endereco);
    strcpy(novaPessoa.data_nascimento,valores->data_nascimento);
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

int remover_pessoa(NoPessoa **inicio, NoPet **listaPets, int codigo_alvo ) {
    NoPessoa *aux = *inicio;
    NoPet *p = *listaPets;
    int verificador = pode_remover_pessoa(aux,p,codigo_alvo);

    if(verificador == 0)return 0;

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


int alterar_pessoa(NoPessoa *inicio, valores *valores) {
    NoPessoa *no = buscar_pessoa(inicio, valores->codigo);

    if (no == NULL) {
        printf("Não existe essa pessoa \n");
        return 0;
    }

    if (valores->nome[0] != '\0') {
        strncpy(no->dados.nome, valores->nome, sizeof(no->dados.nome) - 1);
        no->dados.nome[sizeof(no->dados.nome) - 1] = '\0';
    }

    if (valores->fone[0] != '\0') {
        strncpy(no->dados.fone, valores->fone, sizeof(no->dados.fone) - 1);
        no->dados.fone[sizeof(no->dados.fone) - 1] = '\0';
    }

    if (valores->data_nascimento[0] != '\0') {
        strncpy(no->dados.data_nascimento, valores->data_nascimento,
                sizeof(no->dados.data_nascimento) - 1);
        no->dados.data_nascimento[sizeof(no->dados.data_nascimento) - 1] = '\0';
    }

    if (valores->endereco[0] != '\0') {
        strncpy(no->dados.endereco, valores->endereco,
                sizeof(no->dados.endereco) - 1);
        no->dados.endereco[sizeof(no->dados.endereco) - 1] = '\0';
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

void inserir_pessoa_dados(NoPessoa **inicio, Pessoa pessoa) {
    NoPessoa *novo = malloc(sizeof(NoPessoa));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }

    novo->dados = pessoa;
    novo->prox = NULL;

    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        NoPessoa *aux = *inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void carregar_arquivo_pessoa(NoPessoa **inicio) {
    FILE *arq = fopen("pessoa.bin", "rb");
    if (!arq) {
        return;
    }

    Pessoa temp;

    while (fread(&temp, sizeof(Pessoa), 1, arq) == 1) {
        inserir_pessoa_dados(inicio, temp);
    }
    fclose(arq);

}

void imprimir_pessoa_select(NoPessoa **fila_pessoa, valores *valores) {
    NoPessoa *aux = *fila_pessoa;


    while(aux != NULL){
    if (valores->codigo != 0 && valores->codigo == aux->dados.codigo)
        imprimir_pessoa(aux->dados);

    if (valores->nome[0] != '\0' && strcmp(valores->nome,aux->dados.nome)==0)
        imprimir_pessoa(aux->dados);

    if (valores->fone[0] != '\0' && strcmp(valores->fone,aux->dados.fone)==0)
        imprimir_pessoa(aux->dados);

    if (valores->data_nascimento[0] != '\0' && strcmp(valores->data_nascimento,aux->dados.data_nascimento)==0)
        imprimir_pessoa(aux->dados);

    if (valores->endereco[0] != '\0' && strcmp(valores->endereco,aux->dados.endereco)==0)
        imprimir_pessoa(aux->dados);

        aux = aux->prox;
    }

    printf("------------\n");
}