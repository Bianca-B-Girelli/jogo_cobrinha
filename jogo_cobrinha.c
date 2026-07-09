#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

// ---------------------------------------------------------------------------------
// 1. DEFINIÇÃO DAS ESTRUTURAS
// ---------------------------------------------------------------------------------

typedef enum EstadoJogo {
    MENU,       // Estado que exibe o menu principal e opções do usuário
    JOGANDO    // Estado ativo de simulação de voo com a nave espacial
} EstadoJogo;

typedef struct Cobra{ // Definição da cobra
    Vector2 posicao; // Posição da cobra em duas dimençãos (x, y)
    float velocidade; 
    Color cor;
}Cobra;
 

// ---------------------------------------------------------------------------------


int main(void){

    const int largura_tela = 1200; // 40 quadradinhos
    const int altura_tela = 800; //10 quadradinhos
    const float raio_cobrinha = 40.0f;


    InitWindow(largura_tela, altura_tela, "Jogo Da Cobrinha");
    Texture2D fundo = LoadTexture("fundo.png");

    SetTargetFPS(60);

    // DESATIVAÇÃO DA TECLA ESCAPE NATIVA:
    // O comando abaixo impede que pressionar a tecla ESC feche a janela do jogo.
    // Isso é feito para que possamos usar o ESC como comando para voltar para o menu.
    SetExitKey(KEY_P);

    // Inicialização da máquina de estados e variáveis de fluxo de interface
    EstadoJogo estadoAtual = MENU;
    int opcaoSelecionada = 0;       // Representa a opção do menu: 0 = Jogar, 1 = Fechar
    bool fecharJogo = false; // Flag de controle seguro para encerrar o laço

    Cobra cobrinha[4];
    for (int i=0;i<4;i++){
        cobrinha[i].posicao.x = 600; 
        cobrinha[i].posicao.y = 40 * i;
        cobrinha[i].cor = BLUE;
        cobrinha[i].velocidade = 80.0;
    }
    

// ---------------------------------------------------------------------------------
// 2. LAÇO PRINCIPAL DO JOGO (GAME LOOP) 
// ---------------------------------------------------------------------------------
// O loop continua rodando enquanto a flag de saída for falsa e o usuário não clicar no X da janela [3, 5]


    while (!fecharJogo &&!WindowShouldClose()) {

    // =============================================================================
    // ETAPA DE ATUALIZAÇÃO DA LÓGICA DE JOGO (UPDATE) 
    // =============================================================================
        switch (estadoAtual) {
            case MENU: {
                // Captura de entrada discreta (apenas um evento por clique) para navegar no menu 
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                    opcaoSelecionada = 1; // Seleciona a opção "Fechar"
                }
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                    opcaoSelecionada = 0; // Seleciona a opção "Jogar"
                }

                // Processamento de seleção de opções ao pressionar a tecla ENTER 
                if (IsKeyPressed(KEY_ENTER)) {
                    if (opcaoSelecionada == 0) {
                    //Aqui pode estar faltando a posição inicial da cobrinha
                        estadoAtual = JOGANDO;  // Muda o estado ativo para a jogabilidade
                    }
                    else if (opcaoSelecionada == 1) {
                        fecharJogo = true; // Define a flag para encerrar o jogo com segurança
                    }
                }
                break;
            }

            case JOGANDO: {
                // Monitora a tecla ESCAPE de forma discreta para retornar ao menu com segurança 
                if (IsKeyPressed(KEY_ESCAPE)) {
                    estadoAtual = MENU; // Altera o estado sem fechar o programa de maneira abrupta [7]
                }
                for (int i=0;i<4;i++){
                // Captura contínua de teclas para movimentação linear e suave da nave espacial 
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                    cobrinha[i].posicao.x -= cobrinha[i].velocidade; // Desloca para a esquerda (subtrai no eixo X) 
                }
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                    cobrinha[i].posicao.x += cobrinha[i].velocidade; // Desloca para a direita (soma no eixo X) 
                }
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                    cobrinha[i].posicao.y += cobrinha[i].velocidade; // Desloca para a direita (soma no eixo X) 
                }
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                    cobrinha[i].posicao.y -= cobrinha[i].velocidade; // Desloca para cima (subtrai no eixo Y) 
                }
                }


            // SISTEMA DE COLISÃO BÁSICO (Bordas de Tela):
                // Limita as coordenadas da nave para evitar que o usuário saia do campo visível.
            for (int i=0;i<4;i++){
                if (cobrinha[i].posicao.x < 40.0f){ 
                    cobrinha[i].posicao.x = 40.0f;
                }
                if (cobrinha[i].posicao.x > (float)largura_tela - 40.0f) {
                    cobrinha[i].posicao.x = (float)largura_tela - 40.0f;
                }
                if (cobrinha[i].posicao.y < 40.0f){
                    cobrinha[i].posicao.y = 40.0f;}
                if (cobrinha[i].posicao.y > (float)altura_tela - 40.0f) {
                    cobrinha[i].posicao.y = (float)altura_tela - 40.0f;
                }
            }
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(fundo, 0, 0, WHITE);

        EndDrawing();
    }
    UnloadTexture(fundo);
    CloseWindow();
}
    