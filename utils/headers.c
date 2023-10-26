#include <stdio.h>
#include "headers.h"

int menu(){
	int op;
	
	printf("[1] - Cadastrar Livro\n");
	printf("[2] - Ver Livros\n");
	printf("[0] - Sair\n");
	
	return op;
}

void cadastrar_livro(struct livros livro1){
	FILE *db;
	db = fopen("database/teste.txt", "a");

	if(db){
		printf("Digite as informacoes do livro\n");
		getchar();
		printf("Titulo: ");
		fgets(livro1.titulo, 100, stdin);
		printf("\nAutor: ");
		fgets(livro1.autor, 50, stdin);
		printf("\nGenero: ");
		fgets(livro1.genero, 50, stdin);
		printf("\nTotal de paginas: ");
		scanf("%d", &livro1.qtd_paginas);
		
		fprintf(db, "Titulo: %s, Autor: %s, Genero: %s, Paginas: %d\n", livro1.titulo, livro1.autor, livro1.genero, livro1.qtd_paginas);
		
		fclose(db);
	}
	else{
		printf("Base de dados nao encontrada.\n");
	}
}