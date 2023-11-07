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
void carregar_dados(void);
void limpar_buffer(void);
char *input_string(const char *txt);
char *formatar_entrada(char *str);
struct st_livro *buscar_livro(char *titulo, char *autor);

//menu
int menu(void);
int status_menu(void);
int estante_menu(void);
int filtrar_menu(void);
int filtrar_status_menu(void);
int favorito_menu(void);

// cadastrar
void cadastrar_livro(void);
void ordena_livros(struct st_livro *novo_livro);
void armazenar_livros_db(void);

// favoritos
void pre_add_favorito(void);
void cadastrar_favorito(struct st_livro *novo_livro);
void ordena_favoritos(struct favoritos *novo_favorito);
void armazenar_favorito_db(void);
void pre_remover_favorito(void);
void remover_favorito(char *titulo, char *autor);
bool ehfavorito(char *titulo, char *autor);
void visualizar_favoritos(void);

// estante
void visualizar_livros(void);
int contar_livros(void);
void editar_status(void);
void sortear_livros(void);
void remover_livro(void);

// filtrar
void filtrar(int filtro);
void mostrar_generos_unicos(void);
void mostrar_livros_genero(char *genero);
void mostrar_autores_unicos(void);
void mostrar_livros_autor(char *autor);