#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

#define TAMANHO_HABILIDADE 5

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");
            else
                printf("? ");
        }
        printf("\n");
    }
}

// Gera matriz de habilidade em cone (ponta para baixo)
void gerarCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade em cruz
void gerarCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade em octaedro (losango)
void gerarOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int l = origemLinha - offset + i;
                int c = origemColuna - offset + j;
                if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                    if (tabuleiro[l][c] == AGUA)
                        tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

// Posiciona um navio no tabuleiro
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i;
        int c = coluna;

        if (diagonal) {
            c = (direcao == 1) ? coluna + i : coluna - i;
        } else {
            if (direcao == 0) { // horizontal
                l = linha;
                c = coluna + i;
            }
        }

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + i;
        int c = coluna;

        if (diagonal) {
            c = (direcao == 1) ? coluna + i : coluna - i;
        } else {
            if (direcao == 0) { // horizontal
                l = linha;
                c = coluna + i;
            }
        }

        tabuleiro[l][c] = NAVIO;
    }
}

// Programa principal
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionamento de navios
    if (podePosicionar(tabuleiro, 2, 3, 0, 0)) posicionarNavio(tabuleiro, 2, 3, 0, 0);
    if (podePosicionar(tabuleiro, 5, 5, 1, 0)) posicionarNavio(tabuleiro, 5, 5, 1, 0);

    // Matrizes de habilidade
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Aplicar habilidades
    aplicarHabilidade(tabuleiro, cone, 1, 1);       // Topo do cone em (1,1)
    aplicarHabilidade(tabuleiro, cruz, 7, 7);       // Centro da cruz em (7,7)
    aplicarHabilidade(tabuleiro, octaedro, 4, 4);   // Centro do octaedro em (4,4)

    // Mostrar resultado
    imprimirTabuleiro(tabuleiro);

    return 0;
}