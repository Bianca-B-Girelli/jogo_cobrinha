#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>


// Definição dos estados lógicos de navegação do jogo
typedef enum EstadoJogo {
    MENU,       // Estado que exibe o menu principal e opções do usuário
    JOGANDO    // Estado ativo de simulação de voo com a nave espacial
} EstadoJogo;

typedef struct Cobra{
    Vector2 posicao;
    float velocidade;
    int tamanho_largura;
    int tamanho_comprimento;
    Color cor;
}Cobra;

typedef struct Maca{
    Vector2 posicao;
    Texture2D imagem;
    bool ativo;
}Maca;

typedef struct quadradinhos{
    Vector2 posicao;
    Color cor;
    bool ocupado;
    bool maca;
}

int main(void){
    const int largura_tela = 1200; // 15 quadradinhos
    const int altura_tela = 800; //10 quadradinhos


    InitWindow(larguraTela, alturaTela, "Jogo Da Cobrinha");
    SetTargetFPS(60);

    Cobra cobrinha;
    cobrinha.posicao = (Vector2){ (float)largura_tela / 2.0f, (float)altur_tela / 2.0f };
    cobrinha.velocidade = 20.0;
    cobrinha.tamanho_largura = 80;

    
    
    


}