#ifndef TIPO_PET_H
#define TIPO_PET_H

#include "validacoes.h"
#include "pessoa.h"
#include "pet.h"
#include "comando.h"

typedef struct TipoPet{
    int codigo;
    char descricao[100];
}TipoPet;

typedef struct NoTipoPet {
    TipoPet dados;
    struct NoTipoPet *prox;
    struct NoTipoPet *ant;
}NoTipoPet;

typedef struct NoArvoreTipoPet {
    TipoPet dados;
    struct NoArvoreTipoPet *direita;
    struct NoArvoreTipoPet *esquerda;
}NoArvoreTipoPet;

void inserir_tipo_pet(NoTipoPet **inicio, TipoPet novoTipoPet);

int remover_tipo_pet(NoTipoPet **inicio, int codigo_alvo);

NoTipoPet *buscar_tipo_pet(NoTipoPet *inicio, int codigo_alvo);

int alterar_tipo_pet(NoTipoPet *inicio, int codigo_alvo, char *descricao);

void imprimir_tipo_pet(TipoPet tipoPet);

void listar_tipos_pet_por_descricao(NoTipoPet *inicio);

NoArvoreTipoPet* construir_arvore_tipo_por_descricao(NoTipoPet *inicio);

NoArvoreTipoPet* inserir_tipo_na_arvore_por_descricao(NoArvoreTipoPet *raiz, TipoPet tipo);

void percorrer_em_ordem_tipo(NoArvoreTipoPet *raiz);

void liberar_arvore_tipo(NoArvoreTipoPet *raiz);

void salvar_arquivo_tipo_pet(NoTipoPet *inicio);

void carregar_arquivo_tipo_pet(NoTipoPet **inicio);

int validar_tipo_pet(TipoPet tipoPet);

int codigo_tipo_pet_existe(NoTipoPet *inicio, int codigo);




#endif