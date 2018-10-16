#include <stdio.h>
#include <stdlib.h>

struct Node {//estrutura da tarefa, não sei como fzr isso
	int num;
	struct Node *prox;
};
typedef struct Node node;

int tam;
//adicionando inputs possiveis para as tarefas em questão de prioridade
void inicia(node *TAREFAS);
int menu(void);
void opcao(node *TAREFAS, int op);
node *criaNo();
void insereFim(node *TAREFAS);
void insereInicio(node *TAREFAS);
void exibe(node *TAREFAS);
void libera(node *TAREFAS);
void insere(node *TAREFAS);
node *retiraInicio(node *TAREFAS);
node *retiraFim(node *TAREFAS);
node *retira(node *TAREFAS);


int main(void)
{
	node *TAREFAS = (node *)malloc(sizeof(node));
	if (!TAREFAS) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else {
		inicia(TAREFAS);
		int opt;

		do {
			opt = menu();
			opcao(TAREFAS, opt);
		} while (opt);

		free(TAREFAS);
		return 0;
	}
}

void inicia(node *TAREFAS)//nada dentro da lista de tarefas
{
	TAREFAS->prox = NULL;
	tam = 0;
}

int menu(void)
{
	int opt;

	printf("Escolha a opcao\n");
	printf("0. Sair\n");
	printf("1. Zerar lista\n");
	printf("2. Exibir lista\n");
	printf("3. Adicionar node no inicio\n");
	printf("4. Adicionar node no final\n");
	printf("5. Escolher onde inserir\n");
	printf("6. Retirar do inicio\n");
	printf("7. Retirar do fim\n");
	printf("8. Escolher de onde tirar\n");
	printf("Opcao: "); scanf("%d", &opt);

	return opt;
}

void opcao(node *TAREFAS, int op)
{
	node *tmp;
	switch (op) {
	case 0:
		libera(TAREFAS);
		break;

	case 1:
		libera(TAREFAS);
		inicia(TAREFAS);
		break;

	case 2:
		exibe(TAREFAS);
		break;

	case 3:
		insereInicio(TAREFAS);
		break;

	case 4:
		insereFim(TAREFAS);
		break;

	case 5:
		insere(TAREFAS);
		break;

	case 6:
		tmp = retiraInicio(TAREFAS);
		printf("Retirado: %3d\n\n", tmp->num);
		break;

	case 7:
		tmp = retiraFim(TAREFAS);
		printf("Retirado: %3d\n\n", tmp->num);
		break;

	case 8:
		tmp = retira(TAREFAS);
		printf("Retirado: %3d\n\n", tmp->num);
		break;

	default:
		printf("Comando invalido\n\n");
	}
}

//fazendo as funcoes funcionarem
int vazia(node *TAREFAS)
{
	if (TAREFAS->prox == NULL)
		return 1;
	else
		return 0;
}

node *aloca()
{
	node *novo = (node *)malloc(sizeof(node));
	if (!novo) {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else {
		printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}


void insereFim(node *TAREFAS)
{
	node *novo = aloca();
	novo->prox = NULL;

	if (vazia(TAREFAS))
		TAREFAS->prox = novo;
	else {
		node *tmp = TAREFAS->prox;

		while (tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
	tam++;
}

void insereInicio(node *TAREFAS)
{
	node *novo = aloca();
	node *oldHead = TAREFAS->prox;

	TAREFAS->prox = novo;
	novo->prox = oldHead;

	tam++;
}

void exibe(node *TAREFAS)
{
	system("clear");
	if (vazia(TAREFAS)) {
		printf("sem tarefas!\n\n");
		return;
	}

	node *tmp;
	tmp = TAREFAS->prox;
	printf("Tarefas:");
	while (tmp != NULL) {
		printf("%5d", tmp->num);
		tmp = tmp->prox;
	}
	printf("\n        ");
	int count;
	for (count = 0; count < tam; count++)
		printf("  ^  ");
	printf("\nOrdem:");
	for (count = 0; count < tam; count++)
		printf("%5d", count + 1);


	printf("\n\n");
}

void libera(node *TAREFAS)
{
	if (!vazia(TAREFAS)) {
		node *proxNode,
			*atual;

		atual = TAREFAS->prox;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

void insere(node *TAREFAS)
{
	int pos,
		count;
	printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", tam);
	scanf("%d", &pos);

	if (pos>0 && pos <= tam) {
		if (pos == 1)
			insereInicio(TAREFAS);
		else {
			node *atual = TAREFAS->prox,
				*anterior = TAREFAS;
			node *novo = aloca();

			for (count = 1; count < pos; count++) {
				anterior = atual;
				atual = atual->prox;
			}
			anterior->prox = novo;
			novo->prox = atual;
			tam++;
		}

	}
	else
		printf("Elemento invalido\n\n");
}

node *retiraInicio(node *TAREFAS)
{
	if (TAREFAS->prox == NULL) {
		printf("Não há tarefas\n");
		return NULL;
	}
	else {
		node *tmp = TAREFAS->prox;
		TAREFAS->prox = tmp->prox;
		tam--;
		return tmp;
	}

}

node *retiraFim(node *TAREFAS)
{
	if (TAREFAS->prox == NULL) {
		printf("Não há tarefas para excluir\n\n");
		return NULL;
	}
	else {
		node *ultimo = TAREFAS->prox,
			*penultimo = TAREFAS;

		while (ultimo->prox != NULL) {
			penultimo = ultimo;
			ultimo = ultimo->prox;
		}

		penultimo->prox = NULL;
		tam--;
		return ultimo;
	}
}

node *retira(node *TAREFAS)
{
	int opt,
		count;
	printf("Que posicao, [de 1 ate %d] voce deseja retirar: ", tam);
	scanf("%d", &opt);

	if (opt>0 && opt <= tam) {
		if (opt == 1)
			return retiraInicio(TAREFAS);
		else {
			node *atual = TAREFAS->prox,
				*anterior = TAREFAS;

			for (count = 1; count < opt; count++) {
				anterior = atual;
				atual = atual->prox;
			}

			anterior->prox = atual->prox;
			tam--;
			return atual;
		}

	}
	else {
		printf("Elemento invalido\n\n");
		return NULL;
	}
}
