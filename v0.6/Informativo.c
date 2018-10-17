#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{//deverá haver maior especificao no futuro
    char nome[51];
    int cargo;
}usuario;

typedef struct Comentario{
    usuario usual;
    char texto [261];
    struct Comentario *proximo;
}comentario;

typedef struct task{//Luiz está finalizando esse struct
    int tipo;
    struct task *anterior;
    struct task *proxima;
    char desc[261];
    usuario responsavel;//marcador de quem pegou a tarefa
    int marcador_responsavel;//marcador de conclus‹o
    int marcador_dono;//marcardo de certificaçnao de conclus‹o
}tarefa;


typedef struct{
    char titulo[51];
    char descricao[261];
    usuario dono;//o dono também pode estar numa estrutura de listas
    tarefa *task;
    int dia;
    int mes;
    int ano;
    long deadline;//procurar biblioteca de tempo e funcionamento da mesma
    comentario *coment;//lista de comentarios sobre a pauta
}pauta;


//estruturas daqui pra cima-----------------------------------------------------
//Funcoes daqui pra baixo---------------------------------------


long Urgencia(int dia, int mes, int ano)
{
    long importancia;
    time_t atual;
    struct tm str_time;
    time_t time_of_day;

    str_time.tm_year = ano-1900;
    str_time.tm_mon = mes-1;
    str_time.tm_mday = dia;
    str_time.tm_hour = 0;
    str_time.tm_min = 0;
    str_time.tm_sec = 0;
    str_time.tm_isdst = 0;

    time_of_day = mktime (&str_time);
    atual = time (NULL);
    importancia = (time_of_day)-(atual);
    return (importancia);
}


pauta defPauta(usuario userAtual){
    char escolha = 'Y';
    int dia,mes,ano;
    pauta pautaLocal;
    printf("defina titulo da pauta\n->");
    fflush(stdin);
    fgets(pautaLocal.titulo, 50, stdin);
    printf("faca uma breve descricao da pauta\n->");
    fflush(stdin);
    fgets(pautaLocal.descricao, 250, stdin);
    size_t destination_size = sizeof (pautaLocal.dono.nome);
    strncpy(pautaLocal.dono.nome, userAtual.nome, destination_size);
    pautaLocal.dono.nome[destination_size - 1] = '\0';
    printf("deseja adicionar uma tarefa? (Y/N)\n->");
    fflush(stdin);
    scanf("%c",&escolha);
    while(escolha){
        while( (escolha!='Y') && (escolha!='N') ){
            printf("%c nao eh uma opcao valida, adicione Y = sim, N = nao\n->",escolha);
            fflush(stdin);
            scanf("%c",&escolha);
        }
        if (escolha == 'Y'){
            defTarefa(pautaLocal);// defTarefa(pautaLocal,userAtual); // criar defTarefa
        }else if (escolha == 'N')
            break;
        printf("deseja adicionar uma tarefa? (Y/N)\n->");
        fflush(stdin);
        scanf("%c",&escolha);
    }
    printf("defina uma data no estilo dd/mm/yyyy\n->");
    scanf("%d/%d/%d",&pautaLocal.dia,&pautaLocal.mes,&pautaLocal.ano);
    pautaLocal.deadline = Urgencia(pautaLocal.dia,pautaLocal.mes,pautaLocal.ano);
}

void defTarefa(pauta pautaLocal){//n‹o acho que precisa ser enviado nome do usuario
    char escolha;
    tarefa *aux;
    printf("adicionando tarefa a pauta [%s]\n",pautaLocal.titulo);
    tarefa *task=malloc(sizeof(tarefa));
    if (pautaLocal.task==NULL){
        pautaLocal.task=task;
        task->anterior=NULL;
        task->proxima=NULL;
    }
    else{
        aux=pautaLocal.task;
        while (task->proxima!=NULL)
            aux=aux->proxima;
        aux->proxima=task;
        task->anterior=aux;
    }task->proxima=NULL;
    printf("qual o tipo da tarefa:\n'0' para texto\n'1' para foto\n'2' para grafico\n->");//separar em varios printf para ficar mais organizado;
    scanf("%d",task->tipo);
    printf("adicione uma breve descri‹o da tarefa\n->");
    fflush(stdin);
    fgets(task->desc, 260, stdin);
/*    printf("\ndeseja colocar uma deadline diferente da dada a pauta? (y/n)\n->");//esse codigo vai entrar caso cheguemos a conclus‹o que a task pode ter outra varia‹o de deadline.
    fflush(stdin);
    scanf("%c",escolha);
    while( (escolha!='Y') && (escolha!='N') ){
        printf("%c nao eh uma opcao valida, adicione Y = sim, N = nao\n->",escolha);
        fflush(stdin);
        scanf("%c",&escolha);
    }
    if (escolha == 'Y'){
        fflush(stdin);
        printf("defina uma data no estilo dd/mm/yyyy\n->");
        scanf("%d/%d/%d",task->dia,task->mes,task->ano);
    }else{
        task->dia=pautaLocal->dia;
        task->mes=pautaLocal->mes;
        task->ano=pautaLocal->ano;
    }*/
    printf("gostaria de adicionar mais alguma tarefa? (Y/N)\n->");
    fflush(stdin);
    scanf("%d",&escolha);
    while( (escolha!='Y') && (escolha!='N') ){
        printf("%c nao eh uma opcao valida, adicione Y = sim, N = nao\n->",escolha);
        fflush(stdin);
        scanf("%c",&escolha);
    }if (escolha=='Y')
        defTarefa(pautaLocal);
    else if (escolha=='N')
        return;
}


int menuPrincipal(){
    int escolha;
    printf("O que voce deseja fazer?\n");
    printf("1. Criar Pauta\n");
    printf("2. Procurar Pauta\n");
    printf("3. Procurar Tarefa\n");
    printf("4. \n");
    printf("0. Sair\n");
    printf("->");
    scanf("%d",&escolha);
    return escolha;
}

usuario defUser(usuario usual){
    printf("bom dia, qual o seu nome?\n->");
    fflush(stdin);
    fgets(usual.nome, 50, stdin);
    printf("qual a sua funcao? (escolha um numero)\n");
    printf("1 = design\n");
    printf("2 = CC\n");
    printf("3 = Admin\n->");
    fflush(stdin);
    scanf("%d",&usual.cargo);
    return(usual);
}

//executaveis --------------------


void exeComando(int comando,usuario userAtual){
    switch(comando){
    case 0:
        break;
    case 1:
        defPauta(userAtual);
        break;
    default:
        break;
    }
    return;
}

int main(){
    int comando;
    usuario atual;
    atual = defUser(atual);
    printf("nome = %s \ncargo = %d\n",atual.nome,atual.cargo);
    do{
        comando = menuPrincipal();
        exeComando(comando,atual);
    }while (comando!=0);
    return 0;
}
