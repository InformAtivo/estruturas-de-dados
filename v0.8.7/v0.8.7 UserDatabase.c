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
    int marcador_dono;//marcardo de certificacnao de conclusao
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

void swap(pauta* a, pauta* b){
	pauta t = *a;
	*a = *b;
	*b = t;
}

int partition (pauta arr[], int low, int high){
    int j;
    int i = (low - 1);
    for (j = low; j <= high- 1; j++){
        if (arr[j].deadline <= arr[high].deadline){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(pauta arr[], int low, int high){
	if (low < high){
		int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

long Urgencia(int dia, int mes, int ano){
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

usuario defUser(){
    int temp;
    int mark=0;
    usuario atual;
    usuario usuarioTeste;
    printf("Defina o nome do usuario\n->");
    fflush (stdin);
    fgets(atual.nome,50,stdin);
    atual.nome[strlen(atual.nome)-1]='\0';
    FILE *u;
    u=fopen("usuarios","rb");
    int nUsuarios=0;
    if (u==NULL){
        fclose(u);
        printf("Defina o cargo do usuario (escolha um numero)\n");
        printf("1 = design\n");
        printf("2 = CC\n");
        printf("3 = Admin\n->");
        fflush(stdin);
        scanf("%d",&atual.cargo);
        u=fopen("usuarios","wb+");
        fwrite(&atual,sizeof(atual),1,u);
        fclose(u);
        return atual;
    }else{
        while (1){
            fread(&usuarioTeste,sizeof(usuarioTeste),1,u);
            if (feof(u)!=0){
                printf("usuario nao encontrado\n");
                break;
            }
            if (strcmp(usuarioTeste.nome, atual.nome)==0){
                printf("usuario encontrado\n");
                mark = 1;
                atual.cargo = usuarioTeste.cargo;
                fclose(u);
                break;
            }
        }
    }
    if (mark==0){
        fclose(u);
        u=fopen("usuarios","ab");
        printf("Defina o cargo do usuario (escolha um numero)\n");
        printf("1 = design\n");
        printf("2 = CC\n");
        printf("3 = Admin\n->");
        fflush(stdin);
        scanf("%d",&atual.cargo);
        fwrite(&atual,sizeof(atual),1,u);
        fclose(u);
    }
    return atual;
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
    int n,x,count = 6;
    char escolha;
    printf("\no que voce deseja alterar? escolha o numero referente ao local\n(escreva\"0\" para cancelar)\n");
    printf("\n1- Dono:%s\n2- Titulo:%s\n3- Descricao:%s",pautaTeste.dono.nome,pautaTeste.titulo,pautaTeste.descricao);
    printf("\n4- Deadline: %d/%d/%d\n\n",pautaTeste.dia,pautaTeste.mes,pautaTeste.ano);
    if (pautaTeste.task[0].tipo!=0){
        printf("Tarefas:\n");
        printf("5- Adicionar uma tarefa\n");
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
    case 5:
        pautaTeste = defTarefa(pautaTeste);
        break;
    default:
        n= n-2;
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

void giveTask(usuario usuarioLocal){
    FILE *f;
    f = fopen("pautas","rb");
    int n,nRelevante = 0,nSecundaria = 0;
    int temp,x;
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
    pauta pautaLocal[nPautas], pautaRelevante[nPautas], pautaSecundaria[nPautas];
    for(temp=0;temp<nPautas;temp++){
        fread(&pautaLocal[temp],sizeof(pautaTeste),1,f);
        for(x=0;x<20;x++){
            if((pautaLocal[temp].task[x].tipo) == (usuarioLocal.cargo)&&(pautaLocal[temp].task[x].marcador_dono==0)&&(strcmp(pautaLocal[temp].task[x].responsavel.nome, "Ninguem")==0)){
                pautaRelevante[nRelevante] = pautaLocal[temp];
                pautaRelevante[nRelevante].deadline = Urgencia(pautaRelevante[nRelevante].dia,pautaRelevante[nRelevante].mes,pautaRelevante[nRelevante].ano);
                nRelevante++;
                break;
            }else{
                if(x==19){
                    pautaSecundaria[nSecundaria] = pautaLocal[temp];
                    pautaSecundaria[nSecundaria].deadline = Urgencia(pautaSecundaria[nSecundaria].dia,pautaSecundaria[nSecundaria].mes,pautaSecundaria[nSecundaria].ano);
                    nSecundaria++;
                    break;
                }
            }
        }
        if(feof(f)!=0){
            break;
        }
    }
    quickSort(pautaRelevante, 0, nRelevante-1);
    quickSort(pautaSecundaria, 0, nSecundaria-1);
    printf("\n#######################################################\nPautas adequadas para producao");
    for(temp=0;temp<nRelevante;temp++){
        printf("\n\nDono:%s\nTitulo:%s\nDescricao:%s",pautaRelevante[temp].dono.nome,pautaRelevante[temp].titulo,pautaRelevante[temp].descricao);
        printf("\nDeadline: %d/%d/%d\n\n",pautaRelevante[temp].dia,pautaRelevante[temp].mes,pautaRelevante[temp].ano);
        if (pautaRelevante[temp].task[0].tipo!=0){
            printf("Tarefas:\n");
            n=0;
            while(pautaRelevante[temp].task[n].tipo!=0){
                printf("Tarefa numero %d: %s\n",n+1,pautaRelevante[temp].task[n].desc);
                printf("Responsavel atual: %s\n",pautaRelevante[temp].task[n].responsavel.nome);
                printf("Estado da tarefa: ");
                if (pautaRelevante[temp].task[n].marcador_dono == 0){
                    printf("em andamento\n");
                }else{
                    printf("concluida\n");
                }
                printf("tipo da tarefa: %d\n",pautaRelevante[temp].task[n].tipo);
                n++;
            }
        }
        printf("--------------------\n");
    }
    printf("\n#######################################################\nPautas que podem precisar de ajuda\n");
    for(temp=0;temp<nSecundaria;temp++){
        printf("\n\nDono:%s\nTitulo:%s\nDescricao:%s",pautaSecundaria[temp].dono.nome,pautaSecundaria[temp].titulo,pautaSecundaria[temp].descricao);
        printf("\nDeadline: %d/%d/%d\n\n",pautaSecundaria[temp].dia,pautaSecundaria[temp].mes,pautaSecundaria[temp].ano);
        if (pautaSecundaria[temp].task[0].tipo!=0){
            printf("Tarefas:\n");
            n=0;
            while(pautaSecundaria[temp].task[n].tipo!=0){
                printf("Tarefa numero %d: %s\n",n+1,pautaSecundaria[temp].task[n].desc);
                printf("Responsavel atual: %s\n",pautaSecundaria[temp].task[n].responsavel.nome);
                printf("Estado da tarefa: ");
                if (pautaSecundaria[temp].task[n].marcador_dono == 0){
                    printf("em andamento\n");
                }else{
                    printf("concluida\n");
                }
                printf("tipo da tarefa: %d\n",pautaSecundaria[temp].task[n].tipo);
                n++;
            }
        }
        printf("--------------------\n");
    }
    return;
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
        printf("--------------------\n");
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
        giveTask(userAtual);
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
