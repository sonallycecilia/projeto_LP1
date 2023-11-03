#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.h"

struct st_livro *lista_livros = NULL;

/*
━┏━┓━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
━┃┏┛━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
┏┛┗┓┏┓┏┓┏━┓━┏━━┓┏━━┓┏━━┓┏━━┓━━━━┏━━┓┏━━┓┏━┓━┏━━┓┏━┓┏┓┏━━┓┏━━┓━┏━━┓
┗┓┏┛┃┃┃┃┃┏┓┓┃┏━┛┃┏┓┃┃┏┓┃┃━━┫━━━━┃┏┓┃┃┏┓┃┃┏┓┓┃┏┓┃┃┏┛┣┫┃┏━┛┗━┓┃━┃━━┫
━┃┃━┃┗┛┃┃┃┃┃┃┗━┓┃┗┛┃┃┃━┫┣━━┃━━━━┃┗┛┃┃┃━┫┃┃┃┃┃┃━┫┃┃━┃┃┃┗━┓┃┗┛┗┓┣━━┃
━┗┛━┗━━┛┗┛┗┛┗━━┛┗━━┛┗━━┛┗━━┛━━━━┗━┓┃┗━━┛┗┛┗┛┗━━┛┗┛━┗┛┗━━┛┗━━━┛┗━━┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┏━┛┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

int menu()
{
    int op;

    printf("[1] - Cadastrar Livro\n");
    printf("[2] - Ver livros\n");
    printf("[3] - Filtrar\n");
    printf("[4] - Quantidade de Livros na Estante\n");
    printf("[5] - Remover Elemento\n");
    printf("[0] - Sair\n");
    scanf("%d", &op);

    return op;
}

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

char *input_string(const char *txt)
{
    char buffer[256];
    printf("%s: ", txt);
    fflush(stdin); // limpar o buffer
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove a quebra de linha, se houver
    return strdup(buffer);                // strdup duplica as strings e, em seguida, libere a memória alocada no final do programa ou quando não precisar mais das strings.
}

void capitalizar(char *txt)
{
    if (txt == NULL)
        return;

    txt[0] = toupper(txt[0]);

    for (int i = 1; txt[i]; i++)
    {
        if (txt[i - 1] == ' ')
            txt[i] = toupper(txt[i]);
        else
            txt[i] = tolower(txt[i]);
    }
}

char *trim(char *str)
{
    char *end;
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    end[1] = '\0';
    return str;
}


bool livro_existe(struct st_livro *novo_livro)
{
    bool res = false;
    struct st_livro *livro_atual = lista_livros;
    while (livro_atual != NULL && !res)
    {
        if (strcmp(trim(livro_atual->titulo), trim(novo_livro->titulo)) == 0)
            if (strcmp(trim(livro_atual->autor), trim(novo_livro->autor)) == 0)
                res = true;
        livro_atual = livro_atual->proxPtr_livro;
    }
    return res;
}

/*
┏━━━┓━━━━━━━┏┓━━━━━━━━━━┏┓━━━━━━━━
┃┏━┓┃━━━━━━━┃┃━━━━━━━━━┏┛┗┓━━━━━━━
┃┃━┗┛┏━━┓━┏━┛┃┏━━┓━┏━━┓┗┓┏┛┏━┓┏━━┓
┃┃━┏┓┗━┓┃━┃┏┓┃┗━┓┃━┃━━┫━┃┃━┃┏┛┃┏┓┃
┃┗━┛┃┃┗┛┗┓┃┗┛┃┃┗┛┗┓┣━━┃━┃┗┓┃┃━┃┗┛┃
┗━━━┛┗━━━┛┗━━┛┗━━━┛┗━━┛━┗━┛┗┛━┗━━┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

void ordena_livros(struct st_livro *novo_livro)
{
    if (lista_livros == NULL || strcmp(novo_livro->titulo, lista_livros->titulo) < 0)
    {
        novo_livro->proxPtr_livro = lista_livros;
        lista_livros = novo_livro;
    }
    else
    {
        struct st_livro *atual = lista_livros;
        while (atual->proxPtr_livro != NULL && strcmp(novo_livro->titulo, atual->proxPtr_livro->titulo) > 0)
            atual = atual->proxPtr_livro;

        novo_livro->proxPtr_livro = atual->proxPtr_livro;
        atual->proxPtr_livro = novo_livro;
    }
}

void carregar_livros()
{
    FILE *db = fopen("database/livros.txt", "r");
    char linha[256], titulo[256], autor[256], genero[256];
    int qtd_paginas;

    if (db)
    {
        while (fgets(linha, sizeof(linha), db))
        {
            if (sscanf(linha, "%[^|] | %[^|] | %[^|] | %d", titulo, autor, genero, &qtd_paginas) == 4)
            {
                struct st_livro *novo_livro = (struct st_livro *)malloc(sizeof(struct st_livro));
                if (novo_livro)
                {
                    novo_livro->titulo = trim(strdup(titulo));
                    novo_livro->autor = trim(strdup(autor));
                    novo_livro->genero = trim(strdup(genero));
                    novo_livro->qtd_paginas = qtd_paginas;
                    novo_livro->proxPtr_livro = NULL;

                    ordena_livros(novo_livro);
                }
            }
        }
        fclose(db);
    }
    else
    {
        printf("Base de dados não encontrada\n");
    }
}

void gravar_livros()
{
    FILE *db = fopen("database/livros.txt", "w");
    if (db)
    {
        struct st_livro *atual = lista_livros;
        while (atual != NULL)
        {
            fprintf(db, "%s | %s | %s | %d\n", atual->titulo, atual->autor, atual->genero, atual->qtd_paginas);
            atual = atual->proxPtr_livro;
        }
        fclose(db);
    }
    else
    {
        printf("Não foi possivel abrir o arquivo de banco de dados.\n");
    }
}

void cadastrar_livro()
{
    struct st_livro *novo_livro = (struct st_livro *)malloc(sizeof(struct st_livro));
    if (novo_livro)
    {
        char *confirmar;

        limpar_buffer();
        novo_livro->titulo = input_string("Titulo");
        capitalizar(novo_livro->titulo);

        novo_livro->autor = input_string("Autor");
        capitalizar(novo_livro->autor);
        if (livro_existe(novo_livro))
        {
            printf("Este livro já existe na estante.\n");
            free(novo_livro);
            return;
        }
        novo_livro->genero = trim(input_string("Genero"));
        capitalizar(novo_livro->genero);

        printf("Quantidade de paginas: ");
        scanf("%d", &novo_livro->qtd_paginas);
        novo_livro->proxPtr_livro = NULL;

        printf("%s | %s | %s | %d\n", novo_livro->titulo, novo_livro->autor, novo_livro->genero, novo_livro->qtd_paginas);

        printf("Os dados inseridos estão corretos?\n");

        limpar_buffer();

        confirmar = trim(input_string("Sim/Não "));
        capitalizar(confirmar);

        if (!(strcmp(confirmar, "Sim") == 0))
        {
            free(novo_livro);
            return;
        }
        printf("Livro cadastrado com sucesso.\n");
        ordena_livros(novo_livro);
        gravar_livros();
    }
    else
    {
        printf("Não ha espaço disponivel para o livro.\n");
    }
}

/*
━━━━━━━━━━━━━━━━━━━┏┓━━━━━━━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━┃┃━━━━━━━━━━━━━━━━━━
━━━━┏┓┏┓┏━━┓┏━┓━━━━┃┃━┏┓┏┓┏┓┏━┓┏━━┓┏━━┓
━━━━┃┗┛┃┃┏┓┃┃┏┛━━━━┃┃━┣┫┃┗┛┃┃┏┛┃┏┓┃┃━━┫
━━━━┗┓┏┛┃┃━┫┃┃━━━━━┃┗┓┃┃┗┓┏┛┃┃━┃┗┛┃┣━━┃
━━━━━┗┛━┗━━┛┗┛━━━━━┗━┛┗┛━┗┛━┗┛━┗━━┛┗━━┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

void pegar_info()
{
    FILE *db;
    struct st_livro livro;
    db = fopen("database/livros.txt", "r");
    char linha[256], titulo[256], autor[256], genero[256];

    if (db)
    {
        while (fgets(linha, sizeof(linha), db))
        {
            if (sscanf(linha, "%[^|] | %[^|] | %[^|] | %d", titulo, autor, genero, &livro.qtd_paginas) == 4)
            {
                livro.titulo = strdup(titulo);
                livro.autor = strdup(autor);
                livro.genero = strdup(genero);
                printf("Titulo: %s\nAutor: %s\nGenero: %s\nPaginas: %d\n\n", livro.titulo, livro.autor, livro.genero, livro.qtd_paginas);
                free(livro.titulo);
                free(livro.autor);
                free(livro.genero);
            }
            else
            {
                printf("Erro ao ler a linha: %s", linha);
            }
        }

        fclose(db);
    }
    else
    {
        printf("Base de dados não encontrada\n");
    }
}

int contar_livros()
{
    int cont = 0;
    struct st_livro *atual = lista_livros;
    while (atual != NULL)
    {
        cont++;
        atual = atual->proxPtr_livro;
    }
    return cont;
}
/*
━┏━┓━━┏┓━━┏┓━━━━━━━━
━┃┏┛━━┃┃━┏┛┗┓━━━━━━━
┏┛┗┓┏┓┃┃━┗┓┏┛┏━┓┏━━┓
┗┓┏┛┣┫┃┃━━┃┃━┃┏┛┃┏┓┃
━┃┃━┃┃┃┗┓━┃┗┓┃┃━┃┗┛┃
━┗┛━┗┛┗━┛━┗━┛┗┛━┗━━┛
━━━━━━━━━━━━━━━━━━━━
*/

int filtrar_m()
{
    int op;

    printf("[1] - Filtrar por autor \n");
    printf("[2] - Filtrar por gênero\n");
    scanf("%d", &op);

    return op;
}

void mostrar_genero(char *genero)
{
    struct st_livro *livro_atual = lista_livros;
    printf("Livros do gênero %s:\n\n", genero);
    while (livro_atual != NULL)
    {
        if (strcmp(trim(livro_atual->genero), trim(genero)) == 0)
        {
            printf("%s | %s\n", livro_atual->titulo, livro_atual->autor);
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
    printf("\n");
}

void mostrar_generos_unicos()
{
    int escolha;
    char *palavra;
    struct st_livro *livro_atual = lista_livros;
    char *generos[256];
    int count = 0;

    while (livro_atual != NULL)
    {
        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(generos[i], livro_atual->genero) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            generos[count++] = livro_atual->genero;
        }
        livro_atual = livro_atual->proxPtr_livro;
    }

    printf("Gêneros cadastrados:\n");
    for (int i = 0; i < count; i++)
    {
        printf("    [%d]   %s\n", i + 1, generos[i]);
    }

    limpar_buffer();
    printf("\nQue Gênero deseja escolher:\n");
    scanf("%d", &escolha);

    if (escolha < count && escolha > 0)
    {
        mostrar_genero(trim(generos[escolha - 1]));
    }
    else
        printf("Gênero invalida.\n");
        limpar_buffer();

}

void mostrar_autores(char *autor)
{
    struct st_livro *livro_atual = lista_livros;
    printf("Livros do Autor %s:\n\n", autor);
    while (livro_atual != NULL)
    {
        if (strcmp(trim(livro_atual->autor), trim(autor)) == 0)
        {
            printf("%s | %s\n", livro_atual->titulo, livro_atual->genero);
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
    printf("\n");
}

void mostrar_autores_unicos()
{
    int escolha;
    struct st_livro *livro_atual = lista_livros;
    char *autores[256];
    int count = 0;

    while (livro_atual != NULL)
    {
        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(autores[i], livro_atual->autor) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            autores[count++] = livro_atual->autor;
        }
        livro_atual = livro_atual->proxPtr_livro;
    }

    printf("Autores cadastrados:\n");
    for (int i = 0; i < count; i++)
    {
        printf("    [%d]   %s\n", i + 1, autores[i]);
    }

    limpar_buffer();
    printf("\nQue autor deseja escolher:\n");
    scanf("%d", &escolha);

    if (escolha < count && escolha > 0)
        mostrar_autores(trim(autores[escolha - 1]));
    else
        printf("Autor invalida.\n");
        limpar_buffer();

}

void filtrar(int filtro)
{
    if (filtro == 2)
        mostrar_generos_unicos();
    else
        mostrar_autores_unicos();
}

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┏┓━━━━━━━━━━━━━━
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃┃━━━━━━━━━━━━━━
┏━┓┏━━┓┏┓┏┓┏━━┓┏┓┏┓┏━━┓┏━┓━━━━┃┃━┏┓┏┓┏┓┏━┓┏━━┓
┃┏┛┃┏┓┃┃┗┛┃┃┏┓┃┃┗┛┃┃┏┓┃┃┏┛━━━━┃┃━┣┫┃┗┛┃┃┏┛┃┏┓┃
┃┃━┃┃━┫┃┃┃┃┃┗┛┃┗┓┏┛┃┃━┫┃┃━━━━━┃┗┓┃┃┗┓┏┛┃┃━┃┗┛┃
┗┛━┗━━┛┗┻┻┛┗━━┛━┗┛━┗━━┛┗┛━━━━━┗━┛┗┛━┗┛━┗┛━┗━━┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

void remover_livro()
{
    char *titulo;
    char *autor;

    limpar_buffer();

    titulo = input_string("Digite o título do livro que deseja remover");
    capitalizar(titulo);

    autor = input_string("Qual o autor?");
    capitalizar(autor);

    struct st_livro *livro_atual = lista_livros, *prev = NULL;

    while (livro_atual != NULL)
    {
        if (strcmp(livro_atual->titulo, titulo) == 0 && strcmp(livro_atual->autor, autor) == 0)
        {
            if (prev == NULL)
            {
                lista_livros = livro_atual->proxPtr_livro;
            }
            else
            {
                prev->proxPtr_livro = livro_atual->proxPtr_livro;
            }

            free(livro_atual);
            printf("Livro removido com sucesso.\n");
            gravar_livros();
            return;
        }

        prev = livro_atual;
        livro_atual = livro_atual->proxPtr_livro;
    }

    printf("Livro não encontrado.\n");
}
