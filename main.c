#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "utils/functions/functions.h"

struct st_livro livro;

int main()
{
	carregar_dados();

	setlocale(LC_ALL, "Portuguese");
	int option;
	int estante;
	int filtro;
	int favorito;

	do
	{
		option = menu();

		switch (option)
		{
		case 1:
			cadastrar_livro();
			break;

		case 2:
			do
			{
				estante = estante_menu();

				switch (estante)
				{
				case 1:
					visualizar_livros();
					break;
				case 2:
					printf("\nTemos %d livro(s) na estante!\n", contar_livros());
					break;
				case 3:
					editar_status();
					break;
				case 4:
					remover_livro();
					break;

				case 0:
					printf("\nVoltando para o menu...\n");
					break;
				default:
					printf("\nOpcao invalida!\n");
					break;
				}
			} while (estante != 0);
			break;

		case 3:
			do
			{
				filtro = filtrar_menu();
				switch (filtro)
				{
				case 1:
					filtrar(1);
					break;
				case 2:
					filtrar(2);
					break;
				case 3:
					filtrar(3);
					break;
				case 4:
					filtrar(4);
					break;
				case 0:
					printf("\nVoltando para o menu...\n");
					break;
				default:
					printf("\nOpcao invalida!\n");
					break;
				}
			} while (filtro != 0);
			break;

		case 4:
			do
			{
				favorito = favorito_menu();
				switch (favorito)
				{
				case 1:
					pre_add_favorito();
					break;

				case 2:
					pre_remover_favorito();
					break;
				case 3:
					visualizar_favoritos();
					break;
				case 0:
					printf("\nVoltando para o menu...\n");
					break;
				default:
					printf("\nOpcao invalida!\n");
					break;
				}
			} while (favorito != 0);
			break;

		case 0:
			printf("\nPROGRAMA ENCERRADO!\n\n");
			break;

		default:
			printf("\nOpcao invalida!\n");
			break;
		}
	} while (option != 0);

	return 0;
}
