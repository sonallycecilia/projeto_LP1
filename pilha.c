//operador de seta usa para mudar o valor do ponteiro atraves da seta
//no pop nao interessa o valor, apenas o topo (ptr), retorna o valor removido

#include <stdio.h>
#include <stdlib.h>

/* Esse código pode ser encontrado no "C: Como programar" do Deitel.
O arquivo que estou mandando é uma versão mais comentada do código
lá presente. */

/* Estrutura básica de um nó para pilha. Pode conter outras
variáveis. No caso, o nó é uma estrutura autorreferenciada, de modo
que uma de suas variáveis diz respeito a um ponteiro para algo do
mesmo tipo. */

struct node {
	int valor;
	struct node *proxPtr;
};

/* Redefinição de tipos envolvendo estruturas e os
ponteiros para elas */


typedef struct node Node;
typedef Node* NodePtr;

/* Operações básicas de pilhas. O que caracteriza uma
pilha é o fato de que há uma lógica "last in, first out", ou
seja, o último que entrou é o primeiro a sair. Uma
analogia é um baralho de cartas ou uma pilha de pratos. 
*/

void push(NodePtr *topoPtr, int valor_novo);
int pop(NodePtr *topoPtr);
int esta_vazia(NodePtr topoPtr);
void imprime_pilha(NodePtr atualPtr);

/* Função que insere um novo nó na pilha, com o valor
que for informado. */

void push(NodePtr *topoPtr, int valor_novo)
{
	// Cria um novo nó e aloca memoria para ele
	NodePtr novoPtr;
	novoPtr = (NodePtr) malloc(sizeof(Node));
	
	// Caso a alocação acima seja bem-sucedida (tem memória)
	if(novoPtr != NULL)
	{
		// Ajuste o valor desse novo nó para o informado
		novoPtr -> valor = valor_novo;
		// Faca com que o proximo nó desse no seja o topo
		// da pilha (que, agora, é o penúltimo elemento)
		novoPtr -> proxPtr = *topoPtr;
		// Mude o topo da pilha para esse novo nó
		*topoPtr = novoPtr;
	}
}

/* Função que remove um elemento da pilha (no caso, o do topo) 
*/

int pop(NodePtr *topoPtr)
{
	// Armazena um nó temporário (lidar com remoções)
	NodePtr tempPtr;
	// Armazenar o valor do nó removido (para retorno)
	int valor_removido;
	
	// Fazer o nó temporario apontar para o topo da pilha
	tempPtr = *topoPtr;
	// Armazena o valor do nó a ser removido
	valor_removido = (*topoPtr) -> valor;
	// Faca com que o topo da pilha seja o próximo (o
	// topo será removido, então precisamos de um novo topo)
	*topoPtr = (*topoPtr) -> proxPtr;
	
	// A memória referente ao nó removido é liberada
	// Para isso, precisamos de um ponteiro para essa memória
	// Esse procedimento é feito depois de mudarmos o topo
	free(tempPtr);
	return valor_removido;
}

void imprime_pilha(NodePtr atualPtr)
{
	if(atualPtr == NULL)
	{
		printf("A pilha esta vazia\n");
	}
	else
	{
		// Enquanto tiver nós para acessar
		while(atualPtr != NULL)
		{
			// Imprima o valor desse nó
			printf("%d > ", atualPtr -> valor);
			// Faça com que o ponteiro aponte p/ próximo
			atualPtr = atualPtr -> proxPtr;
		}
		
		// Quando não tiver mais elementos a avançar
		printf("NULO\n");
	}
}

int esta_vazia(NodePtr topoPtr)
{
	return topoPtr == NULL;
}

int main()
{
	NodePtr pilhaPtr = NULL;
	
	imprime_pilha(pilhaPtr);
	push(&pilhaPtr, 10);
	imprime_pilha(pilhaPtr);
	push(&pilhaPtr, 20);
	imprime_pilha(pilhaPtr);
	pop(&pilhaPtr);
	imprime_pilha(pilhaPtr);
	
}
ling1_pilha.c
Exibindo ling1_pilha.c…