#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "utils/functions/functions.h"
#include "utils/structs/structs.h"

struct st_livro livro;

int main()
{
	carregar_livros();
	setlocale(LC_ALL, "Portuguese_Brazil");
	int option;
	int filtro;

	do
	{
		option = menu();

		switch (option)
		{
		case 1:
			cadastrar_livro();
			break;

		case 2:
			pegar_info();
			break;

		case 3:
			filtro = filtrar_m();
			switch (filtro)
			{
			case 1:
				filtrar(1);
				break;

			case 2:
				filtrar(2);
				break;

			default:
				printf("Opcao invalida.\n");
				limpar_buffer();
				break;
			}
			break;

		case 0:
			printf("Programa encerrado.");
			break;

		default:
			printf("Opcao invalida.\n");
			limpar_buffer();
			break;
		}

	} while (option != 0);

	return 0;
}