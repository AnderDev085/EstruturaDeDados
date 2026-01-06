#include <stdio.h>
#include "comando.h"



int main(){
    no_comando *fila_comando;
    no_comando *fila_comando_pet;
    no_comando *fila_comando_pessoa;
    no_comando *fila_comando_tipo_pet;
    iniciar_fila_de_comando(&fila_comando);
    iniciar_fila_de_comando(&fila_comando_pet);
    iniciar_fila_de_comando(&fila_comando_pessoa);
    iniciar_fila_de_comando(&fila_comando_tipo_pet);
    FILE *file = fopen("script.txt", "r");
    ler_arquivo(file,&fila_comando);
    printf("Comando lido: %s\n", fila_comando->prox->ordem);
    fclose(file);
    return 0;
}