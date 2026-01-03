#ifndef PET_H
#define PET_H

typedef struct{
    int codigo;
    int codigo_pes;
    int codigo_tipo;
    char nome[100];
}Pet;

typedef struct NoPet{
    Pet dados;
    struct NoPet *prox;
    struct NoPet *ant;
} NoPet;

void inserir_pet(NoPet **inicio, Pet novoPet);

int remover_pet(NoPet **inicio, int codigo_alvo);

NoPet *buscar_pet(NoPet *inicio, int codigo_alvo);

void salvar_arquivo_pet(NoPet *inicio);

void carregar_arquivo_pet(NoPet **inicio);



#endif