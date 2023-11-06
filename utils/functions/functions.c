#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.h"

struct st_livro *lista_livros = NULL;
struct favoritos *favoritos = NULL;

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
    char *input;
    int op;

    printf("\n====================================\n"
           "=          MENU DE OPÇÕES          =\n"
           "====================================\n"
           "= [1] - Cadastrar Livro            =\n"
           "= [2] - Sobre a estante            =\n"
           "= [3] - Filtrar                    =\n"
           "= [4] - Favoritos                  =\n"
           "= [5] - Remover Livro              =\n"
           "= [0] - Sair                       =\n"
           "====================================\n\n");
    input = input_string("Digite a opção desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
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
        int confirmar;
        char *input;

        printf("\n--- Cadastro de Livro ---\n");

        novo_livro->titulo = input_string("Digite o título do livro");
        capitalizar(novo_livro->titulo);

        novo_livro->autor = input_string("Digite o nome do autor");
        capitalizar(novo_livro->autor);
        if (livro_existe(novo_livro))
        {
            printf("Este livro já existe na estante.\n");
            free(novo_livro);
            return;
        }
        novo_livro->genero = trim(input_string("Digite o gênero do livro"));
        capitalizar(novo_livro->genero);

        printf("Digite a quantidade de páginas do livro: ");
        scanf("%d", &novo_livro->qtd_paginas);
        novo_livro->proxPtr_livro = NULL;
        limpar_buffer();

        printf("\nVocê inseriu os seguintes dados:\n Titulo: %s\n Autor: %s\n Gênero: %s\n Quantidade de Páginas: %d\n", novo_livro->titulo, novo_livro->autor, novo_livro->genero, novo_livro->qtd_paginas);
        do
        {
            input = input_string("Os dados inseridos estão corretos? ([1]Sim/[2]Não)");
            if (strspn(input, "0123456789\n") == strlen(input))
                confirmar = atoi(input);
            else
                confirmar = -1;

            switch (confirmar)
            {
            case 1:
                printf("\nLivro cadastrado com sucesso.\n");

                ordena_livros(novo_livro);
                gravar_livros();
                break;

            case 2:
                printf("\nSem problemas.\n");
                free(novo_livro);
                return;

            default:
                printf("Opcao invalida.\n");
                break;
            }
        } while (confirmar != 1 && confirmar != 2);
        do
        {
            input = input_string("Os dados inseridos estão corretos? ([1]Sim/[2]Não)");
            if (strspn(input, "0123456789\n") == strlen(input))
                confirmar = atoi(input);
            else
                confirmar = -1;

            switch (confirmar)
            {
            case 1:
                printf("\nLivro adicionado a lista de favoritos com sucesso.\n");
                cadastrar_favorito(novo_livro);
                break;

            case 2:
                printf("\nQuem sabe depois.\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
            }
        } while (confirmar != 1 && confirmar != 2);
    }
    else
    {
        printf("Não há espaço disponível para o livro.\n");
    }
}

// favoritos

int favorito_m()
{
    char *input;
    int op;

    printf("\n"
           "====================================\n"
           "=          MENU DE OPÇÕES          =\n"
           "====================================\n"
           "= [1] - Adicionar Favorito         =\n"
           "= [2] - Remover Favorito           =\n"
           "= [0] - Voltar                     =\n"
           "====================================\n"
           "\n");

    input = input_string("Digite a opção desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

void cadastrar_favorito(struct st_livro *novo_livro)
{
    struct favoritos *favorito = (struct favoritos *)malloc(sizeof(struct favoritos));
    favorito->item = novo_livro;
    favorito->proxPtr_favorito = NULL;
    if (!(ehfavorito(novo_livro->titulo, novo_livro->autor)))
    {
        ordena_favoritos(favorito);
        gravar_favorito();
        printf("\nFavorito cadastrado com sucesso.\n");
    }
    else
    {
        printf("\nFavorito já cadastrado. Não foi possivel cadastrar favorito. \n");
    }
}

void ordena_favoritos(struct favoritos *novo_favorito)
{
    if (favoritos == NULL || strcmp(novo_favorito->item->titulo, favoritos->item->titulo) < 0)
    {
        novo_favorito->proxPtr_favorito = favoritos;
        favoritos = novo_favorito;
    }
    else
    {
        struct favoritos *atual = favoritos;
        while (atual->proxPtr_favorito != NULL && strcmp(novo_favorito->item->titulo, atual->proxPtr_favorito->item->titulo) > 0)
            atual = atual->proxPtr_favorito;

        novo_favorito->proxPtr_favorito = atual->proxPtr_favorito;
        atual->proxPtr_favorito = novo_favorito;
    }
}

void gravar_favorito()
{
    FILE *db = fopen("database/favoritos.txt", "w");
    if (db)
    {
        struct favoritos *atual = favoritos;
        while (atual != NULL)
        {
            fprintf(db, "%s | %s | %s | %d\n", atual->item->titulo, atual->item->autor, atual->item->genero, atual->item->qtd_paginas);
            atual = atual->proxPtr_favorito;
        }
        fclose(db);
    }
    else
    {
        printf("Não foi possivel abrir o arquivo de banco de dados.\n");
    }
}

void carregar_favoritos()
{
    FILE *db = fopen("database/favoritos.txt", "r");
    char linha[256], titulo[256], autor[256], genero[256];
    int qtd_paginas;

    if (db)
    {
        while (fgets(linha, sizeof(linha), db))
        {
            if (sscanf(linha, "%[^|] | %[^|] | %[^|] | %d", titulo, autor, genero, &qtd_paginas) == 4)
            {
                struct favoritos *favorito = (struct favoritos *)malloc(sizeof(struct favoritos));
                struct st_livro *novo_livro = (struct st_livro *)malloc(sizeof(struct st_livro));
                if (novo_livro)
                {
                    novo_livro->titulo = trim(strdup(titulo));
                    novo_livro->autor = trim(strdup(autor));
                    novo_livro->genero = trim(strdup(genero));
                    novo_livro->qtd_paginas = qtd_paginas;
                    novo_livro->proxPtr_livro = NULL;
                    favorito->item = novo_livro;
                    favorito->proxPtr_favorito = NULL;
                    ordena_favoritos(favorito);
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

void remover_favorito(char *titulo, char *autor)
{
    struct favoritos *atual = favoritos;
    struct favoritos *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->item->titulo, titulo) == 0 && strcmp(atual->item->autor, autor) == 0)
        {
            if (anterior == NULL)
            {
                favoritos = atual->proxPtr_favorito;
            }
            else
            {
                anterior->proxPtr_favorito = atual->proxPtr_favorito;
            }

            free(atual);
            printf("Favorito removido com sucesso.\n");
            gravar_favorito();

            return;
        }

        anterior = atual;
        atual = atual->proxPtr_favorito;
    }

    printf("Favorito não encontrado.\n");
}

struct st_livro *buscar_livro(char *titulo, char *autor)
{
    struct st_livro *atual = lista_livros;

    while (atual != NULL)
    {
        if (strcmp(atual->titulo, titulo) == 0 && strcmp(atual->autor, autor) == 0)
        {
            return atual;
        }
        atual = atual->proxPtr_livro;
    }

    return NULL;
}

void pre_add_favorito()
{
    char *titulo;
    char *autor;
    struct st_livro *favorito = NULL;

    titulo = trim(input_string("Digite o título do livro"));
    capitalizar(titulo);
    autor = trim(input_string("Digite o autor do livro"));
    capitalizar(autor);
    favorito = buscar_livro(titulo, autor);
    if (favorito == NULL)
        printf("Livro não existe.");
    else
        cadastrar_favorito(favorito);
        
}

void pre_remover_favorito()
{
    char *titulo;
    char *autor;

    titulo = trim(input_string("Digite o título do livro"));
    capitalizar(titulo);
    autor = trim(input_string("Digite o autor do livro"));
    capitalizar(autor);
    remover_favorito(titulo, autor);
}

bool ehfavorito(char *titulo, char *autor)
{
    struct favoritos *atual = favoritos;

    while (atual != NULL)
    {
        if (strcmp(atual->item->titulo, titulo) == 0 && strcmp(atual->item->autor, autor) == 0)
        {
            return true;
        }
        atual = atual->proxPtr_favorito;
    }

    return false;
}

void ver_favoritos()
{
    struct favoritos *atual = favoritos;
    if (atual == NULL)
    {
        printf("Não há favoritos.\n");
        return;
    }

    printf("\n"
           "====================================\n"
           "=          LIVROS FAVORITOS        =\n"
           "====================================\n");
    while (atual != NULL)
    {
        printf("♦ Título: %s\n♦ Autor: %s\n♦ Gênero: %s\n♦ Quantidade de páginas: %d\n", atual->item->titulo, atual->item->autor, atual->item->genero, atual->item->qtd_paginas);
        printf("====================================\n");
        atual = atual->proxPtr_favorito;
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

int ver_menu()
{
    char *input;
    int op;

    printf("\n"
           "====================================\n"
           "=          MENU DE OPÇÕES          =\n"
           "====================================\n"
           "= [1] - Ver livros                 =\n"
           "= [2] - Quantidade de livros na    =\n"
           "=       Estante                    =\n"
           "= [0] - Voltar                     =\n"
           "====================================\n"
           "\n");

    input = input_string("Digite a opção desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

void pegar_info()
{
    struct st_livro *atual = lista_livros;
    int id = 1;

    if (atual == NULL)
    {
        printf("Não há livros.\n");
        return;
    }

    printf("\n"
           "====================================\n"
           "=         LIVROS NA ESTANTE        =\n"
           "====================================\n");
    while (atual != NULL)
    {
        printf("ID: %d\n♦ Título: %s\n♦ Autor: %s\n♦ Gênero: %s\n♦ Quantidade de páginas: %d\n", id, atual->titulo, atual->autor, atual->genero, atual->qtd_paginas);
        printf("====================================\n");
        atual = atual->proxPtr_livro;
        id++;
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
    char *input;

    printf("\n"
           "====================================\n"
           "=          MENU DE FILTRO          =\n"
           "====================================\n"
           "= [1] - Filtrar por autor          =\n"
           "= [2] - Filtrar por gênero         =\n"
           "= [3] - Filtrar por favoritos      =\n"
           "= [0] - Sair                       =\n"
           "====================================\n\n");
    input = input_string("Digite a opção desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

void mostrar_genero(char *genero)
{
    struct st_livro *livro_atual = lista_livros;
    printf("\n"
           "====================================\n"
           "      Livros do gênero %s       \n"
           "====================================\n",
           genero);
    while (livro_atual != NULL)
    {
        if (strcmp(trim(livro_atual->genero), trim(genero)) == 0)
        {
            printf("♦ %s escrito por %s\n", livro_atual->titulo, livro_atual->autor);
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
    printf("====================================\n");
}

void mostrar_generos_unicos()
{
    int escolha;
    char *input;
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

    printf("\n"
           "====================================\n"
           "=        Gêneros cadastrados:      =\n"
           "====================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("[%d] - %s\n", i + 1, generos[i]);
    }
    printf("====================================\n\n");

    do
    {
        input = input_string("Digite a opção desejada");

        if (strspn(input, "0123456789\n") == strlen(input))
            escolha = atoi(input);
        else
            escolha = -1;

        if (escolha <= count && escolha > 0)
        {
            mostrar_genero(trim(generos[escolha - 1]));
        }
        else
            printf("Gênero invalida.\n");
    } while (!(escolha <= count && escolha > 0));
}

void mostrar_autores(char *autor)
{
    struct st_livro *livro_atual = lista_livros;
    printf("\n"
           "====================================\n"
           "      Livros do Autor %s       \n"
           "====================================\n",
           autor);
    while (livro_atual != NULL)
    {
        if (strcmp(trim(livro_atual->autor), trim(autor)) == 0)
        {
            printf("♦ %s do gênero %s\n", livro_atual->titulo, livro_atual->genero);
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
    printf("====================================\n");
}

void mostrar_autores_unicos()
{
    int escolha;
    char *input;
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

    printf("\n"
           "====================================\n"
           "=        Autores cadastrados:      =\n"
           "====================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("[%d] - %s\n", i + 1, autores[i]);
    }
    printf("====================================\n\n");
    do
    {
        input = input_string("Digite a opção desejada");

        if (strspn(input, "0123456789\n") == strlen(input))
            escolha = atoi(input);
        else
            escolha = -1;

        if (escolha <= count && escolha > 0)
        {
            mostrar_autores(trim(autores[escolha - 1]));
        }
        else
            printf("Gênero invalida.\n");
    } while (!(escolha <= count && escolha > 0));
}

void filtrar(int filtro)
{
    switch (filtro)
    {
    case 1:
        mostrar_autores_unicos();
        break;

    case 2:
        mostrar_generos_unicos();
        break;
    case 3:
        ver_favoritos();
        break;
    }
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

    printf("\n"
           "====================================\n"
           "=           Remover Livro          =\n"
           "====================================\n\n");

    titulo = trim(input_string("Digite o título do livro que deseja remover"));
    capitalizar(titulo);

    autor = trim(input_string("Qual o autor do livro? "));
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
            if (ehfavorito(livro_atual->titulo, livro_atual->autor))
                remover_favorito(livro_atual->titulo, livro_atual->autor);
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
