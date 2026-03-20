#include <stdio.h>
#include <stdbool.h>

#define N 4

void imprimirTabuleiro(int grid[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int d = 0; d < N; d++) {
            printf("%d ", grid[r][d]);
        }
        printf("\n");
    }
}

bool ehSeguro(int grid[N][N], int linha, int col, int num) {
    // Verifica linha e coluna
    for (int x = 0; x < N; x++) {
        if (grid[linha][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Verifica a subgrade 2x2
    // Para N=4, o início é linha - linha % 2
    int inicioLinha = linha - linha % 2;
    int inicioCol = col - col % 2;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (grid[i + inicioLinha][j + inicioCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool resolverSudoku(int grid[N][N]) {
    int linha, col;
    bool vazio = true;

    for (linha = 0; linha < N; linha++) {
        for (col = 0; col < N; col++) {
            if (grid[linha][col] == 0) {
                vazio = false;
                break;
            }
        }
        if (!vazio) break;
    }

    if (vazio) return true;

    for (int num = 1; num <= 4; num++) {
        if (ehSeguro(grid, linha, col, num)) {
            grid[linha][col] = num;
            if (resolverSudoku(grid)) return true;
            grid[linha][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int tabuleiro[N][N] = {
        {0,2,4,0},
        {1,0,0,3},
        {4,0,0,2},
        {0,1,3,0}
    };

    if (resolverSudoku(tabuleiro)) {
        imprimirTabuleiro(tabuleiro);
    } else {
        printf("Sem solução.");
    }

    return 0;
}