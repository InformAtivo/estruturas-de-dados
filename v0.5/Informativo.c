#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct{//deverá haver maior especificação no futuro
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
    int marcador_responsavel;//marcador de conclusão
    int marcador_dono;//marcardo de certificaçnao de conclusão
}tarefa;


typedef struct{
    char titulo[51];
    char descricao[261];
    usuario dono;//o dono também pode estar numa estrutura de listas
    tarefa *task;
    long deadline;//procurar biblioteca de tempo e funcionamento da mesma
    comentario *coment;//lista de comentarios sobre a pauta
}pauta;


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
    scanf("%s",&pautaLocal.titulo);
    printf("faca uma breve descricao da pauta\n->");
    scanf("%s",&pautaLocal.descricao);
    pautaLocal.dono.nome = userAtual.nome;
    while(escolha==Y){
        printf("deseja adicionar uma tarefa? (Y/N)\n->");
        scanf("%c",&escolha);
        while( (escolha!=Y) || (escolha!=N) ){
            printf("opcao invalida, adicione Y = sim, N = nao\n->");
            scanf("%c",&escolha);
        }
        if (escolha == Y){
            defTarefa(pautaLocal,userAtual);
        }
    }
    printf("defina uma data no estilo dd/mm/yyyy");
    scanf("%d/%d/%d",&dia,&mes,&ano);
    pautaLocal.deadline = Urgencia(dia,mes,ano);
}

int menuPrincipal(){
    int escolha;
    printf("O que voce deseja fazer?\n");
    printf("1. Criar Pauta\n");
    printf("2. Procurar Pauta\n");
    printf("3. Procurar Tarefa");
    printf("4. ");
    printf("0. Sair\n");
    printf("-> ");
    scanf("%d",&escolha);
    return escolha;
}
usuario defUser(usuario usual){
    printf("bom dia, qual o seu nome?\n->");
    scanf("%s",&usual.nome);
    printf("qual a sua funcao?\n");
    printf("1 = design\n");
    printf("2 = CC\n");
    printf("3 = Admin\n->");
    scanf("%d",&usual.cargo);
    return(usual);

}
pauta
void exeComando(int comando){
    switch(comando){
    case 0:
        return;
    case 1:
        defPauta();
    case 2:
        break;
    }
}

int main(){
    int comando;
    usuario atual;
    atual = defUser(atual);
    printf("nome = %s \ncargo = %d\n",atual.nome,atual.cargo);
    comando = menuPrincipal();
    while (comando!=0){
        exeComando(comando);
        printf("comando = %d\n",comando);
        comando = menuPrincipal();

    }

}
