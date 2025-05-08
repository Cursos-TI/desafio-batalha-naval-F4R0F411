#include <stdio.h>

// Define o tamanho do tabuleiro e o valor de um navio
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se é possível posicionar um navio sem sair dos limites e sem sobreposição
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;
        
        if (diagonal) {
            // Para diagonais
            l = (direcao == 1) ? linha + i : linha + i;        // Direção da linha aumenta
            c = (direcao == 1) ? coluna + i : coluna - i;       // Coluna aumenta ou diminui
        } else {
            // Para horizontal e vertical
            l = (direcao == 0) ? linha : linha + i;  // 0 = horizontal, 1 = vertical
            c = (direcao == 0) ? coluna + i : coluna;
        }

        // Verifica se está fora dos limites ou se já tem navio
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != AGUA) {
            return 0; // Não pode posicionar
        }
    }
    return 1; // Pode posicionar
}

// Função para posicionar um navio
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (diagonal) {
            // Para diagonais
            l = (direcao == 1) ? linha + i : linha + i;
            c = (direcao == 1) ? coluna + i : coluna - i;
        } else {
            // Para horizontal e vertical
            l = (direcao == 0) ? linha : linha + i;
            c = (direcao == 0) ? coluna + i : coluna;
        }
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    // Inicializa o tabuleiro com água
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionar dois navios horizontais/verticais
    // Navio 1: Horizontal a partir da posição (2,3)
    int linha1 = 2, coluna1 = 3, direcao1 = 0, diagonal1 = 0; // 0 = horizontal
    if (podePosicionar(tabuleiro, linha1, coluna1, direcao1, diagonal1)) {
        posicionarNavio(tabuleiro, linha1, coluna1, direcao1, diagonal1);
    } else {
        printf("Erro: Não foi possível posicionar o Navio 1.\n");
        return 1;
    }

    // Navio 2: Vertical a partir da posição (5,5)
    int linha2 = 5, coluna2 = 5, direcao2 = 1, diagonal2 = 0; // 1 = vertical
    if (podePosicionar(tabuleiro, linha2, coluna2, direcao2, diagonal2)) {
        posicionarNavio(tabuleiro, linha2, coluna2, direcao2, diagonal2);
    } else {
        printf("Erro: Não foi possível posicionar o Navio 2.\n");
        return 1;
    }

    // Posicionar dois navios em diagonal
    // Navio 3: Diagonal principal a partir da posição (0,0)
    int linha3 = 0, coluna3 = 0, direcao3 = 1, diagonal3 = 1; // 1 = sentido normal da diagonal (linha++, coluna++)
    if (podePosicionar(tabuleiro, linha3, coluna3, direcao3, diagonal3)) {
        posicionarNavio(tabuleiro, linha3, coluna3, direcao3, diagonal3);
    } else {
        printf("Erro: Não foi possível posicionar o Navio 3.\n");
        return 1;
    }

    // Navio 4: Diagonal secundária a partir da posição (0,9)
    int linha4 = 0, coluna4 = 9, direcao4 = -1, diagonal4 = 1; // -1 = sentido inverso da diagonal (linha++, coluna--)
    if (podePosicionar(tabuleiro, linha4, coluna4, direcao4, diagonal4)) {
        posicionarNavio(tabuleiro, linha4, coluna4, direcao4, diagonal4);
    } else {
        printf("Erro: Não foi possível posicionar o Navio 4.\n");
        return 1;
    }

    // Exibe o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}