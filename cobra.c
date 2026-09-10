#include "cobra.h"

Node* criar_cobra(void){
    Node *cabecalho = (Node*) malloc(sizeof(Node));
    if (cabecalho == NULL) {
        printf("Erro crítico: Falha na alocação de memória para o nó cabeçalho.\n");
        return NULL;
    }
    cabecalho->data = 0;
    cabecalho->next = NULL;
    return cabecalho;
}

bool inserir_fim(Node *cabecalho, int corpo) {
    if (cabecalho == NULL) return false;

    Node *novo_no = (Node*) malloc(sizeof(Node));
    if (novo_no == NULL) {
        printf("Erro: Falha na alocação de memória para novo nó.\n");
        return false;
    }

    novo_no->data = corpo;
    novo_no->next = NULL;


    Node *atual = cabecalho;
    while (atual->next != NULL) {
        atual = atual->next;
    }

    atual->next = novo_no;
    return true;
}

void destruir_cobra(Node *cabecalho) {
    if (cabecalho == NULL) return;

    Node *atual = cabecalho;
    while (atual != NULL) {
        Node *proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}
