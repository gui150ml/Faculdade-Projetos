#include <stdio.h>
#include <stdbool.h>
#include "teclado.h"
#include "video.h"


cor_t COR_TEXTO = {10, 5, 25};    
cor_t COR_FUNDO = {50, 30, 30};       
cor_t COR_CELULA = {255, 255, 0};       
cor_t COR_VAZIA = {0, 0, 0};          

//aqui vai desenha o tabuleiro
void desenhar_tela(int mat[4][4]) {
    vid_limpa();

    
    vid_cor_fundo(COR_FUNDO);
    vid_cor_texto(COR_FUNDO);  
    vid_pos((posicao_t){0, 0});
    for (int i = 0; i < 30; i++) {
        vid_imps("                                                  \n");
    }

    //o Tabuleiro
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            posicao_t pos = {5 + i * 2, 10 + j * 6};
            vid_pos(pos);

            if (mat[i][j] == 0) {
                vid_cor_fundo(COR_VAZIA);
                vid_cor_texto(COR_VAZIA);
                vid_imps("      ");
            } else {
                vid_cor_fundo(COR_CELULA);
                vid_cor_texto(COR_TEXTO);
                char buffer[8];
                snprintf(buffer, sizeof(buffer), " %2d   ", mat[i][j]);
                vid_imps(buffer);
            }
        }
    }

    vid_atualiza();
}

//===================== funções de movimento =====================================
bool mover_cima(int mat[4][4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            if (mat[i][j] == 0) {
                int aux = mat[i - 1][j];
                mat[i - 1][j] = 0;
                mat[i][j] = aux;
            }
        }
    }
    return true;
}

bool mover_baixo(int mat[4][4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 2; i >= 0; i--) {
            if (mat[i][j] == 0) {
                int aux = mat[i + 1][j];
                mat[i + 1][j] = 0;
                mat[i][j] = aux;
            }
        }
    }
    return true;
}

bool mover_esquerda(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (mat[i][j] == 0) {
                int aux = mat[i][j - 1];
                mat[i][j - 1] = 0;
                mat[i][j] = aux;
            }
        }
    }
    return true;
}

bool mover_direita(int mat[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (mat[i][j] == 0) {
                int aux = mat[i][j + 1];
                mat[i][j + 1] = 0;
                mat[i][j] = aux;
            }
        }
    }
    return true;
}

//vai ver se ganhou
bool ganhou(int mat[4][4]) {
    int correto[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };
    int certos = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[i][j] == correto[i][j]) {
                certos++;
            }
        }
    }

    return certos == 16;
}


int main() {
    tecla_t tecla;
    int matriz[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 0, 15}
    };

    tec_inicia();
    vid_inicia();

    desenhar_tela(matriz);

    while (!ganhou(matriz)) {
        tecla = tec_tecla();

        switch (tecla) {
            case T_CIMA: mover_cima(matriz); break;
            case T_BAIXO: mover_baixo(matriz); break;
            case T_ESQUERDA: mover_esquerda(matriz); break;
            case T_DIREITA: mover_direita(matriz); break;
            case T_NADA: continue;
            default: continue;
        }

        desenhar_tela(matriz);
    }


    posicao_t pos = {15, 10};
    vid_pos(pos);
    vid_cor_texto((cor_t){0, 255, 0});
    vid_cor_fundo(COR_FUNDO);
    vid_imps("Vitoria!");

    vid_atualiza();
    tec_fim();
    vid_fim();

    return 0;
}
