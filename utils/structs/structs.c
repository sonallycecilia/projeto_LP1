#include "structs.h"

#ifndef LIVRO_H
#define LIVRO_H

struct st_livro {
    char *titulo;
    char *autor;
    char *genero;
    int qtd_paginas;
    int status;
    struct st_livro *proxPtr_livro;

};

#endif