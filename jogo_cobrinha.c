#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

// ---------------------------------------------------------------------------------
// 1. DEFINIÇÃO DAS ESTRUTURAS
// ---------------------------------------------------------------------------------

typedef enum EstadoJogo {
    MENU,       // Estado que exibe o menu principal e opções do usuário
    JOGANDO     // Estado ativo de simulação com a cobrinha
} EstadoJogo;

typedef struct Cobra {
    Vector2 posicao;
    float velocidade;
    Color cor;
} Cobra;


int main(void) {

    const int largura_tela = 1200;
    const int altura_tela = 800;
    const float raio_cobrinha = 40.0f; // Tamanho do quadrado da cobrinha

    // Variáveis de controle de estado
    EstadoJogo estadoAtual = MENU;
    bool fecharJogo = false;
    int opcaoSelecionada = 0; // 0 = Jogar, 1 = Fechar

    InitWindow(largura_tela, altura_tela, "Jogo Da Cobrinha");
   
    // O comando abaixo impede que pressionar a tecla ESC feche a janela do jogo diretamente
    SetExitKey(KEY_P);

    // Carrega a textura de fundo
    // Certifique-se de ter a imagem "fundo.png" na mesma pasta do executável
    Texture2D fundo = LoadTexture("fundo.png");

    SetTargetFPS(60);

    // Inicialização dos 4 segmentos da cobrinha
    Cobra cobrinha[4];
    for (int i = 0; i < 4; i++) {
        cobrinha[i].posicao.x = 600;
        cobrinha[i].posicao.y = 400 + (40 * i); // Alinhados verticalmente no início
        cobrinha[i].cor = BLUE;
        cobrinha[i].velocidade = 5.0f; // Velocidade de movimento por frame
    }

    // ---------------------------------------------------------------------------------
    // 2. LAÇO PRINCIPAL DO JOGO (GAME LOOP)
    // ---------------------------------------------------------------------------------
    while (!fecharJogo && !WindowShouldClose()) {

        // =============================================================================
        // ETAPA DE ATUALIZAÇÃO DA LÓGICA DE JOGO (UPDATE)
        // =============================================================================
        switch (estadoAtual) {
            case MENU: {
                // Navegação no menu
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                    opcaoSelecionada = 1; // Seleciona "Fechar"
                }
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                    opcaoSelecionada = 0; // Seleciona "Jogar"
                }

                // Processamento de seleção
                if (IsKeyPressed(KEY_ENTER)) {
                    if (opcaoSelecionada == 0) {
                        // Reseta a posição inicial dos segmentos ao iniciar o jogo
                        for (int i = 0; i < 4; i++) {
                            cobrinha[i].posicao.x = 600;
                            cobrinha[i].posicao.y = 400 + (40 * i);
                        }
                        estadoAtual = JOGANDO;  
                    } else if (opcaoSelecionada == 1) {
                        fecharJogo = true;
                    }
                }
                break;
            }

            case JOGANDO: {
                // Voltar para o menu principal com ESC
                if (IsKeyPressed(KEY_ESCAPE)) {
                    estadoAtual = MENU;
                }
               
                // Movimentação (Controla a cabeça - índice 0)
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                    cobrinha[0].posicao.x -= cobrinha[0].velocidade;
                }
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                    cobrinha[0].posicao.x += cobrinha[0].velocidade;
                }
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                    cobrinha[0].posicao.y += cobrinha[0].velocidade;
                }
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                    cobrinha[0].posicao.y -= cobrinha[0].velocidade;
                }

                // Seguidor simples para o corpo (segmentos 1, 2 e 3 seguem o anterior)
                // Nota: para uma movimentação de cobra real em grid, o sistema precisaria de um histórico de posições.
                // Mas por enquanto, este laço mantém o corpo junto ao movimento básico:
                for (int i = 3; i > 0; i--) {
                    // Interpolação simples para os segmentos seguirem o da frente de forma suave
                    cobrinha[i].posicao.x += (cobrinha[i-1].posicao.x - cobrinha[i].posicao.x) * 0.15f;
                    cobrinha[i].posicao.y += ((cobrinha[i-1].posicao.y + 40.0f) - cobrinha[i].posicao.y) * 0.15f;
                }

                // SISTEMA DE COLISÃO BÁSICO (Bordas de Tela aplicadas à cabeça)
                if (cobrinha[0].posicao.x < 0) {
                    cobrinha[0].posicao.x = 0;
                }
                if (cobrinha[0].posicao.x > (float)largura_tela - raio_cobrinha) {
                    cobrinha[0].posicao.x = (float)largura_tela - raio_cobrinha;
                }
                if (cobrinha[0].posicao.y < 0) {
                    cobrinha[0].posicao.y = 0;
                }
                if (cobrinha[0].posicao.y > (float)altura_tela - raio_cobrinha) {
                    cobrinha[0].posicao.y = (float)altura_tela - raio_cobrinha;
                }
                break;
            }
        }

        // =============================================================================
        // ETAPA DE PROCESSAMENTO GRÁFICO (DRAW)
        // =============================================================================
        BeginDrawing();
        ClearBackground(BLACK); // Caso a imagem de fundo falhe, a tela fica preta

        // Desenha a imagem de fundo se ela foi carregada com sucesso
        if (fundo.id > 0) {
            DrawTexture(fundo, 0, 0, WHITE);
        }

        switch (estadoAtual) {
            case MENU: {
                // Desenho do Menu Principal
                const char* title = "JOGO DA COBRINHA";
                int titleWidth = MeasureText(title, 44);
                DrawText(title, largura_tela / 2 - titleWidth / 2, 150, 44, GREEN);

                if (opcaoSelecionada == 0) {
                    DrawText("> JOGAR <", largura_tela / 2 - MeasureText("> JOGAR <", 24) / 2, 320, 24, RAYWHITE);
                    DrawText("FECHAR", largura_tela / 2 - MeasureText("FECHAR", 20) / 2, 380, 20, GRAY);
                } else {
                    DrawText("JOGAR", largura_tela / 2 - MeasureText("JOGAR", 20) / 2, 320, 20, GRAY);
                    DrawText("> FECHAR <", largura_tela / 2 - MeasureText("> FECHAR <", 24) / 2, 380, 24, RAYWHITE);
                }

                const char* footer = "Navegue com W/S ou Setas e selecione com Enter";
                int footerWidth = MeasureText(footer, 14);
                DrawText(footer, largura_tela / 2 - footerWidth / 2, 520, 14, DARKGRAY);
                break;
            }

            case JOGANDO: {
                // Desenha todos os segmentos da cobrinha (corpo e cabeça)
                // O loop desenha de trás para frente para a cabeça (índice 0) ficar por cima
                for (int i = 3; i >= 0; i--) {
                    // Diferencia a cor da cabeça para ficar visualmente melhor
                    Color corSegmento = (i == 0) ? SKYBLUE : cobrinha[i].cor;
                   
                    DrawRectangleV(
                        cobrinha[i].posicao,
                        (Vector2){ raio_cobrinha, raio_cobrinha },
                        corSegmento
                    );
                }
               
                // Texto de dica de retorno enquanto joga
                DrawText("Pressione ESC para voltar ao Menu", 20, 20, 20, LIGHTGRAY);
                break;
            }
        }

        EndDrawing();
    }
   
    // Descarrega a textura e fecha a janela de forma segura
    UnloadTexture(fundo);
    CloseWindow();
   
    return 0;
}
