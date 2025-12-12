#ifndef TIPO_PET_H
#define TIPO_PET_H

struct tipo_pet{
    int codigo;
    char descricao[100];
};

struct no_tipo_pet{
    struct tipo_pet tipo_pet;
    struct no_tipo_pet *prox;
    struct no_tipo_pet *ant;
};


#endif