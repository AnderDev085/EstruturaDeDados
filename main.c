#include <stdio.h>
#include "comando.h"



int main(){
    no_comando *fila_comando;
    iniciar_fila_de_comando(&fila_comando);
    FILE *file = fopen("script.txt", "r");
    ler_linha(file, &fila_comando);
    printf("Comando lido: %s\n", fila_comando->comando.ordem);
    fclose(file);
    



    return 0;
}