#ifndef PET_H
#define PET_H

struct pet{
    int codigo;
    int codigo_pes;
    int codigo_tipo;
    char nome[100];
};

struct no_pet{
    struct pet pet;
    struct no_pet *prox;
    struct no_pet *ant;
};


#endif