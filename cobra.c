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

void gerar_maca(Maca *maca, Cabecalho *cobra, int largura_tela, int altura_tela, float raio) {
    bool posicao_valida = false; // Variável de controle para saber se a posição sorteada é segura (não está em cima da cobra)

    // Laço que continua rodando até encontrar uma posição totalmente livre na tela
    while (!posicao_valida) {

        // Calcula quantas colunas e linhas cabem na tela com base no tamanho do bloco (raio)
        int max_x = (largura_tela / (int)raio);
        int max_y = (altura_tela / (int)raio);
        
        // Sorteia uma posição X e Y aleatória alinhada estritamente ao grid do jogo
        int random_x = GetRandomValue(0, max_x - 1) * (int)raio; 
        int random_y = GetRandomValue(0, max_y - 1) * (int)raio;

        // Atribui as coordenadas sorteadas para a estrutura da maçã e ativa ela
        maca->posicao = (Vector2){ (float)random_x, (float)random_y };
        maca->ativa = true; 

        /// Sorteio dos tipos de maçã (Total de 20 chances)
        int chance = GetRandomValue(1, 20);
        if (chance == 1) {
            maca->tipo = 2; // Dourada 
        } else if (chance == 2) {
            maca->tipo = 3; // Estragada 
        } else {
            maca->tipo = 1; // Normal 
        }

        // Percorre todo o corpo da cobra checando se há colisão com o local da maçã
        posicao_valida = true;
        Node *atual = cobra->inicio;
        while (atual != NULL) {
            if (atual->posicao.x == maca->posicao.x && atual->posicao.y == maca->posicao.y) {
                // Se a maçã nasceu em cima de algum pedaço da cobra, invalidamos a posição
                posicao_valida = false; // Bateu na cobra, tenta sortear de novo
                break;
            }
            atual = atual->next;
        }
    }
}

void remover_fim(Cabecalho *cobra) {
    if (cobra == NULL || cobra->len <= 1) return; // não remove se for nulo ou menor/igual a 1

    if (cobra->inicio == cobra->fim) {
        // Se por acaso tiver só a cabeça
        free(cobra->inicio);
        cobra->inicio = NULL;
        cobra->fim = NULL;
        cobra->len = 0;
        return;
    }

    // Percorre até encontrar o penúltimo nó
    Node *atual = cobra->inicio;
    while (atual->next != cobra->fim) {
        atual = atual->next;
    }

    // Libera o último nó atual
    free(cobra->fim);
    
    // O penúltimo passa a ser o novo fim
    cobra->fim = atual;
    cobra->fim->next = NULL;
    cobra->len--;
}