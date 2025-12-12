#ifndef COMANDO_H
#define COMANDO_H
#include <stdio.h>
struct comando{
    char ordem[200];
};

struct no_comando{
    struct comando comando;
    struct no_comando *prox;
    struct no_comando *ant;
};

typedef struct comando comando;
typedef struct no_comando no_comando;

void iniciar_fila_de_comando(no_comando **fila);
void push_fila_de_comando(no_comando **fila, comando comando);
int ler_linha( FILE *f, no_comando **fila_comando);
void validar_comando(comando comando);


#endif