//
//  main.c
//  Informativo v0.0.1.
//
//  Created by Bernardo Russo on 21/09/18.
//  Copyright © 2018 Bernardo Russo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

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

//enum tipos_tarefa {texto, foto, grafico};

typedef struct{
    char titulo[51];
    char descricao[261];
    usuario dono;//o dono também pode estar numa estrutura de listas
    tarefa *task;
    int deadline;//procurar biblioteca de tempo e funcionamento da mesma
    comentario *coment;//lista de comentarios sobre a pauta
}pauta;

int escolha(){
    int escolha;
    printf("O que deseja fazer?\n");
    printf("1. Escrever Pauta;\n");
    printf("2. Procurar Pauta;\n");
    printf("3. ");
    printf("0. Sair;\n");
    printf("-> ");
    scanf("%i",&escolha);
    return escolha;
}

void acao(int opt){
    switch (opt){
        case 0: ;
            
    }
}

int main() {//definir maneiras de colocar valores nas pautas/tarefas
    int opt=escolha();
    return 0;
}
