#include <stdio.h>
#include "validacoes.h"
#include "pessoa.h"
#include "pet.h"
#include "tipo_pet.h"
#include "comando.h"



int main(){
    no_comando *fila_comando = NULL;
    no_comando *fila_comando_pet = NULL;
    no_comando *fila_comando_pessoa = NULL;
    no_comando *fila_comando_tipo_pet = NULL;
    NoPessoa *fila_pessoa = NULL;
    NoTipoPet *fila_tipo_pet = NULL;
    NoPet *fila_pet = NULL;
    valores valores;
    inicializar_valores(&valores);
    FILE *file = fopen("script.txt", "r");
    ler_arquivo(file,&fila_comando);
    validar_fila_comando(&fila_comando);

    carregar_arquivo_pessoa(&fila_pessoa);
    
    despachar_fila_comando(&fila_comando, &fila_comando_pet, &fila_comando_tipo_pet, &fila_comando_pessoa);

    executar_fila_comando_tipo(&fila_comando_tipo_pet, &fila_tipo_pet,fila_pet,&valores);

    executar_fila_comando_pessoa(&fila_comando_pessoa,&fila_pessoa,fila_pet,&valores);

    executar_fila_comando_pet(&fila_comando_pet, &fila_pet, fila_pessoa, fila_tipo_pet, &valores);

    salvar_arquivo_pessoa(fila_pessoa);
    liberar_lista_pessoa(&fila_pessoa);



    fclose(file);
    return 0;
}