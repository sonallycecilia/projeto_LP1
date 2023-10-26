#include <stdio.h>
#include <string.h>
#include "utils/headers.h"


struct livros livro;

int main(){
	int option;

	do{
		option = menu();

		switch (option){
		case 1:
			cadastrar_livro(livro);
			break;

		case 2:
			pegar_info();
			break;

		case 3:
			pegar_chave();

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