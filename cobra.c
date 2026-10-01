#include "cobra.h"

Cabecalho* criar_cobra(void) {
    Cabecalho *cobra = (Cabecalho*) malloc(sizeof(Cabecalho));
    if (cobra == NULL) {
        printf("Erro ao alocar memória para o cabeçalho.\n");
        return NULL;
    }
    cobra->inicio = NULL;
    cobra->fim = NULL;
    cobra->len = 0;
    return cobra;
}

bool inserir_fim(Cabecalho *cobra, Vector2 posicao, Color cor) {
    if (cobra == NULL) return false;

    Node *novo_no = (Node*) malloc(sizeof(Node));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para novo segmento.\n");
        return false;
    }

    novo_no->posicao = posicao;
    novo_no->cor = cor;
    novo_no->next = NULL;

    if (cobra->inicio == NULL) {
        cobra->inicio = novo_no;
        cobra->fim = novo_no;
    } else {
        cobra->fim->next = novo_no;
        cobra->fim = novo_no;
    }

    cobra->len++;
    return true;
}

void destruir_cobra(Cabecalho *cobra) {
    if (cobra == NULL) return;

    Node *atual = cobra->inicio;
    while (atual != NULL) {
        Node *proximo = atual->next;
        free(atual);
        atual = proximo;
    }

    cobra->inicio = NULL;
    cobra->fim = NULL;
    cobra->len = 0;
    free(cobra); // Libera a estrutura do cabeçalho
}