#ifndef PET_H
#define PET_H

typedef struct {
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

typedef struct NoArvorePet {
    Pet dados;
    struct NoArvorePet *direita;
    struct NoArvorePet *esquerda;

}NoArvorePet;

void inserir_pet(NoPet **inicio, Pet novoPet);

int remover_pet(NoPet **inicio, int codigo_alvo);

NoPet *buscar_pet(NoPet *inicio, int codigo_alvo);

int validar_pet(Pet pet);

int alterar_pet(NoPet *inicio, int codigo_alvo, int *codigo_pes, char *nome, int *codigo_tipo);

int codigo_pet_existe(NoPet *inicio, int codigo);

void imprimir_pet(Pet pet);

void listar_pets(NoPet *inicio);

int pessoa_tem_pets(NoPet *inicio, int codigo_pessoa);

void listar_pets_por_nome(NoPet *inicio);


NoArvorePet* construir_arvore_pet_por_nome(NoPet *inicio);

NoArvorePet* inserir_pet_na_arvore_por_nome(NoArvorePet *raiz, Pet pet);

void percorrer_em_ordem_pet(NoArvorePet *raiz);

void liberar_arvore_pet(NoArvorePet *raiz);

void salvar_arquivo_pet(NoPet *inicio);

void carregar_arquivo_pet(NoPet **inicio);




#endif