#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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
void gravar_livros(void);
void remover_livro(void);
void cadastrar_livro(void);

// ver informação
void pegar_info(void);
int contar_livros(void);

//filtrar
int filtrar_m(void);
void mostrar_genero(char *genero);
void mostrar_generos_unicos(void);
void mostrar_autores(char *autor);
void mostrar_autores_unicos(void);
void filtrar(int filtro);

//remvover
void remover_livro(void);