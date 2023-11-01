#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


char *input_string(const char *txt){
    char buffer[256];
    printf("%s: ", txt);
    fflush(stdin);  //limpar o buffer 
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  //remove a quebra de linha, se houver
    return strdup(buffer);
}


int validar_livro(){

}

void cadastrar_livro(){
    struct st_livro *novo_livro = malloc(sizeof(struct st_livro));
    if (novo_livro) {
		int pgs;
    
		novo_livro -> titulo = input_string("Titulo");
        novo_livro -> autor = input_string("Autor");
        novo_livro -> genero = input_string("Genero");
		printf("Quantidade de paginas: ");
    	scanf("%d", &pgs);
		novo_livro -> qtd_paginas = pgs;
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
            fprintf(db, "%s, %s, %s, %d\n", novo_livro->titulo, novo_livro->autor, novo_livro->genero, novo_livro->qtd_paginas);
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
		printf("oi");
		while (fgets(linha, sizeof(linha), db)) {
        	if (sscanf(linha, "%99[^,], %99[^,], %99[^,], %d", livro.titulo, livro.autor, livro.genero, &livro.qtd_paginas) == 4) {
            	printf("Titulo: %s\nAutor: %s\nGenero: %s\nPaginas: %d\n\n\n", livro.titulo, livro.autor, livro.genero, livro.qtd_paginas);
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

