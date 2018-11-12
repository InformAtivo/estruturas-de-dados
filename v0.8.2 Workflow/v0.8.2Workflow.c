#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    char nome[51];
    int cargo;
}usuario;

typedef struct task{
    int tipo;
    char desc[261];
    usuario responsavel;//marcador de quem pegou a tarefa
    int marcador_responsavel;//marcador de conclusao
    int marcador_dono;//marcardo de certifica�nao de conclusao
}tarefa;


typedef struct{
    char titulo[51];
    char descricao[261];
    usuario dono;
    tarefa task[20];
    int dia;
    int mes;
    int ano;
    long deadline;
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

usuario assingUser(){
    usuario usuarioLocal;
    printf("defina o nome do usuario\n->");
    fflush(stdin);
    fgets(usuarioLocal.nome, 50, stdin);
    usuarioLocal.nome[strlen(usuarioLocal.nome)-1]='\0';
    printf("defina o cargo do usuario\n");
    printf("1 = design\n");
    printf("2 = CC\n");
    printf("3 = Admin\n->");
    fflush(stdin);
    scanf("%d",&usuarioLocal.cargo);
    return usuarioLocal;
}

pauta defTarefa(pauta pautaLocal){
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
    pautaLocal.task[n].desc[strlen(pautaLocal.task[n].desc)-1]='\0';
    printf("voce deseja atribuir essa tarefa a alguem? (Y/N)\n->");
    fflush(stdin);
    scanf("%c",&escolha);
   while( (escolha!='Y') && (escolha!='N') ){
        printf("%c nao eh uma opcao valida, desaja atribuir a tarefa? Y = sim, N = nao\n->",escolha);
        fflush(stdin);
        scanf("%c",&escolha);
    }
    if (escolha == 'Y'){
        pautaLocal.task[n].responsavel = assingUser();
    }else{
        char str[] = "Ninguem";
        size_t destination_size = sizeof (pautaLocal.task[n].responsavel.nome);
        strncpy(pautaLocal.task[n].responsavel.nome, str, destination_size);
        pautaLocal.task[n].responsavel.nome[destination_size - 1] = '\0';
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
    pautaLocal.titulo[strlen(pautaLocal.titulo)-1]='\0';
    printf("faca uma breve descricao da pauta\n->");
    fflush(stdin);
    fgets(pautaLocal.descricao, 250, stdin);
    pautaLocal.descricao[strlen(pautaLocal.descricao)-1]='\0';
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
            pautaLocal = defTarefa(pautaLocal);
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
    f = fopen("pautas","ab");
    if(f==NULL) {
        printf("arquivo nao existente, criando um arquivo\n");
        fclose(f);
        f = fopen("pautas","wb+");
    }
    fwrite(&pautaLocal,sizeof(pautaLocal),1,f);
    fclose(f);
    return;
}

pauta editPauta(pauta pautaTeste[],int a){
    int n,x;
    printf("\no que voce deseja alterar? escolha o numero referente ao local\n");
    printf("\n1- Dono:%s\n2- Titulo:%s\n3- Descricao:%s",pautaTeste[a].dono.nome,pautaTeste[a].titulo,pautaTeste[a].descricao);
    printf("\n4- Deadline: %d/%d/%d\n\n",pautaTeste[a].dia,pautaTeste[a].mes,pautaTeste[a].ano);
    if (pautaTeste[a].task[0].tipo!=0){
        printf("Tarefas:\n");
        n=0;
        while(pautaTeste[a].task[n].tipo!=0){
            printf("5- Tarefa numero %d: %s\n",n+1,pautaTeste[a].task[n].desc);
            printf("6- Responsavel atual: %s\n",pautaTeste[a].task[n].responsavel.nome);
            printf("7- Estado da tarefa: ");
            if (pautaTeste[a].task[n].marcador_dono == 0){
                printf("em andamento\n");
            }else{
                printf("concluida\n");
            }
            printf("8- tipo da tarefa: %d\n",pautaTeste[a].task[n].tipo);
            n++;
        }
    }
    scanf("%d",&n);
}

void choosePauta(){
    printf("Qual pauta deve ser editada?\n->");
    FILE *f;
    f = fopen("pautas","rb");
    int n;
    int temp;
    pauta pautaTeste;
    if(f==NULL) {
        printf("arquivo nao existente, criando um arquivo\n");
        fclose(f);
        f = fopen("pautas","wb+");
        fclose(f);
        return;
    }
    int nPautas = 0;
    while(1){
        fread(&pautaTeste,sizeof(pautaTeste),1,f);
        if(feof(f)!=0){
            break;
        }
        nPautas++;
    }
    fclose(f);
    f = fopen("pautas","rb");
    pauta pautaLocal[nPautas];
    for(temp=0;temp<nPautas;temp++){
        fread(&pautaLocal[temp],sizeof(pautaTeste),1,f);
        if(feof(f)!=0){
            break;
        }
        printf("\n\nPauta numero %d\nDono:%s\nTitulo:%s\nDescricao:%s",temp+1,pautaLocal[temp].dono.nome,pautaLocal[temp].titulo,pautaLocal[temp].descricao);
        printf("\nDeadline: %d/%d/%d\n",pautaLocal[temp].dia,pautaLocal[temp].mes,pautaLocal[temp].ano);
        if (pautaLocal[temp].task[0].tipo!=0){
            printf("Tarefas:\n");
            n=0;
            while(pautaLocal[temp].task[n].tipo!=0){
                printf("Tarefa numero %d: %s\n",n+1,pautaLocal[temp].task[n].desc);
                printf("Responsavel atual: %s\n",pautaLocal[temp].task[n].responsavel.nome);
                printf("Estado da tarefa: ");
                if (pautaLocal[temp].task[n].marcador_dono == 0){
                    printf("em andamento\n");
                }else{
                    printf("concluida\n");
                }
                printf("tipo da tarefa: %d\n",pautaLocal[temp].task[n].tipo);
                n++;
            }
        }
    }
    fclose(f);
    printf("\nEscolha o numero da tarefa a ser editada(digite \"0\" para cancelar)\n");
    do{
        printf("os numeros das pautas estao no topo de sua descricao\n->");
        scanf("%d",&n);
        if(n==0) return;
    }while((n<0) || (n>nPautas));
    editPauta(pautaLocal,n);
    return;
}

int menuPrincipal(){
    int escolha;
    printf("O que voce deseja fazer?\n");
    printf("1. Criar Pauta\n");
    printf("2. Mostrar Pautas\n");
    printf("3. Editar uma pauta\n");
    printf("4. \n");//me de uma tarefa
    printf("0. Sair\n");
    printf("->");
    scanf("%d",&escolha);
    return escolha;
}

usuario defUser(usuario usual){
    printf("bom dia, qual o seu nome?\n->");
    fflush(stdin);
    fgets(usual.nome, 50, stdin);
    usual.nome[strlen(usual.nome)-1]='\0';
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
    int n;
    pauta pautaTeste;
    f = fopen("pautas","rb");
    if(f==NULL) {
        printf("arquivo nao existente, criando um arquivo\n");
        fclose(f);
        f = fopen("pautas","wb+");
        fclose(f);
        return;
    }
    while(1){
        fread(&pautaTeste,sizeof(pautaTeste),1,f);
        if(feof(f)!=0){
            break;
        }
        printf("\n\nDono:%s\nTitulo:%s\nDescricao:%s",pautaTeste.dono.nome,pautaTeste.titulo,pautaTeste.descricao);
        printf("\nDeadline: %d/%d/%d\n\n",pautaTeste.dia,pautaTeste.mes,pautaTeste.ano);
        if (pautaTeste.task[0].tipo!=0){
            printf("Tarefas:\n");
            n=0;
            while(pautaTeste.task[n].tipo!=0){
                printf("Tarefa numero %d: %s\n",n+1,pautaTeste.task[n].desc);
                printf("Responsavel atual: %s\n",pautaTeste.task[n].responsavel.nome);
                printf("Estado da tarefa: ");
                if (pautaTeste.task[n].marcador_dono == 0){
                    printf("em andamento\n");
                }else{
                    printf("concluida\n");
                }
                printf("tipo da tarefa: %d\n",pautaTeste.task[n].tipo);
                n++;
            }
        }
    }
    fclose(f);
    printf("\n");
    return;
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
    case 3:
        choosePauta();
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
