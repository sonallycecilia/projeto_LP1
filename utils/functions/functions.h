#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct st_livro{
	char *titulo;
	char *autor;
	char *genero;
	int qtd_paginas;
	struct st_livro *proxPtr_livro;
};

struct st_livro *lista_livros = NULL;

int menu(){
	int op;
	
	printf("[1] - Cadastrar Livro\n");
	printf("[2] - Ver livros\n");
	printf("[3] - Filtrar\n");
	printf("[0] - Sair\n");
	scanf("%d", &op);
	
	return op;
}

int verificar_pos_ordem_alfa(){
    
}


char *input_string(const char *txt){
    char buffer[256];
    printf("%s: ", txt);
    fflush(stdin);  //limpar o buffer 
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  //remove a quebra de linha, se houver
    return strdup(buffer); //strdup duplica as strings e, em seguida, libere a memória alocada no final do programa ou quando não precisar mais das strings.
}

void formatar_titulo(char *string){
    while(*string != '\0'){
        *string = toupper(*string);
        while(*string != ' ' && *string != '\0'){
            string++;
        }
        string++;
    }
}


void cadastrar_livro(){
   struct st_livro* novo_livro = (struct st_livro*) malloc(sizeof(struct st_livro)); //mudei
   //struct st_livro *novo_livro = malloc(sizeof(struct st_livro));
    if (novo_livro) {
		novo_livro -> titulo = input_string("Titulo");
        formatar_titulo(novo_livro->titulo);
        novo_livro -> autor = input_string("Autor");
        formatar_titulo(novo_livro->autor);
        novo_livro -> genero = input_string("Genero");
        formatar_titulo(novo_livro->genero);
		printf("Quantidade de paginas: ");
    	scanf("%d", &novo_livro->qtd_paginas);
        novo_livro -> proxPtr_livro = NULL; //aqui vai ser modificado

        if (lista_livros == NULL) {
            lista_livros = novo_livro;
        } 
		else{
            struct st_livro *atual = lista_livros;
            while (atual -> proxPtr_livro != NULL){
                atual = atual -> proxPtr_livro;
            }
            atual -> proxPtr_livro = novo_livro;
        }

        FILE *db = fopen("database/livros.txt", "a");
        if (db){
			printf("Livro cadastrado com sucesso.\n");
            fprintf(db, "%s | %s | %s | %d\n", novo_livro->titulo, novo_livro->autor, novo_livro->genero, novo_livro->qtd_paginas);
            fclose(db);
        } 
		else{
            printf("Não foi possivel abrir o arquivo de banco de dados.\n");
        }
    } 
	else {
        printf("Não ha espaço disponivel para o livro.\n");
    }
}


void pegar_info(){
	FILE *db;
	struct st_livro livro;
	db = fopen("database/livros.txt", "r");
	char linha[256];

	if (db){
		while (fgets(linha, sizeof(linha), db)) {
        	if (sscanf(linha, "%[^|] | %[^|] | %[^|] | %d", livro.titulo, livro.autor, livro.genero, &livro.qtd_paginas) == 4) {
            	printf("Titulo: %s\nAutor: %s\nGenero: %s\nPaginas: %d\n\n", livro.titulo, livro.autor, livro.genero, livro.qtd_paginas);
        } 
		else {
            printf("Erro ao ler a linha: %s", linha);
        }
    }

        fclose(db);
    } 
	else{
        printf("Base de dados não encontrada\n");
    }
}

