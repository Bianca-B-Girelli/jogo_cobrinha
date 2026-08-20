#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>


// ---------------------------------------------------------------------------------
// 1. DEFINIÇÃO DAS ESTRUTURAS
// ---------------------------------------------------------------------------------

typedef enum EstadoJogo {
    MENU,       // Estado que exibe o menu principal e opções do usuário
    JOGANDO,    // Estado ativo de simulação com a cobrinha
    FIM         // Estado de Game Over
} EstadoJogo;


// Estruturação da cobrinha
typedef struct Cobra {
    Vector2 posicao;
    float velocidade;
    Color cor;
    bool viva;
} Cobra;

void mover_cobrinha(Cobra *cobrinha, float *contadorTempo, float tempoPasso, float raio_cobrinha, Vector2 direcao){
    *contadorTempo += GetFrameTime();

    if (*contadorTempo >= tempoPasso) {

        *contadorTempo -= tempoPasso;


        // Move o corpo
        for (int i = 3; i > 0; i--) {
            cobrinha[i].posicao =
                cobrinha[i - 1].posicao;
        }


        // Move a cabeça
        cobrinha[0].posicao.x +=
            direcao.x * raio_cobrinha;

        cobrinha[0].posicao.y +=
            direcao.y * raio_cobrinha;
    }
}

void encerrar_jogo(Cobra *cobrinha, int largura_tela, int altura_tela, float raio_cobrinha, EstadoJogo *estadoAtual){
    if (cobrinha[0].posicao.x < 0 ||
        cobrinha[0].posicao.x >
        (float)largura_tela - raio_cobrinha ||

        cobrinha[0].posicao.y < 0 ||
        cobrinha[0].posicao.y >
        (float)altura_tela - raio_cobrinha) {

        // Cobra morreu
        cobrinha[0].viva = false;

        // Vai para a tela de Game Over
        *estadoAtual = FIM;
    }
}

int main(void) {

    // Configuração da janela
    const int largura_tela = 1200;
    const int altura_tela = 800;
    const float raio_cobrinha = 40.0f;


    // Variáveis de controle de estado
    EstadoJogo estadoAtual = MENU;
    bool fecharJogo = false;
    int opcaoSelecionada = 0; // 0 = Jogar, 1 = Fechar


    InitWindow(largura_tela, altura_tela, "Jogo Da Cobrinha");

    // Impede que uma tecla feche a janela automaticamente
    SetExitKey(KEY_P);


    // ---------------------------------------------------------------------------------
    // CARREGAMENTO DAS TEXTURAS
    // ---------------------------------------------------------------------------------

    Texture2D fundo = LoadTexture("imagens/fundo.png");
    Texture2D fundo2 = LoadTexture("imagens/fundo2.png");
    Texture2D fundoGameOver = LoadTexture("imagens/gameover.png");


    // FPS
    SetTargetFPS(60);


    // ---------------------------------------------------------------------------------
    // INICIALIZAÇÃO DA COBRA
    // ---------------------------------------------------------------------------------

    Cobra cobrinha[4];

    cobrinha[0].viva = true;


    // Direção inicial da cobra
    Vector2 direcao = { 0, -1 };


    // Cronômetro para o movimento em passos
    float tempoPasso = 0.15f;
    float contadorTempo = 0.0f;


    // ---------------------------------------------------------------------------------
    // 2. LAÇO PRINCIPAL DO JOGO
    // ---------------------------------------------------------------------------------

    while (!fecharJogo && !WindowShouldClose()) {


        // =============================================================================
        // ETAPA DE ATUALIZAÇÃO DA LÓGICA
        // =============================================================================

        switch (estadoAtual) {

            // -------------------------------------------------------------------------
            // MENU
            // -------------------------------------------------------------------------

            case MENU: {

                // Navegação no menu
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                    opcaoSelecionada = 1;
                }

                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                    opcaoSelecionada = 0;
                }


                // Processamento de seleção
                if (IsKeyPressed(KEY_ENTER)) {

                    // Jogar
                    if (opcaoSelecionada == 0) {

                        // Reseta a cobra
                        for (int i = 0; i < 4; i++) {

                            cobrinha[i].posicao.x = 600;
                            cobrinha[i].posicao.y =
                                400 + (raio_cobrinha * i);

                            cobrinha[i].cor = BLUE;
                            cobrinha[i].viva = true;
                        }


                        // Reseta a direção
                        direcao = (Vector2){ 0, -1 };

                        // Reseta o contador
                        contadorTempo = 0.0f;

                        // Começa o jogo
                        estadoAtual = JOGANDO;
                    }


                    // Fechar
                    else if (opcaoSelecionada == 1) {
                        fecharJogo = true;
                    }
                }

                break;
            }


            // -------------------------------------------------------------------------
            // JOGANDO
            // -------------------------------------------------------------------------

            case JOGANDO: {

                // Voltar para o menu principal com ESC
                if (IsKeyPressed(KEY_ESCAPE)) {
                    estadoAtual = MENU;
                }


                // Só movimenta se a cobra estiver viva
                if (cobrinha[0].viva) {

                    // -------------------------------------------------------------
                    // CAPTAÇÃO DE ENTRADA
                    // -------------------------------------------------------------

                    // Esquerda
                    if ((IsKeyPressed(KEY_LEFT) ||
                         IsKeyPressed(KEY_A)) &&
                        direcao.x == 0) {

                        direcao = (Vector2){ -1, 0 };
                    }


                    // Direita
                    if ((IsKeyPressed(KEY_RIGHT) ||
                         IsKeyPressed(KEY_D)) &&
                        direcao.x == 0) {

                        direcao = (Vector2){ 1, 0 };
                    }


                    // Cima
                    if ((IsKeyPressed(KEY_UP) ||
                         IsKeyPressed(KEY_W)) &&
                        direcao.y == 0) {

                        direcao = (Vector2){ 0, -1 };
                    }


                    // Baixo
                    if ((IsKeyPressed(KEY_DOWN) ||
                         IsKeyPressed(KEY_S)) &&
                        direcao.y == 0) {

                        direcao = (Vector2){ 0, 1 };
                    }


                    // -------------------------------------------------------------
                    // MOVIMENTO DA COBRA
                    // -------------------------------------------------------------

                    mover_cobrinha(cobrinha, &contadorTempo, tempoPasso, raio_cobrinha, direcao);

                    // -------------------------------------------------------------
                    // COLISÃO COM AS BORDAS
                    // -------------------------------------------------------------
                    encerrar_jogo(cobrinha, largura_tela, altura_tela, raio_cobrinha, &estadoAtual);

                }

                break;
            }


            // -------------------------------------------------------------------------
            // GAME OVER
            // -------------------------------------------------------------------------

            case FIM: {

                // Pressiona ENTER para voltar ao menu
                if (IsKeyPressed(KEY_ENTER)) {

                    cobrinha[0].viva = true;

                    estadoAtual = MENU;
                }

                break;
            }
        }


        // =============================================================================
        // ETAPA DE PROCESSAMENTO GRÁFICO
        // =============================================================================

        BeginDrawing();

        ClearBackground(BLACK);


        switch (estadoAtual) {

            // -------------------------------------------------------------------------
            // TELA DO MENU
            // -------------------------------------------------------------------------

            case MENU: {

                // Carrega o fundo do menu
                if (fundo2.id > 0) {
                    DrawTexture(fundo2, 0, 0, WHITE);
                }


                // Título
                const char* title = "JOGO DA COBRINHA";

                int titleWidth =
                    MeasureText(title, 80);

                DrawText(
                    title,
                    largura_tela / 2 - titleWidth / 2,
                    200,
                    80,
                    BLACK
                );


                // Opções do menu
                if (opcaoSelecionada == 0) {

                    DrawText(
                        "> JOGAR <",
                        largura_tela / 2.3 -
                        MeasureText("> JOGAR <", 24) / 2,
                        320,
                        44,
                        RAYWHITE
                    );

                    DrawText(
                        "FECHAR",
                        largura_tela / 2.3 -
                        MeasureText("FECHAR", 20) / 2,
                        380,
                        44,
                        BLACK
                    );

                } else {

                    DrawText(
                        "JOGAR",
                        largura_tela / 2.25 -
                        MeasureText("JOGAR", 20) / 2,
                        320,
                        44,
                        BLACK
                    );

                    DrawText(
                        "> FECHAR <",
                        largura_tela / 2.35 -
                        MeasureText("> FECHAR <", 24) / 2,
                        380,
                        44,
                        RAYWHITE
                    );
                }


                // Footer
                const char* footer =
                    "Navegue com W/S ou Setas e selecione com Enter";

                int footerWidth =
                    MeasureText(footer, 14);

                DrawText(
                    footer,
                    largura_tela / 2.6 -
                    footerWidth / 2,
                    600,
                    24,
                    BLACK
                );

                break;
            }


            // -------------------------------------------------------------------------
            // TELA DO JOGO
            // -------------------------------------------------------------------------

            case JOGANDO: {

                // Fundo do jogo
                if (fundo.id > 0) {
                    DrawTexture(fundo, 0, 0, WHITE);
                }


                // Desenha os segmentos da cobra
                for (int i = 3; i >= 0; i--) {

                    // Cabeça com cor diferente
                    Color corSegmento =
                        (i == 0) ?
                        SKYBLUE :
                        cobrinha[i].cor;


                    DrawRectangleV(
                        cobrinha[i].posicao,
                        (Vector2){
                            raio_cobrinha,
                            raio_cobrinha
                        },
                        corSegmento
                    );
                }


                // Texto de dica
                DrawText(
                    "Pressione ESC para voltar ao Menu",
                    20,
                    20,
                    20,
                    LIGHTGRAY
                );

                break;
            }


            // -------------------------------------------------------------------------
            // TELA DE GAME OVER
            // -------------------------------------------------------------------------

            case FIM: {

                // Desenha a imagem de Game Over
                if (fundoGameOver.id > 0) {
                    DrawTexture(
                        fundoGameOver,
                        0,
                        0,
                        WHITE
                    );
                }


                // -------------------------------------------------------------
                // GAME OVER CENTRALIZADO
                // -------------------------------------------------------------

                const char* gameOverText = "GAME OVER";

                int tamanhoFonte = 80;

                int larguraTexto =
                    MeasureText(
                        gameOverText,
                        tamanhoFonte
                    );


                DrawText(
                    gameOverText,
                    (largura_tela - larguraTexto) / 2,
                    (altura_tela - tamanhoFonte) / 2,
                    tamanhoFonte,
                    RED
                );


                // -------------------------------------------------------------
                // TEXTO ABAIXO DO GAME OVER
                // -------------------------------------------------------------

                const char* mensagem =
                    "Pressione ENTER para voltar ao menu";

                int tamanhoMensagem = 24;

                int larguraMensagem =
                    MeasureText(
                        mensagem,
                        tamanhoMensagem
                    );


                DrawText(
                    mensagem,
                    (largura_tela - larguraMensagem) / 2,
                    (altura_tela - tamanhoFonte) / 2 + 100,
                    tamanhoMensagem,
                    BLACK
                );


                break;
            }
        }


        EndDrawing();
    }


    // ---------------------------------------------------------------------------------
    // FINALIZAÇÃO
    // ---------------------------------------------------------------------------------

    UnloadTexture(fundo);
    UnloadTexture(fundo2);
    UnloadTexture(fundoGameOver);

    CloseWindow();


    return 0;
}