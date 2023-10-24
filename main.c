#include <stdio.h>
#include <string.h>
#include "headers.h"


struct livro livros;

int main(){
	int option;

	do{
		option = menu();

		switch (option){
		case 1:
			cadastrar_livro(livros);
			break;

		case 0:
			printf("Programa encerrado.");
			break;

		default:
		printf("Opcao invalida.");
			break;
		}
	}while(option != 0);

	
	return 0;
}