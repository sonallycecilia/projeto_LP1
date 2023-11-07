#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// struct
#ifndef LIVRO_H
#define LIVRO_H

struct st_livro
{
    char *titulo;
    char *autor;
    char *genero;
    int qtd_paginas;
    char *status;
    struct st_livro *proxPtr_livro;
};
struct favoritos
{
    struct st_livro *livro;
    struct favoritos *proxPtr_favorito;
};
#endif

// genericos
int menu(void);
void limpar_buffer(void);
char *input_string(const char *txt);
void capitalizar(char *txt);
char *trim(char *str);
bool livro_existe(struct st_livro *novo_livro);

// cadastrar
void ordena_livros(struct st_livro *novo_livro);
void carregar_livros(void);
void armazenar_livros_db(void);
void cadastrar_livro(void);

// favoritos
int favorito_m(void);
void cadastrar_favorito(struct st_livro *novo_livro);
void ordena_favoritos(struct favoritos *novo_favorito);
void gravar_favorito(void);
void carregar_favoritos(void);
void remover_favorito(char *titulo, char *autor);
struct st_livro *buscar_livro(char *titulo, char *autor);
void pre_add_favorito(void);

void pre_remover_favorito(void);
bool ehfavorito(char *titulo, char *autor);
void ver_favoritos(void);

// ver informação
int ver_menu(void);
void visualizar_livros(void);
int contar_livros(void);
void editar_status(void);

// filtrar
int filtrar_m(void);
void mostrar_livros_genero(char *genero);
void mostrar_generos_unicos(void);
void mostrar_livros_autor(char *autor);
void mostrar_autores_unicos(void);
void filtrar(int filtro);

// remvover
void remover_livro(void);