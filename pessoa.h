#ifndef PESSOA_H
#define PESSOA_H

struct pessoa{
    int codigo;
    char nome[100];
    char fone[100];
    char data_nascimento[11];
    char endereco[100];
};

struct no_pessoa{
    struct pessoa pessoa;
    struct no_pessoa *prox;
    struct no_pessoa *ant;
};


#endif