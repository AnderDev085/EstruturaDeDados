#ifndef COMANDO_H
#define COMANDO_H
#include <stdio.h>

#include "validacoes.h"
#include "pessoa.h"
#include "pet.h"
#include "tipo_pet.h"

struct no_comando{
    char ordem[200];
    struct no_comando *prox;
    struct no_comando *ant;
};

struct valores{
    char tipo[7];       
    char tabela[12];
    int order;     
    int codigo;
    int codigo_pes;
    int codigo_tipo;
    char nome[200];
    char fone[200];
    char data_nascimento[200];
    char endereco[200];
    char descricao[200];

};

typedef struct valores valores;
typedef struct no_comando no_comando;

void inicializar_valores(valores *valores);
void remover_fila_de_comando(no_comando **fila);
void adicionar_fila_de_comando(no_comando **fila, char ordem[200]);
void esvaziar_fila_de_comando(no_comando **fila);
void ler_arquivo( FILE *f, no_comando **fila_comando);
int validar_insert(char ordem[200]);
int validar_update(char ordem[200]);
int validar_delete(char ordem[200]);
int validar_select(char ordem[200]);
int validar_comando(no_comando *comando);
void validar_fila_comando(no_comando **fila);
void despachar_fila_comando(no_comando **fila_comando, no_comando **fpet, no_comando **ftipo, no_comando **fpessoa);
void extrair_valores(char ordem[200], valores *valores);
void executar_fila_comando_pessoa(no_comando **fila_comando_pessoa, NoPessoa **fila_pessoa,NoPet *Lista_pet, valores *valores);



#endif