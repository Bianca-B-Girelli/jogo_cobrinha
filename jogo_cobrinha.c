#include "raylib.h"
#include <stdbool.h>
#include <stdio.h> 
#include "cobra.h"


// ---------------------------------------------------------------------------------
// 1. DEFINIÇÃO DAS ESTRUTURAS
// ---------------------------------------------------------------------------------

typedef enum EstadoJogo {
    MENU,       // Estado que exibe o menu principal e opções do usuário
    JOGANDO,    // Estado ativo de simulação com a cobrinha
    FIM         // Estado de Game Over
} EstadoJogo;



void mover_cobrinha(Cabecalho *cobra, float *contadorTempo, float tempoPasso, float raio_cobrinha, Vector2 direcao) {
    *contadorTempo += GetFrameTime();

    if (*contadorTempo >= tempoPasso) {

        *contadorTempo -= tempoPasso;

        if (cobra == NULL || cobra->inicio == NULL) return;

        // Atualiza a posição de cada nó do fim para o início (o nó assume a posição do anterior)
        // atualizar os valores das posições de trás para frente.
        int len = cobra->len;
        if (len > 1) {
            // Cria um array temporário com as posições atuais para reatribuir aos nós
            Vector2 posicoes[len];
            Node *atual = cobra->inicio;
            int idx = 0;
            while (atual != NULL) {
                posicoes[idx++] = atual->posicao;
                atual = atual->next;
            }

            // Desloca as posições do corpo
            atual = cobra->inicio->next;
            idx = 0;
            while (atual != NULL) {
                atual->posicao = posicoes[idx++];
                atual = atual->next;
            }
        }

        // Atualiza a posição da cabeça (primeiro nó)
        cobra->inicio->posicao.x += direcao.x * raio_cobrinha;
        cobra->inicio->posicao.y += direcao.y * raio_cobrinha;
    }
}


void encerrar_jogo(Cabecalho *cobra, int largura_tela, int altura_tela, float raio_cobrinha, EstadoJogo *estadoAtual, bool *viva) {
    if (cobra == NULL || cobra->inicio == NULL) return;

    Vector2 cabeca = cobra->inicio->posicao;

    if (cabeca.x < 0 ||
        cabeca.x > (float)largura_tela - raio_cobrinha ||
        cabeca.y < 0 ||
        cabeca.y > (float)altura_tela - raio_cobrinha) {

        *viva = false;
        *estadoAtual = FIM;
    }
}

void desenhar_menu(Texture2D fundo, int opcaoSelecionada, int largura_tela) {
    // Desenha a imagem de fundo do menu
    if (fundo.id > 0) {
        DrawTexture(fundo, 0, 0, WHITE);
    }

    // Título
    const char* title = "JOGO DA COBRINHA";
    int titleWidth = MeasureText(title, 80);
    DrawText(title, largura_tela / 2 - titleWidth / 2, 200, 80, BLACK);

    // Opções do menu
    if (opcaoSelecionada == 0) {
        DrawText("> JOGAR <", largura_tela / 2.3 - MeasureText("> JOGAR <", 24) / 2, 320, 44, RAYWHITE);
        DrawText("FECHAR", largura_tela / 2.3 - MeasureText("FECHAR", 20) / 2, 380, 44, BLACK);
    } else {
        DrawText("JOGAR", largura_tela / 2.25 - MeasureText("JOGAR", 20) / 2, 320, 44, BLACK);
        DrawText("> FECHAR <", largura_tela / 2.35 - MeasureText("> FECHAR <", 24) / 2, 380, 44, RAYWHITE);
    }

    // Instrução no rodapé
    const char* footer = "Navegue com W/S ou Setas e selecione com Enter";
    int footerWidth = MeasureText(footer, 14);
    DrawText(footer, largura_tela / 2.6 - footerWidth / 2, 600, 24, BLACK);
}

void desenhar_game_over(Texture2D fundoGameOver, int largura_tela, int altura_tela) {
    // Fundo da tela de Game Over
    if (fundoGameOver.id > 0) {
        DrawTexture(fundoGameOver, 0, 0, WHITE);
    }

    // Título "GAME OVER"
    const char* gameOverText = "GAME OVER";
    int tamanhoFonte = 80;
    int larguraTexto = MeasureText(gameOverText, tamanhoFonte);

    DrawText(
        gameOverText,
        (largura_tela - larguraTexto) / 2,
        (altura_tela - tamanhoFonte) / 2,
        tamanhoFonte,
        RED
    );

    // Mensagem de instrução
    const char* mensagem = "Pressione ENTER para voltar ao menu";
    int tamanhoMensagem = 24;
    int larguraMensagem = MeasureText(mensagem, tamanhoMensagem);

    DrawText(
        mensagem,
        (largura_tela - larguraMensagem) / 2,
        (altura_tela - tamanhoFonte) / 2 + 100,
        tamanhoMensagem,
        BLACK
    );
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

    // ALTERAÇÃO: Adicionada a variável cobraViva para controlar o estado da lista
    bool cobraViva = true;

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

    // Inicialização do ponteiro da cobra gerenciado pela lista encadeada
    Cabecalho *cobra = NULL;


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
                    if (opcaoSelecionada == 0) {
                        // Limpa a cobra anterior se existir
                        if (cobra != NULL) {
                            destruir_cobra(cobra);
                        }

                        // ALTERAÇÃO: Cria a cobra apenas com a cabeça (1 nó)
                        cobra = criar_cobra();
                        Vector2 posInicial = { 600.0f, 400.0f };
                        inserir_fim(cobra, posInicial, SKYBLUE);

                        cobraViva = true;
                        direcao = (Vector2){ 0, -1 };
                        contadorTempo = 0.0f;
                        estadoAtual = JOGANDO;
                    } else if (opcaoSelecionada == 1) {
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


                // ALTERAÇÃO: Verifica se a cobra existe e está viva usando cobraViva
                if (cobraViva && cobra != NULL) {
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

                    // ALTERAÇÃO: Tecla C para aumentar a cobra (inserir nó no fim)
                    if (IsKeyPressed(KEY_C)) {
                        if (cobra != NULL && cobra->fim != NULL) {
                            Vector2 novaPos = { 
                                cobra->fim->posicao.x - (direcao.x * raio_cobrinha), 
                                cobra->fim->posicao.y - (direcao.y * raio_cobrinha) 
                            };
                            inserir_fim(cobra, novaPos, BLUE);
                        }
                    }



                    // ALTERAÇÃO: Tecla ESPAÇO para apagar a lista e reiniciar só com a cabeça
                    if (IsKeyPressed(KEY_SPACE)) {

                        if (cobra != NULL) {
                            destruir_cobra(cobra);
                        }

                        cobra = criar_cobra();
                        Vector2 posInicial = { 600.0f, 400.0f };
                        inserir_fim(cobra, posInicial, SKYBLUE);
                    }

                    // -------------------------------------------------------------
                    // MOVIMENTO DA COBRA
                    // -------------------------------------------------------------

                   // ALTERAÇÃO: Passa o ponteiro da lista `cobra`
                    mover_cobrinha(cobra, &contadorTempo, tempoPasso, raio_cobrinha, direcao);

                    // -------------------------------------------------------------
                    // COLISÃO COM AS BORDAS
                    // -------------------------------------------------------------
                    
                    // ALTERAÇÃO: Passa os ponteiros corretos da lista e da flag cobraViva
                    encerrar_jogo(cobra, largura_tela, altura_tela, raio_cobrinha, &estadoAtual, &cobraViva);
                }

                break;
            }


            // -------------------------------------------------------------------------
            // GAME OVER
            // -------------------------------------------------------------------------

            case FIM: {

                // Pressiona ENTER para voltar ao menu
                if (IsKeyPressed(KEY_ENTER)) {

                    cobraViva = true; //Removi 'cobrinha[0].viva = true' para usar 'cobraViva'

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
                desenhar_menu(fundo2, opcaoSelecionada, largura_tela);
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


                // ALTERAÇÃO: Desenha os nós percorrendo a lista encadeada 
                if (cobra != NULL) {
                    Node *atual = cobra->inicio;
                    while (atual != NULL) {
                        // Define cor diferente para a cabeça (primeiro nó)
                        Color corSegmento = (atual == cobra->inicio) ? SKYBLUE : atual->cor;

                        DrawRectangleV(
                            atual->posicao,
                            (Vector2){ raio_cobrinha, raio_cobrinha },
                            corSegmento
                        );
                        atual = atual->next;
                    }
                }


                // Texto de dica
                DrawText(
                    "Pressione ESC para voltar ao Menu",
                    20,
                    20,
                    20,
                    LIGHTGRAY
                );

                // ALTERAÇÃO: Dicas das teclas de teste adicionadas na tela
                DrawText("Tecla C: Aumenta a cobra | ESPACO: Reinicia a lista", 20, 50, 20, YELLOW);

                break;
            }


            // -------------------------------------------------------------------------
            // TELA DE GAME OVER
            // -------------------------------------------------------------------------

            case FIM: {

                desenhar_game_over(fundoGameOver, largura_tela, altura_tela);
                break;
            }
            
        }


        EndDrawing();
    }


    // ---------------------------------------------------------------------------------
    // FINALIZAÇÃO
    // ---------------------------------------------------------------------------------

    // ALTERAÇÃO: Limpeza de memória da lista encadeada ao fechar o jogo
    if (cobra != NULL) {
        destruir_cobra(cobra);
    }


    UnloadTexture(fundo);
    UnloadTexture(fundo2);
    UnloadTexture(fundoGameOver);

    CloseWindow();


    return 0;
}