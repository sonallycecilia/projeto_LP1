#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "utils/functions/functions.h"
#include "utils/structs/structs.h"

struct st_livro livro;

int main(){
	setlocale(LC_ALL, "Portuguese_Brazil");
	int option;

	do{
		option = menu();

		switch (option){
		case 1:
			cadastrar_livro();
			break;

		case 2:
			pegar_info();
			break;

		case 3:
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