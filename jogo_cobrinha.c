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


//Estruturação da cobrinha
typedef struct Cobra {
    Vector2 posicao;
    float velocidade;
    Color cor;
    bool viva;
} Cobra;


int main(void) {
    //Configuraçao da janela
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
    Texture2D fundo = LoadTexture("imagens/fundo.png");
    Texture2D fundo2 = LoadTexture("imagens/fundo2.png");

    //Frames por segundo
    SetTargetFPS(60);

    // Inicialização dos 4 segmentos da cobrinha
    Cobra cobrinha[4];
    cobrinha[0].viva = true;


    // Direção inicial da cobra (X, Y)
    Vector2 direcao = { 0, -1 }; // Começa movendo para cima


    // Cronômetro para o movimento em passos (Grid)
    float tempoPasso = 0.15f; // A cobra se move a cada 0.15 segundos
    float contadorTempo = 0.0f;


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
                            cobrinha[i].posicao.y = 400 + (raio_cobrinha * i);
                            cobrinha[i].cor = BLUE;
                        }
                        direcao = (Vector2){ 0, -1 };
                        contadorTempo = 0.0f;
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
               
                // 1. Captação de Entrada (muda a direção sem permitir inverter 180º)
		        if (cobrinha[0].viva) { 
                    if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && direcao.x == 0) {
                        direcao = (Vector2){ -1, 0 };
                    }
                    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && direcao.x == 0) {
                        direcao = (Vector2){ 1, 0 };
                    }
                    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && direcao.y == 0) {
                        direcao = (Vector2){ 0, -1 };
                    }
                    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && direcao.y == 0) {
                        direcao = (Vector2){ 0, 1 };
                    }


                    // 2. Atualização por Intervalo de Tempo (Passo a Passo)
                    contadorTempo += GetFrameTime();
                    if (contadorTempo >= tempoPasso) {
                        contadorTempo = 0.0f; // Reseta o relógio


                        // Move o corpo: cada segmento pega a posição exata do segmento à sua frente
                        for (int i = 3; i > 0; i--) {
                            cobrinha[i].posicao = cobrinha[i - 1].posicao;
                        }


                        // Move a cabeça de acordo com a direção atual
                        cobrinha[0].posicao.x += direcao.x * raio_cobrinha;
                        cobrinha[0].posicao.y += direcao.y * raio_cobrinha;
                    }


                    // SISTEMA DE COLISÃO REFORMADO USANDO BOOL PARA VERIFICAR SE ELA ESTA VIVA (Bordas de Tela aplicadas à cabeça)
                    if (cobrinha[0].posicao.x < 0 ||
                        cobrinha[0].posicao.x > (float)largura_tela - raio_cobrinha ||
                        cobrinha[0].posicao.y < 0 || 
                        cobrinha[0].posicao.y > (float)altura_tela - raio_cobrinha) 
                        {cobrinha[0].viva = false;}
                }else{ estadoAtual = MENU; 
                       cobrinha[0].viva = true;
                    } 
                                            
                break;
            }
        }


        // =============================================================================
        // ETAPA DE PROCESSAMENTO GRÁFICO (DRAW)
        // =============================================================================
        BeginDrawing();
        ClearBackground(BLACK); // Caso a imagem de fundo falhe, a tela fica preta


        switch (estadoAtual) {
            case MENU: {
                //carrega o fundo do menu
                if (fundo.id > 0) {
                    DrawTexture(fundo2, 0, 0, WHITE);
                }
                // Desenho do titulo no Menu Principal
                const char* title = "JOGO DA COBRINHA";
                int titleWidth = MeasureText(title, 80);
                DrawText(title, largura_tela / 2 - titleWidth / 2, 200, 80, BLACK);

                // Desenha as opçãoes no menu
                if (opcaoSelecionada == 0) {
                    DrawText("> JOGAR <", largura_tela / 2.3 - MeasureText("> JOGAR <", 24) / 2, 320, 44, RAYWHITE);
                    DrawText("FECHAR", largura_tela / 2.3 - MeasureText("FECHAR", 20) / 2, 380, 44, BLACK);
                } else {
                    DrawText("JOGAR", largura_tela / 2.25 - MeasureText("JOGAR", 20) / 2, 320, 44, BLACK);
                    DrawText("> FECHAR <", largura_tela / 2.35 - MeasureText("> FECHAR <", 24) / 2, 380, 44, RAYWHITE);
                }

                //Desenha o footer com as instruções
                const char* footer = "Navegue com W/S ou Setas e selecione com Enter";
                int footerWidth = MeasureText(footer, 14);
                DrawText(footer, largura_tela / 2.6 - footerWidth / 2, 600, 24, BLACK);
                break;
            }


            case JOGANDO: {

                // Carrega a imagem do jogo
                if (fundo.id > 0) {
                    DrawTexture(fundo, 0, 0, WHITE);
                }
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
    UnloadTexture(fundo2);
    CloseWindow();
   
    return 0;
}


