#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "utils/functions/functions.h"

struct st_livro livro;

int main()
{
	carregar_livros();
	carregar_favoritos();

	setlocale(LC_ALL, "Portuguese");
	int option;
	int ver;
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
				ver = ver_menu();

				switch (ver)
				{
				case 1:
					visualizar_livros();
					break;
				case 2:
					printf("Temos %d livro(s) na estante.\n", contar_livros());
					break;
				case 3:
					editar_status();
					break;
				case 4:
					remover_livro();
					break;

				case 0:
					printf("Voltando para o menu.\n");
					break;
				default:
					printf("Opcao invalida.\n");
					break;
				}
			} while (ver != 0);
			break;

		case 3:
			do
			{
				filtro = filtrar_m();
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
					printf("Voltando para o menu.\n");
					break;
				default:
					printf("Opcao invalida.\n");
					break;
				}
			} while (filtro != 0);
			break;
			
		case 4:
			do
			{
				favorito = favorito_m();
				switch (favorito)
				{
				case 1:
					pre_add_favorito();
					break;

				case 2:
					pre_remover_favorito();
					break;

				case 0:
					printf("Voltando para o menu.\n");
					break;
				default:
					printf("Opcao invalida.\n");
					break;
				}
			} while (favorito != 0);
			break;

		case 0:
			printf("Programa encerrado.\n");
			break;

		default:
			printf("Opcao invalida.\n");
			break;
		}
	} while (option != 0);

	return 0;
}
