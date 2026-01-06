#ifndef COMANDO_H
#define COMANDO_H
#include <stdio.h>


struct no_comando{
    char ordem[200];
    struct no_comando *prox;
    struct no_comando *ant;
};


typedef struct no_comando no_comando;

void iniciar_fila_de_comando(no_comando **fila);
void remover_fila_de_comando(no_comando **fila);
void adicionar_fila_de_comando(no_comando **fila, no_comando comando);
void ler_arquivo( FILE *f, no_comando **fila_comando);
int validar_comando(no_comando *comando);
void validar_fila_comando(no_comando **fila);



#endif