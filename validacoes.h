#ifndef VALIDACOES_H
#define VALIDACOES_H

typedef struct NoPessoa NoPessoa;
typedef struct NoPet NoPet;
typedef struct NoTipoPet NoTipoPet;
typedef struct Pet Pet;

int pode_remover_pessoa(NoPessoa *lista_pessoas, NoPet *lista_pets, int codigo_pessoa);

int pode_remover_tipo_pet(NoTipoPet *lista_tipos, NoPet *lista_pets, int codigo_tipo);

int pode_inserir_pet(NoPessoa *lista_pessoas, NoTipoPet *lista_tipos, NoPet *lista_pets, Pet novoPet);

int pode_alterar_pet(NoPessoa *lista_pessoas, NoTipoPet *lista_tipos,NoPet *lista_pets, int codigo_pet, int *novo_codigo_pes, int *novo_codigo_tipo);

int contar_pets_por_tipo(NoPet *lista_pets, int codigo_tipo);

#endif