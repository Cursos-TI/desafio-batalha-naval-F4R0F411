#include <stdio.h>

// Define o tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10
// Define o tamanho dos navios
#define TAMANHO_NAVIO 3

int main() {
    // Matriz que representa o tabuleiro, inicializada com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Vetores que representam os navios
    int navioHorizontal[TAMANHO_NAVIO] = {3, 3, 3}; // 3 posições ocupadas por 3
    int navioVertical[TAMANHO_NAVIO] = {3, 3, 3};   // 3 posições ocupadas por 3

    // Coordenadas iniciais dos navios (definidas diretamente no código)
    int linhaInicialHorizontal = 2;
    int colunaInicialHorizontal = 4;
    
    int linhaInicialVertical = 5;
    int colunaInicialVertical = 7;

    // Verificação para garantir que os navios cabem no tabuleiro (horizontal)
    if (colunaInicialHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Posiciona o navio horizontalmente
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaInicialHorizontal][colunaInicialHorizontal + i] = navioHorizontal[i];
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites do tabuleiro.\n");
        return 1; // Encerra o programa com erro
    }

    // Verificação para garantir que os navios cabem no tabuleiro (vertical)
    if (linhaInicialVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaInicialVertical + i][colunaInicialVertical] != 0) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            // Posiciona o navio verticalmente
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linhaInicialVertical + i][colunaInicialVertical] = navioVertical[i];
            }
        } else {
            printf("Erro: Sobreposição de navios detectada.\n");
            return 1; // Encerra o programa com erro
        }
    } else {
        printf("Erro: Navio vertical fora dos limites do tabuleiro.\n");
        return 1; // Encerra o programa com erro
    }

    // Exibe o tabuleiro no console
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime cada elemento seguido de um espaço
        }
        printf("\n"); // Quebra de linha ao final de cada linha do tabuleiro
    }

    return 0;
}