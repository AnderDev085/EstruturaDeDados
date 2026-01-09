#ifndef PESSOA_H
#define PESSOA_H

#include "validacoes.h"
#include "pet.h"
#include "tipo_pet.h"
#include "comando.h"

typedef struct {
    int codigo;
    char nome[100];
    char fone[100];
    char data_nascimento[11];
    char endereco[100];
}Pessoa;

typedef struct NoPessoa{
    Pessoa dados;
    struct NoPessoa *prox;
    struct NoPessoa *ant;
}NoPessoa;

typedef struct NoArvorePessoa {
    Pessoa dados;
    struct NoArvorePessoa *direita;
    struct NoArvorePessoa *esquerda;
}NoArvorePessoa;

void inserir_pessoa(NoPessoa **inicio,valores *valores);

int remover_pessoa(NoPessoa **inicio, NoPet **ListaPets,int codigo_alvo);

NoPessoa *buscar_pessoa(NoPessoa *inicio,int codigo_alvo);

int alterar_pessoa(NoPessoa *inicio, valores *valores);

void liberar_lista_pessoa(NoPessoa **inicio);

int validar_pessoa(Pessoa pessoa);

void imprimir_pessoa(Pessoa pessoa);

void listar_pessoas(NoPessoa *inicio);

void listar_pessoas_por_nome(NoPessoa *inicio);

NoArvorePessoa* construir_arvore_por_nome(NoPessoa *inicio);

NoArvorePessoa* inserir_na_arvore_por_nome(NoArvorePessoa *raiz, Pessoa pessoa);

void percorrer_em_ordem_pessoa(NoArvorePessoa *raiz);

void liberar_arvore_pessoa(NoArvorePessoa *raiz);

int codigo_pessoa_existe(NoPessoa *inicio, int codigo);


void salvar_arquivo_pessoa(NoPessoa *inicio);

void carregar_arquivo_pessoa(NoPessoa **inicio);

void imprimir_pessoa_select(NoPessoa **fila_pessoa, valores *valores);

void inserir_pessoa_dados(NoPessoa **inicio, Pessoa pessoa);







#endif