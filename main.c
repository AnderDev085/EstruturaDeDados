#include <stdio.h>
#include "comando.h"



int main(){
    no_comando *fila_comando = NULL;
    no_comando *fila_comando_pet = NULL;
    no_comando *fila_comando_pessoa = NULL;
    no_comando *fila_comando_tipo_pet = NULL;
    Valores valores;
    FILE *file = fopen("script.txt", "r");
    ler_arquivo(file,&fila_comando);
    validar_fila_comando(&fila_comando);
    extrair_valores(fila_comando->ordem, &valores);
    printf("%s\n", fila_comando->ordem);
    printf("%s\n", valores.tabela);
    printf("%s\n", valores.nome);
    printf("%s\n", valores.fone);
    printf("%s\n", valores.data_nascimento);
    printf("%s\n", valores.endereco);
    printf("%s\n", valores.descricao);
    printf("%d\n", valores.codigo);
    printf("%d\n", valores.codigo_pes);
    printf("%d\n", valores.codigo_tipo);



    fclose(file);
    return 0;
}