#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

// ---------------------------------------------------------------------------------
// 1. DEFINIÇÃO DAS ESTRUTURAS
// ---------------------------------------------------------------------------------

typedef enum EstadoJogo {
    MENU,       // Estado que exibe o menu principal e opções do usuário
<<<<<<< HEAD
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
=======
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
>>>>>>> bab00c3 (adição do draw)
    Texture2D fundo = LoadTexture("fundo.png");

    SetTargetFPS(60);

<<<<<<< HEAD
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
=======
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
>>>>>>> bab00c3 (adição do draw)
                    }
                }
                break;
            }

            case JOGANDO: {
<<<<<<< HEAD
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
    
=======
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
>>>>>>> bab00c3 (adição do draw)
