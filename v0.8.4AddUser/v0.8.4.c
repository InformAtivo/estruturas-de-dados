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
/* - função não é mais necessaria pois o defUser substitui a mesma.
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
*/
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
        pautaLocal.task[n].responsavel = defUser();
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
void writePauta(pauta pautaLocal){
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
    writePauta(pautaLocal);
    return;
}

pauta editPauta(pauta pautaTeste){
    int n,x,count = 5;
    char escolha;
    printf("\no que voce deseja alterar? escolha o numero referente ao local\n(escreva\"0\" para cancelar)\n");
    printf("\n1- Dono:%s\n2- Titulo:%s\n3- Descricao:%s",pautaTeste.dono.nome,pautaTeste.titulo,pautaTeste.descricao);
    printf("\n4- Deadline: %d/%d/%d\n\n",pautaTeste.dia,pautaTeste.mes,pautaTeste.ano);
    if (pautaTeste.task[0].tipo!=0){
        printf("Tarefas:\n");
        n=0;
        while(pautaTeste.task[n].tipo!=0){
            printf("%d- Descricao da tarefa numero %d: %s\n",count,n+1,pautaTeste.task[n].desc);
            count++;
            printf("%d- Responsavel atual: %s\n",count,pautaTeste.task[n].responsavel.nome);
            count++;
            printf("%d- Estado da tarefa: ",count);
            count++;
            if (pautaTeste.task[n].marcador_dono == 0){
                printf("em andamento\n");
            }else{
                printf("concluida\n");
            }
            printf("%d- tipo da tarefa: %d\n",count,pautaTeste.task[n].tipo);
            count++;
            n++;
        }
    }
    do{
        printf("os numeros das pautas estao ao lado de sua descricao\n->");
        scanf("%d",&n);
        if(n==0) return pautaTeste;
    }while((n<0) || (n>count));
    switch(n){
        case 1:
            printf("defina o novo dono da pauta\n->");
            fflush(stdin);
            fgets(pautaTeste.dono.nome, 50, stdin);
            pautaTeste.dono.nome[strlen(pautaTeste.dono.nome)-1]='\0';
            break;
        case 2:
            printf("defina o novo o titulo da pauta\n->");
            fflush(stdin);
            fgets(pautaTeste.titulo, 50, stdin);
            pautaTeste.titulo[strlen(pautaTeste.titulo)-1]='\0';
            break;
        case 3:
            printf("defina a nova descricao da pauta\n->");
            fflush(stdin);
            fgets(pautaTeste.descricao, 250, stdin);
            pautaTeste.descricao[strlen(pautaTeste.descricao)-1]='\0';
            break;
        case 4:
            printf("defina a nova data limite no estilo dd/mm/yyyy\n->");
            scanf("%d/%d/%d",&pautaTeste.dia,&pautaTeste.mes,&pautaTeste.ano);
            pautaTeste.deadline = Urgencia(pautaTeste.dia,pautaTeste.mes,pautaTeste.ano);
            break;
        default:
            n--;
            switch(n%4){
                case 0:
                    printf("defina a nova descricao da tarefa\n->");
                    fflush(stdin);
                    fgets(pautaTeste.task[(n/4)-1].desc, 250, stdin);
                    pautaTeste.task[(n/4)-1].desc[strlen(pautaTeste.task[(n/4)-1].desc)-1]='\0';
                    break;
                case 1:
                    printf("voce deseja atribuir essa tarefa a alguem? (Y/N)\n->");
                    fflush(stdin);
                    scanf("%c",&escolha);
                    while( (escolha!='Y') && (escolha!='N') ){
                        printf("%c nao eh uma opcao valida, desaja atribuir a tarefa? Y = sim, N = nao\n->",escolha);
                        fflush(stdin);
                        scanf("%c",&escolha);
                    }
                    if (escolha == 'Y'){
                        pautaTeste.task[(n/4)-1].responsavel = defUser();
                    }else{
                        char str[] = "Ninguem";
                        size_t destination_size = sizeof (pautaTeste.task[(n/4)-1].responsavel.nome);
                        strncpy(pautaTeste.task[(n/4)-1].responsavel.nome, str, destination_size);
                        pautaTeste.task[(n/4)-1].responsavel.nome[destination_size - 1] = '\0';
                    }
                    break;
                case 2:
                    printf("defina o estado da tarefa:\n0 = em execucao\n1 = finalizada\n->");
                    scanf("%d",&x);
                    pautaTeste.task[(n/4)-1].marcador_dono = x;
                    break;
                case 3:
                    printf("para qual funcaoo se encaixa essa tarefa?\n");
                    printf("1 = design\n");
                    printf("2 = CC\n");
                    fflush(stdin);
                    scanf("%d",&pautaTeste.task[(n/4)-1].tipo);
                    break;
            }
            break;
    }
    return pautaTeste;
    
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
    printf("\nEscolha o numero da pauta a ser editada(digite \"0\" para cancelar)\n");
    do{
        printf("os numeros das pautas estao no topo de sua descricao\n->");
        scanf("%d",&n);
        if(n==0) return;
    }while((n<0) || (n>nPautas));
    pautaLocal[n-1] = editPauta(pautaLocal[n-1]);
    fopen("pautas","wb");
    fclose(f);
    for(n=0;n<nPautas;n++){
        writePauta(pautaLocal[n]);
    }
    return;
}

int menuPrincipal(){
    int escolha;
    printf("\nO que voce deseja fazer?\n");
    printf("1. Criar Pauta\n");
    printf("2. Mostrar Pautas\n");
    printf("3. Editar uma pauta\n");
    printf("4. Deletar uma pauta\n");
    printf("5. Me de uma tarefa\n");//me de uma tarefa
    printf("6. \n");
    printf("0. Sair\n");
    printf("->");
    scanf("%d",&escolha);
    return escolha;
}

void deletePauta(){
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
        printf("\n\nPauta numero %d\nDono:%s\nTitulo:%s\nDescricao:%s", temp+1,pautaLocal[temp].dono.nome,pautaLocal[temp].titulo, pautaLocal[temp].descricao);
        printf("\nDeadline: %d/%d/%d\n", pautaLocal[temp].dia,pautaLocal[temp].mes,pautaLocal[temp].ano);
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
    printf("\nEscolha o numero da pauta a ser deletada(digite \"0\" para cancelar)\n");
    do{
        printf("os numeros das pautas estao no topo de sua descricao\n->");
        scanf("%d",&n);
        if(n==0) return;
    }while((n<0) || (n>nPautas));
    fopen("pautas","wb");
    fclose(f);
    for(temp=0;temp<nPautas;temp++){
        if(temp!=(n-1)){
            writePauta(pautaLocal[temp]);
        }
    }
    return;
}

usuario defUser(){
    int temp;
    int mark=1;
    usuario atual;
    usuario usuarioTeste;
    printf("Bom dia, qual o seu nome?\n->");
    fflush (stdin);
    fgets(atual.nome,50,stdin);
    FILE *u;
    u=fopen("usuarios","rb");
    int nUsuarios=0;
    if (u==NULL){
        fclose(u);
        printf("qual o seu cargo? (escolha um numero)\n");
        printf("1 = design\n");
        printf("2 = CC\n");
        printf("3 = Admin\n->");
        fflush(stdin);
        scanf("%d",&atual.cargo);
        u=fopen("usuarios","wb+");
        fwrite(&atual,sizeof(usuario),1,u);
        return atual;
    }else{
        while (1){
            fread(&usuarioTeste,sizeof(usuario),1,u);
            if (feof(u)!=0)
                break;
            nUsuarios++;
        }
        usuario usuariosLista[nUsuarios];
        for (temp=0;temp<nUsuarios;temp++){
            fread(&usuariosLista[temp],sizeof(usuario),1,u);
            if (feof(u)!=0)
                break;
            if (usuariosLista[temp].nome == atual.nome){
                mark=1;
                atual.cargo = usuariosLista[temp].cargo;
                break;
            }
        }
    }
    if (mark==0){
        printf("qual o seu cargo? (escolha um numero)\n");
        printf("1 = design\n");
        printf("2 = CC\n");
        printf("3 = Admin\n->");
        fflush(stdin);
        scanf("%d",&atual.cargo);
        fwrite(&atual,sizeof(usuario),1,u);
    }
    fclose(u);
    return atual;
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
        case 4:
            deletePauta();
            break;
        case 5:
            //giveTask();
            break;
        default:
            break;
    }
    return;
}

int main(){
    int comando;
    usuario atual;
    atual = defUser();
    printf("nome = %s \ncargo = %d\n",atual.nome,atual.cargo);
    do{
        comando = menuPrincipal();
        exeComando(comando,atual);
    }while (comando!=0);
    return 0;
}
