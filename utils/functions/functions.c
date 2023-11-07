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
           "= [2] - Sobre a Estante            =\n"
           "= [3] - Filtrar                    =\n"
           "= [4] - Favoritos                  =\n"
           "= [0] - Sair                       =\n"
           "====================================\n\n");
    input = input_string("Digite a opção desejada");

    if (strspn(input, "0123456789\n") == strlen(input)) // strspn conta quantos digitos de 0 a 9 existe no input e dps compara com o o tamanho da string, se for igual entao o input é valido
        op = atoi(input); //converte para inteiro
    else
        op = -1; //opcao invalida 
    return op;
}

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

char *input_string(const char *txt)//sonally
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

    for (int i = 0; txt[i]; i++)
        txt[i] = (i == 0 || txt[i - 1] == ' ') ? toupper(txt[i]) : tolower(txt[i]);
}

char *trim(char *str)//remove espaços em branco
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
/*
┏━━━┓━━━━━━━┏┓━━━━━━━━━━┏┓━━━━━━━━
┃┏━┓┃━━━━━━━┃┃━━━━━━━━━┏┛┗┓━━━━━━━
┃┃━┗┛┏━━┓━┏━┛┃┏━━┓━┏━━┓┗┓┏┛┏━┓┏━━┓
┃┃━┏┓┗━┓┃━┃┏┓┃┗━┓┃━┃━━┫━┃┃━┃┏┛┃┏┓┃
┃┗━┛┃┃┗┛┗┓┃┗┛┃┃┗┛┗┓┣━━┃━┃┗┓┃┃━┃┗┛┃
┗━━━┛┗━━━┛┗━━┛┗━━━┛┗━━┛━┗━┛┗┛━┗━━┛
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/
int status_m()
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

    input = input_string("Selecione o Status do livro: ");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

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
        //estamos varrendo a lista nao com o atual mas sim para quem ele aponta, a comparação acontece para ver entre quais dois livros o novo livro vai ser adicionado
        novo_livro->proxPtr_livro = atual->proxPtr_livro;
        atual->proxPtr_livro = novo_livro;
    }
}

void carregar_livros()//sonally explica mel
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

void armazenar_livros_db()
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
        char *status;
        char *input;
        int confirmar;
        int op_status;

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

        do{
            op_status = status_m();  

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
                break;}
        }while(op_status != 1 && op_status !=2 && op_status !=3);
        novo_livro->status = status;
        printf("\nVocê inseriu os seguintes dados:\nTitulo: %s\nAutor: %s\nGênero: %s\nQuantidade de Páginas: %d\nStatus do Livro: %s\n", novo_livro->titulo, novo_livro->autor, novo_livro->genero, novo_livro->qtd_paginas,novo_livro->status);
        
        do
        {
            input = input_string("\nOs dados inseridos estão corretos? ([1]Sim/[2]Não)");
            if (strspn(input, "0123456789\n") == strlen(input))
                confirmar = atoi(input);
            else
                confirmar = -1;

            switch (confirmar)
            {
            case 1:
                printf("\nLivro cadastrado com sucesso.\n");

                ordena_livros(novo_livro);
                armazenar_livros_db();
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

void cadastrar_favorito(struct st_livro *novo_livro)
{
    struct favoritos *favorito = (struct favoritos *)malloc(sizeof(struct favoritos));
    favorito->livro = novo_livro;
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

void gravar_favorito()
{
    FILE *db = fopen("database/favoritos.txt", "w");
    if (db)
    {
        struct favoritos *atual = favoritos;
        while (atual != NULL)
        {
            fprintf(db, "%s | %s | %s | %d\n", atual->livro->titulo, atual->livro->autor, atual->livro->genero, atual->livro->qtd_paginas);
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
            printf("Favorito removido com sucesso.\n");
            gravar_favorito();

            return;
        }

        anterior = atual;
        atual = atual->proxPtr_favorito;
    }

    printf("Favorito não encontrado.\n");
}

bool ehfavorito(char *titulo, char *autor)
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
        printf("♦ Título: %s\n♦ Autor: %s\n♦ Gênero: %s\n♦ Quantidade de páginas: %d\n", atual->livro->titulo, atual->livro->autor, atual->livro->genero, atual->livro->qtd_paginas);
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
           "= [3] - Editar Status              =\n"
           "= [4] - Remover Livro              =\n"
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

void visualizar_livros()
{
    //adicionar status pra printar
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

void editar_status(){
    //implementar
}

void sortear_livros(){
    //implementar (gi)
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
           "= [3] - Filtrar por titulo         =\n"
           "= [4] - Filtrar por favoritos      =\n"
           "= [5] - Filtrar por status         =\n"
           "= [0] - Sair                       =\n"
           "====================================\n\n");
    input = input_string("Digite a opção desejada");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

int filtrar_status_m()
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

    input = input_string("Selecione o Status do livro: ");

    if (strspn(input, "0123456789\n") == strlen(input))
        op = atoi(input);
    else
        op = -1;
    return op;
}

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
        titulo = trim(input_string("Digite o título do livro"));
        capitalizar(titulo);

        autor = trim(input_string("Digite o nome do autor"));
        capitalizar(autor);

        livro = buscar_livro(titulo, autor);

        if(livro == NULL)
            printf("Livro não existe na estante!");
        else{
            printf("%s | %s | %s | %d\n", livro->titulo, livro->autor, livro->genero, livro->qtd_paginas);
        }
        break;

    case 4:
        ver_favoritos();
        break;
    case 5:
        //implementar
        break;
    }
}

void mostrar_generos_unicos()//listar generos disponiveis no db
{
    int escolha;
    char *input;
    struct st_livro *livro_atual = lista_livros;
    char *generos[256]; //array de ponteiros(suporta 256 palavras), logo cada indice representa o genero unico guardado
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
            mostrar_livros_genero(trim(generos[escolha - 1]));
        }
        else
            printf("Gênero invalida.\n");
    } while (!(escolha <= count && escolha > 0));
}  

void mostrar_livros_genero(char *genero)//mostrar os livros do genero escolhido
{
    struct st_livro *livro_atual = lista_livros;
    printf("\n"
           "====================================\n"
           "      Livros do gênero %s           \n"
           "====================================\n",
           genero);
    while (livro_atual != NULL)
    {
        if (strcmp(trim(livro_atual->genero), trim(genero)) == 0)
        {
            printf("* %s escrito por %s\n", livro_atual->titulo, livro_atual->autor);
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
    printf("====================================\n");
}

void mostrar_autores_unicos() // mostrar os autores disponiveis no db
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
            mostrar_livros_autor(trim(autores[escolha - 1]));
        }
        else
            printf("Gênero invalida.\n");
    } while (!(escolha <= count && escolha > 0));
}

void mostrar_livros_autor(char *autor) // mostrar os livros do autor escolhido
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
            printf("* %s do gênero %s\n", livro_atual->titulo, livro_atual->genero);
        }
        livro_atual = livro_atual->proxPtr_livro;
    }
    printf("====================================\n");
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
            printf("Livro removido com sucesso.\n");
            armazenar_livros_db();
            return;
        }

        anterior = livro_atual;
        livro_atual = livro_atual->proxPtr_livro;
    }

    printf("Livro não encontrado.\n");
}
