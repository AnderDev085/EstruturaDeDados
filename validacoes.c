#include <stdio.h>
#include "validacoes.h"
#include "pessoa.h"
#include "pet.h"
#include "tipo_pet.h"
#include "comando.h"


int pode_remover_pessoa(NoPessoa *lista_pessoas, NoPet *lista_pets, int codigo_pessoa) {

    if (!codigo_pessoa_existe(lista_pessoas, codigo_pessoa)) {
        printf("Erro: Pessoa com código %d não existe.\n", codigo_pessoa);
        return 0;
    }


    if (pessoa_tem_pets(lista_pets, codigo_pessoa)) {
        printf("Erro: Pessoa com código %d tem pets e não pode ser removida.\n", codigo_pessoa);
        return 0;
    }

    return 1;
}


int pode_remover_tipo_pet(NoTipoPet *lista_tipos, NoPet *lista_pets, int codigo_tipo) {

    if (!codigo_tipo_pet_existe(lista_tipos, codigo_tipo)) {
        printf("Erro: Tipo de pet com código %d não existe.\n", codigo_tipo);
        return 0;
    }

    NoPet *aux = lista_pets;
    while (aux != NULL) {
        if (aux->dados.codigo_tipo == codigo_tipo) {
            printf("Erro: Tipo de pet com código %d está em uso e não pode ser removido.\n", codigo_tipo);
            return 0;
        }
        aux = aux->prox;
    }

    return 1;
}


int pode_inserir_pet(NoPessoa *lista_pessoas, NoTipoPet *lista_tipos, NoPet *lista_pets, Pet novoPet) {

    if (!validar_pet(novoPet)) {
        printf("Erro: Dados do pet inválidos.\n");
        return 0;
    }


    if (codigo_pet_existe(lista_pets, novoPet.codigo)) {
        printf("Erro: Já existe um Pet cadastrado com o código %d.\n", novoPet.codigo);
        return 0;
    }


    if (!codigo_pessoa_existe(lista_pessoas, novoPet.codigo_pes)) {
        printf("Erro: Pessoa com código %d não existe.\n", novoPet.codigo_pes);
        return 0;
    }


    if (!codigo_tipo_pet_existe(lista_tipos, novoPet.codigo_tipo)) {
        printf("Erro: Tipo de pet com código %d não existe.\n", novoPet.codigo_tipo);
        return 0;
    }

    return 1;
}


int pode_alterar_pet(NoPessoa *lista_pessoas, NoTipoPet *lista_tipos,NoPet *lista_pets, int codigo_pet, int *novo_codigo_pes, int *novo_codigo_tipo) {


    if (!codigo_pet_existe(lista_pets, codigo_pet)) {
        printf("Erro: Pet com código %d não existe.\n", codigo_pet);
        return 0;
    }


    if (novo_codigo_pes != NULL) {
        if (!codigo_pessoa_existe(lista_pessoas, *novo_codigo_pes)) {
            printf("Erro: Pessoa com código %d não existe.\n", *novo_codigo_pes);
            return 0;
        }
    }


    if (novo_codigo_tipo != NULL) {
        if (!codigo_tipo_pet_existe(lista_tipos, *novo_codigo_tipo)) {
            printf("Erro: Tipo de pet com código %d não existe.\n", *novo_codigo_tipo);
            return 0;
        }
    }

    return 1;
}


int contar_pets_por_tipo(NoPet *lista_pets, int codigo_tipo) {
    int contador = 0;
    NoPet *aux = lista_pets;

    while (aux != NULL) {
        if (aux->dados.codigo_tipo == codigo_tipo) {
            contador++;
        }
        aux = aux->prox;
    }

    return contador;
}
