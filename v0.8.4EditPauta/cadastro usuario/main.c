//
//  main.c
//  checkUsuario
//
//  Created by Bernardo Russo on 13/11/18.
//  Copyright © 2018 Bernardo Russo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    char nome[51];
    int cargo;
}usuario;

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

usuario abrirUsuario(){
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
    
    
}
int main() {
    usuario atual = abrirUsuario();
    
    return 0;
}
