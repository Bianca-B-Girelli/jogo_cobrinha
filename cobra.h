#ifndef COBRA_H
#define COBRA_H

#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 1. O Nó armazena a posição na tela e a cor do segmento
typedef struct Node {
    Vector2 posicao;
    Color cor;
    struct Node *next;
} Node;

// 2. A estrutura Cabecalho gerencia o ponteiro para o início, fim e o tamanho
typedef struct {
    Node *inicio;
    Node *fim;
    int len;
} Cabecalho;

// Inicializa a estrutura do cabeçalho
Cabecalho* criar_cobra(void);

// Insere um novo segmento no final da cobra
bool inserir_fim(Cabecalho *cobra, Vector2 posicao, Color cor);

// Libera toda a memória alocada para os nós e para o cabeçalho
void destruir_cobra(Cabecalho *cobra);

#endif // COBRA_H