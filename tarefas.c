#include <stdlib.h>

struct Node() {
	int num;
	struct Node *prox;
}
typedef struct Node node;
int tam;
void init(node *TAREFAS);
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


int main() {
	node *TAREFAS = (node *)malloc(sizeof(node));
	if (!TAREFAS) {
		printf("sem memoria disponível");
	}
	else {
		inicia(TAREFAS);
		int opt;

		do {
			opt = menu();
			opcao(TAREFA, opt);
		}
		while (opt);
		free(TAREFAS);
		return(0)
	}
}
void inicia(node *TAREFA)
{
	TAREFA->prox = NULL;
	tam = 0;
}
int menu(void) {
	
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
void opcao(node *TAREFAS, int op){
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
		retiraInicio(TAREFAS);
		break;

	case 7:
		retiraFim(TAREFAS);
		break;

	case 8:
		retira(TAREFAS);
		break;

	default:
		prinitf("comando inválido\n\n");
	}
	node *aloca() {
		node *novo = (node *)malloc(sizeof(node));
		if (!novo) {
			printf("sem memoria sufiente! \n");
			exit(1);
		}
		else {
			printf("novo elemento: ");
			scanf("%d", &novo->num);
			return novo;
		}

	}
}
