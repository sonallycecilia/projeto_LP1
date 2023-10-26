#include <string.h>
#include <stdio.h>

struct livros{
	char titulo[100];
	char autor[50];
	char genero[50];
	int qtd_paginas;
};

struct livros livro1;
int menu();
void cadastrar_livro();
void pegar_info();

int menu(){
	int op;
	
	printf("[1] - Cadastrar Livro\n");
	printf("[2] - Ver livros\n");
	printf("[3] - Filtrar\n");
	printf("[0] - Sair\n");
	scanf("%d", &op);
	
	return op;
}


void cadastrar_livro() {
    FILE *db;
    int res = 0;

    db = fopen("database/livros.txt", "a");
    if (db) {
        do {
            printf("- Digite as informacoes do livro -");

			getchar();
			printf("\nTitulo: ");
			fgets(livro1.titulo, 100, stdin);
			livro1.titulo[strcspn(livro1.titulo, "\n")] = '\0';

			printf("\nAutor: ");
			fgets(livro1.autor, 50, stdin);
			livro1.autor[strcspn(livro1.autor, "\n")] = '\0';

			printf("\nGenero: ");
			fgets(livro1.genero, 50, stdin);
			livro1.genero[strcspn(livro1.genero, "\n")] = '\0';

			printf("\nTotal de paginas: ");
			scanf("%d", &livro1.qtd_paginas);

            printf("- Confirme as informacoes -\n");
            printf("Titulo: %s\n", livro1.titulo);
            printf("Autor: %s\n", livro1.autor);
            printf("Genero: %s\n", livro1.genero);
            printf("Total de paginas: %d\n", livro1.qtd_paginas);

            printf("Digite [0] - Nao / [1] - Sim: ");
            scanf("%d", &res);
			getchar();
			
			//ainda tem que add funcao de verificar repetido

            if (res) {
                fprintf(db, "%s, %s, %s, %d\n", livro1.titulo, livro1.autor, livro1.genero, livro1.qtd_paginas);
                printf("Livro cadastrado com sucesso.\n");
            } else {
                printf("Cadastro de livro cancelado. Tente Novamente.\n");
            }
        } while (!res);

        fclose(db);
    } else {
        printf("Base de dados não encontrada.\n");
    }
}


void pegar_info(){
	FILE *db;
	char c;
	db = fopen("database/livros.txt", "r");
	
	if (db){
		while((c = getc(db)) != EOF){
			printf("%c", c);
		}
		fclose(db);
	}
	else{
		printf("Base de dados nao encontrada\n");
	}

}

