#include <stdio.h>
#include <stdbool.h>
#include "teclado.h"  // Inclui a biblioteca do teclado

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

void imprimir_matriz(int matriz[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf(" %d ", matriz[i][j]);
        }
        printf("\n");
    }
}

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

    return certos == 15;
}

int main() {
    tecla_t tecla;  // Variável para armazenar a tecla pressionada
    int matriz[4][4] = {
        {1, 2, 3, 4},
        {5, 0, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 6, 15}
    };

    tec_inicia();  // Inicializa o teclado em modo cru
    imprimir_matriz(matriz);

    while (!ganhou(matriz)) {  // Loop até o jogo ser ganho
        tecla = tec_tecla();  // Captura a tecla pressionada

        // Processa apenas as teclas de direção
        switch (tecla) {
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
            case T_NADA:
                // Nenhuma tecla foi pressionada
                continue;
            default:
                // Se uma tecla inválida for pressionada, podemos ignorá-la
                printf("Tecla inválida! Pressione uma tecla de direção (setas).\n");
                continue;
        }

        imprimir_matriz(matriz);  // Imprime a matriz após o movimento
        printf("\n");
    }

    printf("Você ganhou!\n");
    tec_fim();  // Finaliza o teclado em modo cru
    return 0;
}
