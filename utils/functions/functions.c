#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.h"

struct st_livro *lista_livros = NULL;
struct favoritos *favoritos = NULL;

/*
 ▄▀  ██▀ █▄ █ ██▀ █▀▄ █ ▄▀▀ ▄▀▄ ▄▀▀
 ▀▄█ █▄▄ █ ▀█ █▄▄ █▀▄ █ ▀▄▄ █▀█ ▄██
*/
void carregar_dados()//carrega as informações que estao no bd(tanto de livros quanto de favoritos) para as listas de livros e favoritos
{
    FILE *db = fopen("database/livros.txt", "r");
    char linha[256], titulo[256], autor[256], genero[256], status[256];
    int qtd_paginas;

    if (db)
    {
        while (fgets(linha, sizeof(linha), db))
        {
            if (sscanf(linha, "%[^|] | %[^|] | %[^|] | %d | %[^|]", titulo, autor, genero, &qtd_paginas, status) == 5)
            {
                struct st_livro *novo_livro = (struct st_livro *)malloc(sizeof(struct st_livro));
                if (novo_livro)
                {
                    novo_livro->titulo = formatar_entrada(strdup(titulo));
                    novo_livro->autor = formatar_entrada(strdup(autor));
                    novo_livro->genero = formatar_entrada(strdup(genero));
                    novo_livro->qtd_paginas = qtd_paginas;
                    novo_livro->status = formatar_entrada(strdup(status));

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

    db = fopen("database/favoritos.txt", "r");

    if (db)
    {
        while (fgets(linha, sizeof(linha), db))
        {
            if (sscanf(linha, "%[^|] | %[^|] | %[^|] | %d | %[^|]", titulo, autor, genero, &qtd_paginas, status) == 5)
            {
                struct favoritos *favorito = (struct favoritos *)malloc(sizeof(struct favoritos));
                struct st_livro *novo_livro = (struct st_livro *)malloc(sizeof(struct st_livro));
                if (novo_livro)
                {
                    novo_livro->titulo = formatar_entrada(strdup(titulo));
                    novo_livro->autor = formatar_entrada(strdup(autor));
                    novo_livro->genero = formatar_entrada(strdup(genero));
                    novo_livro->qtd_paginas = qtd_paginas;
                    novo_livro->status = formatar_entrada(strdup(status));
                    novo_livro->proxPtr_livro = NULL;
                    favorito->livro = novo_livro;
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

void limpar_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

char *input_string(const char *txt) // sonally
{
    char buffer[256];
    printf("%s: ", txt);
    fflush(stdin); // limpar o buffer
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove a quebra de linha, se houver
    return strdup(buffer);                // strdup duplica as strings e, em seguida, libere a memória alocada no final do programa ou quando não precisar mais das strings.
}

char *formatar_entrada(char *str) // capitaliza a(s) palavra(s) e remove os espaços em branco
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

    for (int i = 0; str[i]; i++)
        str[i] = (i == 0 || str[i - 1] == ' ') ? toupper(str[i]) : tolower(str[i]);
    return str;
}

struct st_livro *buscar_livro(char *titulo, char *autor) // busca o livro na estante por meio do titulo e autor passados, essa função retorna o livro.
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

/*
 █▄ ▄█ ██▀ █▄ █ █ █ ▄▀▀
 █ ▀ █ █▄▄ █ ▀█ ▀▄█ ▄██
*/

int menu()
{
    char *input;
    int op;

    printf("\n====================================\n"
           "=               MENU               =\n"
           "====================================\n"
           "= [1] - Cadastrar Livro            =\n"
           "= [2] - Sobre a Estante            =\n"
           "= [3] - Filtrar                    =\n"
           "= [4] - Favoritos                  =\n"
           "= [0] - Sair                       =\n"
           "====================================\n\n");
    input = input_string("Digite a opcao desejada");

    if (strspn(input, "0123456789\n") == strlen(input)) // strspn conta quantos digitos de 0 a 9 existe no input e dps compara com o o tamanho da string, se for igual entao o input é valido
        op = atoi(input);                               // converte para inteiro
    else
        op = -1; // opcao invalida
    return op;
}

int status_menu()
{
    char *input;
    int op;

    printf("\n"
           "====================================\n"
           "=          MENU DE STATUS          =\n"
           "====================================\n"
           "= [1] - Lido                       =\n"
           "= [2] - Quero ler                  =\n"
           "= [3] - Abandonado                 =\n"
           "====================================\n"
           "\n");

    input = input_string("Selecione o Status do livro");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

int estante_menu()
{
    char *input;
    int op;

    printf("\n"
           "====================================\n"
           "=           MENU ESTANTE           =\n"
           "====================================\n"
           "= [1] - Visualizar livros          =\n"
           "= [2] - Quantidade de livros na    =\n"
           "=       Estante                    =\n"
           "= [3] - Editar Status              =\n"
           "= [4] - Remover Livro              =\n"
           "= [0] - Voltar                     =\n"
           "====================================\n"
           "\n");

    input = input_string("Digite a opcao desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

int filtrar_menu()
{
    int op;
    char *input;

    printf("\n"
           "====================================\n"
           "=          MENU DE FILTRO          =\n"
           "====================================\n"
           "= [1] - Filtrar por autor          =\n"
           "= [2] - Filtrar por genero         =\n"
           "= [3] - Filtrar por titulo         =\n"
           "= [4] - Filtrar por favoritos      =\n"
           "= [5] - Filtrar por status         =\n"
           "= [0] - Voltar                     =\n"
           "====================================\n\n");
    input = input_string("Digite a opcao desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

int filtrar_status_menu()
{
    char *input;
    int op;

    printf("\n"
           "====================================\n"
           "=          MENU DE STATUS          =\n"
           "====================================\n"
           "= [1] - Lido                       =\n"
           "= [2] - Quero ler                  =\n"
           "= [3] - Abandonado                 =\n"
           "= [0] - Voltar                     =\n"
           "====================================\n"
           "\n");

    input = input_string("Selecione o Status do livro");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

int favorito_menu()
{
    char *input;
    int op;

    printf("\n"
           "====================================\n"
           "=          MENU FAVORITOS          =\n"
           "====================================\n"
           "= [1] - Adicionar Favorito         =\n"
           "= [2] - Remover Favorito           =\n"
           "= [3] - Visualizar Favoritos       =\n"
           "= [0] - Voltar                     =\n"
           "====================================\n"
           "\n");

    input = input_string("Digite a opcao desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

/*
 ▄▀▀ ▄▀▄ █▀▄ ▄▀▄ ▄▀▀ ▀█▀ █▀▄ ▄▀▄
 ▀▄▄ █▀█ █▄▀ █▀█ ▄██  █  █▀▄ ▀▄▀
*/

void cadastrar_livro()
{
    struct st_livro *novo_livro = (struct st_livro *)malloc(sizeof(struct st_livro));
    if (novo_livro)
    {
        char *status;
        char *input;
        int confirmar;
        int op_status;

        printf("\n--- CADASTRO DE LIVRO ---\n");

        novo_livro->titulo = formatar_entrada(input_string("\nDigite o titulo do livro"));

        novo_livro->autor = formatar_entrada(input_string("Digite o nome do autor"));

        struct st_livro *livro = buscar_livro(novo_livro->titulo, novo_livro->autor);
        if (livro != NULL)
        {
            printf("\nEste livro ja existe na estante!\n");
            free(novo_livro);
            return;
        }

        novo_livro->genero = formatar_entrada(input_string("Digite o genero do livro"));

        printf("Digite a quantidade de paginas do livro: ");
        scanf("%d", &novo_livro->qtd_paginas);
        limpar_buffer();
        do
        {
            op_status = status_menu();

            switch (op_status)
            {
            case 1:
                status = "Lido";
                break;
            case 2:
                status = "Quero Ler";
                break;
            case 3:
                status = "Abandonado";
                break;
            default:
                printf("Opcao invalida.\n");
                break;
            }
        } while (op_status != 1 && op_status != 2 && op_status != 3);
        novo_livro->status = status;
        novo_livro->proxPtr_livro = NULL;

        printf("\nVoce inseriu os seguintes dados:\nTitulo: %s\nAutor: %s\nGenero: %s\nQuantidade de Paginas: %d\nStatus do Livro: %s\n", novo_livro->titulo, novo_livro->autor, novo_livro->genero, novo_livro->qtd_paginas, novo_livro->status);

        do
        {
            input = input_string("\nOs dados inseridos estao corretos? ([1]Sim/[2]Nao)");
            if (strspn(input, "0123456789\n") == strlen(input))
                confirmar = atoi(input);
            else
                confirmar = -1;

            switch (confirmar)
            {
            case 1:
                printf("\nLivro cadastrado com sucesso!\n");

                ordena_livros(novo_livro);
                armazenar_livros_db();
                break;

            case 2:
                printf("\nSem problemas!Tente novamente.\n");
                free(novo_livro);
                return;

            default:
                printf("\nOpcao invalida!\n");
                break;
            }
        } while (confirmar != 1 && confirmar != 2);
    }
    else
    {
        printf("Nao ha espaço disponivel para o livro!\n");
    }
}

void ordena_livros(struct st_livro *novo_livro) // armazena o livro na lista encadeada em ordem alfabetica
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
        // estamos varrendo a lista nao com o atual mas sim para quem ele aponta, a comparação acontece para ver entre quais dois livros o novo livro vai ser adicionado
        novo_livro->proxPtr_livro = atual->proxPtr_livro;
        atual->proxPtr_livro = novo_livro;
    }
}

void armazenar_livros_db() // pega todos os livros que estao na lista encadeada e sobrescreve no bd para o bd ficar em ordem alfabetica tbm
{
    FILE *db = fopen("database/livros.txt", "w");
    if (db)
    {
        struct st_livro *atual = lista_livros;
        while (atual != NULL)
        {
            fprintf(db, "%s | %s | %s | %d | %s\n", atual->titulo, atual->autor, atual->genero, atual->qtd_paginas, atual->status);
            atual = atual->proxPtr_livro;
        }
        fclose(db);
    }
    else
    {
        printf("Nao foi possivel abrir o arquivo de banco de dados.\n");
    }
}

/*
 █▀ ▄▀▄ █ █ ▄▀▄ █▀▄ █ ▀█▀ ▄▀▄ ▄▀▀
 █▀ █▀█ ▀▄▀ ▀▄▀ █▀▄ █  █  ▀▄▀ ▄██
*/

void pre_add_favorito() //faz uma checagem para ver se o livro já existe na estante antes de adicionar na lista de favoritos
{
    char *titulo;
    char *autor;
    struct st_livro *favorito = NULL;

    titulo = formatar_entrada(input_string("Digite o titulo do livro"));
    autor = formatar_entrada(input_string("Digite o autor do livro"));
    favorito = buscar_livro(titulo, autor);
    if (favorito == NULL)
        printf("\nLivro nao existe na estante!\n");
    else
        cadastrar_favorito(favorito);
}

void cadastrar_favorito(struct st_livro *novo_livro) //adiciona o livro na lista de favoritos
{
    struct favoritos *favorito = (struct favoritos *)malloc(sizeof(struct favoritos));
    favorito->livro = novo_livro;
    favorito->proxPtr_favorito = NULL;
    if (!(ehfavorito(novo_livro->titulo, novo_livro->autor)))
    {
        ordena_favoritos(favorito);
        armazenar_favorito_db();
        printf("\nFavorito cadastrado com sucesso!\n");
    }
    else
    {
        printf("\nFavorito ja cadastrado. Nao foi possivel cadastrar novamente! \n");
    }
}

void ordena_favoritos(struct favoritos *novo_favorito) //ordena a lista de favoritos em ordem alfabetica
{
    if (favoritos == NULL || strcmp(novo_favorito->livro->titulo, favoritos->livro->titulo) < 0)
    {
        novo_favorito->proxPtr_favorito = favoritos;
        favoritos = novo_favorito;
    }
    else
    {
        struct favoritos *atual = favoritos;
        while (atual->proxPtr_favorito != NULL && strcmp(novo_favorito->livro->titulo, atual->proxPtr_favorito->livro->titulo) > 0)
            atual = atual->proxPtr_favorito;

        novo_favorito->proxPtr_favorito = atual->proxPtr_favorito;
        atual->proxPtr_favorito = novo_favorito;
    }
}

void armazenar_favorito_db() //pega todos os livros que estao na lista de favoritos e sobrescreve no bd para o bd ficar em ordem alfabetica tbm
{
    FILE *db = fopen("database/favoritos.txt", "w");
    if (db)
    {
        struct favoritos *atual = favoritos;
        while (atual != NULL)
        {
            fprintf(db, "%s | %s | %s | %d | %s\n", atual->livro->titulo, atual->livro->autor, atual->livro->genero, atual->livro->qtd_paginas, atual->livro->status);
            atual = atual->proxPtr_favorito;
        }
        fclose(db);
    }
    else
    {
        printf("\nNao foi possivel abrir o arquivo de banco de dados!\n");
    }
}

void pre_remover_favorito()
{
    char *titulo;
    char *autor;

    titulo = formatar_entrada(input_string("Digite o titulo do livro"));
    autor = formatar_entrada(input_string("Digite o autor do livro"));
    remover_favorito(titulo, autor);
}

void remover_favorito(char *titulo, char *autor)
{
    struct favoritos *atual = favoritos;
    struct favoritos *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->livro->titulo, titulo) == 0 && strcmp(atual->livro->autor, autor) == 0)
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
            printf("\nFavorito removido com sucesso!\n");
            armazenar_favorito_db();

            return;
        }

        anterior = atual;
        atual = atual->proxPtr_favorito;
    }

    printf("\nFavorito nao encontrado!\n");
}

bool ehfavorito(char *titulo, char *autor) //verifica se o livro que vc quer adicionar em favoritos já esta na lista de favoritos
{
    struct favoritos *atual = favoritos;

    while (atual != NULL)
    {
        if (strcmp(atual->livro->titulo, titulo) == 0 && strcmp(atual->livro->autor, autor) == 0)
        {
            return true;
        }
        atual = atual->proxPtr_favorito;
    }

    return false;
}

void visualizar_favoritos()
{
    struct favoritos *atual = favoritos;
    if (atual == NULL)
    {
        printf("\nVoce ainda nao adicionou livros favoritos!\n");
        return;
    }

    printf("\n"
           "====================================\n"
           "=          LIVROS FAVORITOS        =\n"
           "====================================\n");
    while (atual != NULL)
    {
        printf("\n*Titulo: %s\n*Autor: %s\n*Genero: %s\n*Quantidade de paginas: %d\n*Status de leitura: %s\n", atual->livro->titulo, atual->livro->autor, atual->livro->genero, atual->livro->qtd_paginas, atual->livro->status);
        printf("====================================\n");
        atual = atual->proxPtr_favorito;
    }
}

/*
 ██▀ ▄▀▀ ▀█▀ ▄▀▄ █▄ █ ▀█▀ ██▀
 █▄▄ ▄██  █  █▀█ █ ▀█  █  █▄▄
*/

void visualizar_livros()
{
    // adicionar status pra printar
    struct st_livro *atual = lista_livros;
    int id = 1;

    if (atual == NULL)
    {
        printf("Voce ainda nao adicinou livros na estante!\n");
        return;
    }

    printf("\n"
           "====================================\n"
           "=         LIVROS NA ESTANTE        =\n"
           "====================================\n");
    while (atual != NULL)
    {
        printf("ID: %d\n*Titulo: %s\n*Autor: %s\n*Genero: %s\n*Quantidade de paginas: %d\n*Status de leitura: %s\n", id, atual->titulo, atual->autor, atual->genero, atual->qtd_paginas, atual->status);
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

void editar_status()
{
    // implementar
}

void sortear_livros()
{
    // implementar (gi)
}

void remover_livro()
{
    char *titulo;
    char *autor;

    printf("\n"
           "====================================\n"
           "=           REMOVER LIVRO          =\n"
           "====================================\n\n");

    titulo = formatar_entrada(input_string("Digite o titulo do livro que deseja remover"));

    autor = formatar_entrada(input_string("Qual o autor do livro? "));

    struct st_livro *livro_atual = lista_livros, *anterior = NULL;

    while (livro_atual != NULL)
    {
        if (strcmp(livro_atual->titulo, titulo) == 0 && strcmp(livro_atual->autor, autor) == 0)
        {
            if (anterior == NULL)
            {
                lista_livros = livro_atual->proxPtr_livro;
            }
            else
            {
                anterior->proxPtr_livro = livro_atual->proxPtr_livro;
            }
            if (ehfavorito(livro_atual->titulo, livro_atual->autor))
                remover_favorito(livro_atual->titulo, livro_atual->autor);
            free(livro_atual);
            printf("\nLivro removido com sucesso!\n");
            armazenar_livros_db();
            return;
        }

        anterior = livro_atual;
        livro_atual = livro_atual->proxPtr_livro;
    }

    printf("Livro nao encontrado.\n");
}

/*
 █▀ █ █   ▀█▀ █▀▄ ▄▀▄ █▀▄
 █▀ █ █▄▄  █  █▀▄ █▀█ █▀▄
*/

void filtrar(int filtro)
{
    struct st_livro *livro = NULL;
    char *autor;
    char *titulo;

    switch (filtro)
    {
    case 1:
        mostrar_autores_unicos();
        break;

    case 2:
        mostrar_generos_unicos();
        break;

    case 3:
        titulo = formatar_entrada(input_string("Digite o titulo do livro"));
        autor = formatar_entrada(input_string("Digite o nome do autor"));
        livro = buscar_livro(titulo, autor);

        if (livro == NULL)
            printf("\nLivro nao existe na estante!\n");
        else
        {
            printf("\n====================================\n");
            printf("=         INFORMACOES DO LIVRO      = ");
            printf("\n====================================");
            printf("\n*TITULO: %s\n*AUTOR: %s\n*GENERO: %s\n*QUANTIDADE DE PAG: %d\n*STATUS DE LEITURA: %s\n", livro->titulo, livro->autor,livro->genero, livro->qtd_paginas, livro->status);
            printf("====================================\n");
        }
        break;

    case 4:
        visualizar_favoritos();
        break;
    case 5:
        // implementar
        break;
    }
}

void mostrar_generos_unicos() // listar generos disponiveis no db
{
    int escolha;
    char *input;
    struct st_livro *livro_atual = lista_livros;
    char *generos[256]; // array de ponteiros(suporta 256 palavras), logo cada indice representa o genero unico guardado
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
           "=        GENEROS CADASTRADOS       =\n"
           "====================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("[%d] - %s\n", i + 1, generos[i]);
    }
    printf("====================================\n\n");

    do
    {
        input = input_string("Digite a opcao desejada");

        if (strspn(input, "0123456789\n") == strlen(input))
            escolha = atoi(input);
        else
            escolha = -1;

        if (escolha <= count && escolha > 0)
        {
            mostrar_livros_genero(formatar_entrada(generos[escolha - 1]));
        }
        else
            printf("Genero invalido!\n");
    } while (!(escolha <= count && escolha > 0));
}

void mostrar_livros_genero(char *genero) // mostrar os livros do genero escolhido
{
    struct st_livro *livro_atual = lista_livros;
    printf("\n"
           "====================================\n"
           "      LIVROS DO GENERO %s           \n"
           "====================================\n",
           genero);
    while (livro_atual != NULL)
    {
        if (strcmp(formatar_entrada(livro_atual->genero), formatar_entrada(genero)) == 0)
        {
            printf("\n*TITULO: %s\n*AUTOR: %s\n*QUANTIDADE DE PAG: %d\n*STATUS DE LEITURA: %s\n", livro_atual->titulo, livro_atual->autor, livro_atual->qtd_paginas, livro_atual->status);
            printf("====================================\n");
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
}

void mostrar_autores_unicos() // listar os autores disponiveis no db
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
           "=        AUTORES CADASTRADOS       =\n"
           "====================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("[%d] - %s\n", i + 1, autores[i]);
    }
    printf("====================================\n\n");
    do
    {
        input = input_string("Digite a opcao desejada");

        if (strspn(input, "0123456789\n") == strlen(input))
            escolha = atoi(input);
        else
            escolha = -1;

        if (escolha <= count && escolha > 0)
        {
            mostrar_livros_autor(formatar_entrada(autores[escolha - 1]));
        }
        else
            printf("Autor invalido!\n");
    } while (!(escolha <= count && escolha > 0));
}

void mostrar_livros_autor(char *autor) // mostrar os livros do autor escolhido
{
    struct st_livro *livro_atual = lista_livros;
    printf("\n"
           "====================================\n"
           "      LIVROS DO(A) AUTOR(A) %s       \n"
           "====================================\n",
           autor);
    while (livro_atual != NULL)
    {
        if (strcmp(formatar_entrada(livro_atual->autor), formatar_entrada(autor)) == 0)
        {
            printf("\n*TITULO: %s\n*GENERO: %s\n*QUANTIDADE DE PAG: %d\n*STATUS DE LEITURA: %s\n", livro_atual->titulo, livro_atual->genero, livro_atual->qtd_paginas, livro_atual->status);
            printf("====================================\n");
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
}