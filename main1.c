#include <stdio.h>
#include <stdbool.h>
#include "teclado.h"

// Funções de movimentação
bool mover_cima(int mat[4][4]) {
    int aux;
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            if (mat[i][j] == 0) {
                aux = mat[i - 1][j];
                mat[i - 1][j] = mat[i][j];
                mat[i][j] = aux;
            }
        }
    }
    return true;
}

bool mover_baixo(int mat[4][4]) {
    int aux;
    for (int j = 0; j < 4; j++) {
        for (int i = 2; i >= 0; i--) {
            if (mat[i][j] == 0) {
                aux = mat[i + 1][j];
                mat[i + 1][j] = mat[i][j];
                mat[i][j] = aux;
            }
        }
    }
    return true;
}

bool mover_esquerda(int matriz[4][4]) {
    int aux;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (matriz[i][j] == 0) {
                aux = matriz[i][j - 1];
                matriz[i][j - 1] = matriz[i][j];
                matriz[i][j] = aux;
            }
        }
    }
    return true;
}

bool mover_direita(int matriz[4][4]) {
    int aux;
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (matriz[i][j] == 0) {
                aux = matriz[i][j + 1];
                matriz[i][j + 1] = matriz[i][j];
                matriz[i][j] = aux;
            }
        }
    }
    return true;
}

// Função para imprimir a matriz
void imprimir_matriz(int matriz[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf(" %d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o jogo foi ganho
bool ganhou(int matriz[4][4]) {
    int matri_certo[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};
    int certos = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matri_certo[i][j] == matriz[i][j]) {
                certos++;
            }
        }
    }
    return certos == 15;  // Se todos os números estiverem corretos (exceto o 0), o jogo acabou
}

int main() {
    int fim = 1;
    tecla_t tec; // Mudança de char para tecla_t

    int matriz[4][4] = {
        {1, 2, 3, 4},
        {5, 0, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 6, 15}
    };

    // Inicializa a leitura do teclado
    tec_inicia();

    // Loop principal do jogo
    while (!ganhou(matriz)) {
        // Captura a tecla pressionada
        tec = tec_tecla(); // Captura a tecla pressionada

        // Verifica se alguma tecla foi pressionada (não permite movimento contínuo)
        if (tec != T_NADA) {
            // Se o usuário pressionou a tecla de "fim" (END), o jogo termina
            if (tec == T_END) {
                break;
            }

            // Movimenta a peça dependendo da tecla pressionada
            switch (tec) {
                case T_CIMA:
                    mover_cima(matriz);
                    break;
                case T_BAIXO:
                    mover_baixo(matriz);
                    break;
                case T_ESQUERDA:
                    mover_esquerda(matriz);
                    break;
                case T_DIREITA:
                    mover_direita(matriz);
                    break;
                default:
                    break;
            }

            // Imprime a matriz após o movimento
            imprimir_matriz(matriz);
            printf("\n");
        }

    }

    // Finaliza a leitura do teclado
    tec_fim();

    return 0;
}
