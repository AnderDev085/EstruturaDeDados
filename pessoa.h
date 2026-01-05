#ifndef PESSOA_H
#define PESSOA_H

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

void inserir_pessoa(NoPessoa **inicio,Pessoa novaPessoa);
int remover_pessoa(NoPessoa **inicio,int codigo_alvo);
NoPessoa *buscar_pessoa(NoPessoa **inicio,int codigo_alvo);
int alterar_pessoa(NoPessoa **inicio,int codigo_alvo,char nome[100],char fone[100], char data_de_nascimento[11],char endereco[100]);
void salvar_arquivo_pessoa(NoPessoa *inicio);
void carregar_arquivo_pessoa(NoPessoa **inicio);


#endif