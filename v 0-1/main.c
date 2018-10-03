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

typedef struct Usario{//deverá haver maior especificação no futuro
    char nome[51];
}usuario;

typedef struct{//Luiz está finalizando esse struct
    int tipo;
}tarefa;

typedef struct{
    char titulo[51];
    char dono[51];
    tarefa *task;
    int deadline;//procurar biblioteca de tempo e funcionamento da mesma
    comentario *coment;
}pauta;



int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
