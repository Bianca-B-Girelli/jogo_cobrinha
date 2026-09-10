#ifndef COBRA_H
#define COBRA_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    struct Node *inicio;
    struct Node *fim;
    int len;
} Cabecalho;


Node* criar_cobra(void);

bool inserir_fim(Node *cabecalho, int corpo);

void destruir_cobra(Node *cabecalho);

#endif