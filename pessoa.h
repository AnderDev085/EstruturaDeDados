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

typedef struct NoArvorePessoa {
    Pessoa dados;
    struct NoArvorePessoa *direita;
    struct NoArvorePessoa *esquerda;
}NoArvorePessoa;

void inserir_pessoa(NoPessoa **inicio,Pessoa novaPessoa);

int remover_pessoa(NoPessoa **inicio,int codigo_alvo);

NoPessoa *buscar_pessoa(NoPessoa *inicio,int codigo_alvo);

int alterar_pessoa(NoPessoa *inicio, int codigo_alvo, char *nome, char *fone, char *data_nascimento, char *endereco);

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






#endif