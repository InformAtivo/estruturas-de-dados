//
//  main.c
//  Informativo v0.0.1.
//
//  Created by Bernardo Russo on 21/09/18.
//  Copyright © 2018 Bernardo Russo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Comentario{
    char texto [260];
    struct Comentario *proximo;
}comentario;

typedef struct{//deverá haver maior especificação no futuro
    char nome[51];
}usuario;

typedef struct task{//Luiz está finalizando esse struct
    int tipo;
    struct task *anterior;
    struct task *proxima;
    char desc[260];
}tarefa;

enum tipos_tarefa {texto, foto, grafico};

typedef struct{
    char titulo[51];
    char dono[51];//o dono também pode estar numa estrutura de listas
    tarefa *task;
    int deadline;//procurar biblioteca de tempo e funcionamento da mesma
    comentario *coment;//lista de comentarios sobre a pauta
}pauta;

int main() {//definir maneiras de colocar valores nas pautas/tarefas
    
    return 0;
}
