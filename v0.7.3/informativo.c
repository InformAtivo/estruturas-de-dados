
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#define CAMINHO "c:\\pauta\\"


typedef struct{//dever� haver maior especificao no futuro
    char nome[51];
    int cargo;
}usuario;

typedef struct task{//Luiz est� finalizando esse struct
    int tipo;
    char desc[261];
    usuario responsavel;//marcador de quem pegou a tarefa
    int marcador_responsavel;//marcador de conclus�o
    int marcador_dono;//marcardo de certifica�nao de conclus�o
}tarefa;

typedef struct{
    char titulo[51];
    char descricao[261];
    usuario dono;//o dono tamb�m pode estar numa estrutura de listas
    tarefa task[20];
    int dia;
    int mes;
    int ano;
    long deadline;//procurar biblioteca de tempo e funcionamento da mesma
}pauta;


//estruturas daqui pra cima-----------------------------------------------------
//Funcoes daqui pra baixo---------------------------------------


char criarpath(char *nome){
    char path[100];
    path = CAMINHO ++ nome;
    return path[100];
}


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

usuario assingUser(){
    usuario usuarioLocal;
    printf("defina o nome do usuario\n->");
    fflush(stdin);
    fgets(usuarioLocal.nome, 50, stdin);
    printf("defina o cargo do usuario\n");
    printf("1 = design\n");
    printf("2 = CC\n");
    printf("3 = Admin\n->");
    fflush(stdin);
    scanf("%d",&usuarioLocal.cargo);
    return usuarioLocal;
}

pauta defTarefa(pauta pautaLocal){//n�o acho que precisa ser enviado nome do usuario
    char escolha;
    int n=0;
    tarefa aux;
    printf("adicionando tarefa a pauta [%s]\n",pautaLocal.titulo);
    while(pautaLocal.task[n].tipo!=0){
        n++;
        if (n ==19){
            printf("pauta com muitas tarefas, crie uma nova pauta para adicionar mais tarefas\n");
            return(pautaLocal);
        }
    }
    printf("para qual funcaoo se encaixa essa tarefa?\n");
    printf("1 = design\n");
    printf("2 = CC\n");
    fflush(stdin);
    scanf("%d",&pautaLocal.task[n].tipo);
    printf("faca uma breve descricao da tarefa\n->");
    fflush(stdin);
    fgets(pautaLocal.task[n].desc, 250, stdin);
    printf("voce deseja atribuir essa tarefa a alguem? (Y/N)\n->");
    fflush(stdin);
    scanf("%c",&escolha);
    while( (escolha!='Y') && (escolha!='N') ){
        printf("%c nao eh uma opcao valida, desaja atribuir a tarefa? Y = sim, N = nao\n->",escolha);
        fflush(stdin);
        scanf("%c",&escolha);
    }
    if (escolha == 'Y'){
        pautaLocal.task[n].responsavel = assingUser();//criar funcao assingUser
    }
    pautaLocal.task[n].marcador_dono = 0;
    pautaLocal.task[n].marcador_responsavel = 0;
    return(pautaLocal);
}


void defPauta(usuario userAtual){
    char escolha = 'Y';
    int dia,mes,ano,x;
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
    for(x=0;x<20;x++){
        pautaLocal.task[x].tipo = 0;
    }
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
            pautaLocal = defTarefa(pautaLocal);// defTarefa(pautaLocal,userAtual); // criar defTarefa
        }else if (escolha == 'N')
            break;
        printf("deseja adicionar uma tarefa? (Y/N)\n->");
        fflush(stdin);
        scanf("%c",&escolha);
    }
    printf("defina uma data limite no estilo dd/mm/yyyy\n->");
    scanf("%d/%d/%d",&pautaLocal.dia,&pautaLocal.mes,&pautaLocal.ano);
    pautaLocal.deadline = Urgencia(pautaLocal.dia,pautaLocal.mes,pautaLocal.ano);
    
    FILE *f;
    
    //Fazer uma funcao para escrever a pauta num arquivo
    f = fopen(criarpath(pautaLocal.nome),"wb+");//pauta.titulo
    //criar um While, para andar at� o final do documento
    fwrite(&pautaLocal,sizeof(pautaLocal),1,f);
    fclose(f);
    return;
}



int menuPrincipal(){
    int escolha;
    printf("O que voce deseja fazer?\n");
    printf("1. Criar Pauta\n");
    printf("2. Mostrar Pautas\n");
    printf("3. \n");
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
    printf("qual o seu cargo? (escolha um numero)\n");
    printf("1 = design\n");
    printf("2 = CC\n");
    printf("3 = Admin\n->");
    fflush(stdin);
    scanf("%d",&usual.cargo);
    return(usual);
}

void showPautas(){
    FILE *f;
    pauta pautaTeste;
    f = fopen("pautas","rb");
    while(1){
        fread(&pautaTeste,sizeof(pautaTeste),1,f);
        if(feof(f)!=0){
            break;
        }
        printf("\n\nDono:%s\nTitulo:%s\nDescricao:%s",pautaTeste.dono.nome,pautaTeste.titulo,pautaTeste.descricao);
        printf("\nDeadline: %d/%d/%d\n",pautaTeste.dia,pautaTeste.mes,pautaTeste.ano);
    }
    fclose(f);
}





//executaveis --------------------

void exeComando(int comando,usuario userAtual){
    switch(comando){
        case 0:
            break;
        case 1:
            defPauta(userAtual);
            break;
        case 2:
            showPautas();
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
