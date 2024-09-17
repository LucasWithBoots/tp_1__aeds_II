#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_LABIRINTO 10

// Estrutura para representar uma posição no labirinto
typedef struct Posicao {
    int linha;
    int coluna;
    struct Posicao *proxima; // Para implementação da pilha
} Posicao;

// Estrutura da Pilha usando lista encadeada
typedef struct Pilha {
    Posicao *topo;
} Pilha;

// Função para inicializar a pilha
void inicializarPilha(Pilha *pilha) {
    pilha->topo = NULL;
}

// Função para verificar se a pilha está vazia
int estaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

// Função para empilhar uma posição na pilha
void empilhar(Pilha *pilha, int linha, int coluna) {
    Posicao *novaPosicao = (Posicao *)malloc(sizeof(Posicao));
    novaPosicao->linha = linha;
    novaPosicao->coluna = coluna;
    novaPosicao->proxima = pilha->topo;
    pilha->topo = novaPosicao;
}

// Função para desempilhar uma posição da pilha
void desempilhar(Pilha *pilha) {
    if (estaVazia(pilha)) {
        return;
    }
    Posicao *temp = pilha->topo;
    pilha->topo = pilha->topo->proxima;
    free(temp);
}

// Função para obter a posição no topo da pilha sem removê-la
Posicao *topo(Pilha *pilha) {
    if (estaVazia(pilha)) {
        return NULL;
    }
    return pilha->topo;
}

// Função para verificar se um movimento é válido
int movimentoValido(char labirinto[TAMANHO_LABIRINTO][TAMANHO_LABIRINTO], int visitado[TAMANHO_LABIRINTO][TAMANHO_LABIRINTO], int linha, int coluna) {
    // Verificar limites
    if (linha < 0 || linha >= TAMANHO_LABIRINTO || coluna < 0 || coluna >= TAMANHO_LABIRINTO) {
        return 0;
    }
    // Verificar se a célula não é uma parede e não foi visitada
    if ((labirinto[linha][coluna] == '0' || labirinto[linha][coluna] == 'S') && !visitado[linha][coluna]) {
        return 1;
    }
    return 0;
}

// Função para imprimir o caminho a partir da pilha
void imprimirCaminho(Pilha *pilha) {
    // Para armazenar as posições do caminho
    Posicao *caminho[TAMANHO_LABIRINTO * TAMANHO_LABIRINTO];
    int contador = 0;

    // Copiar posições da pilha para o array
    Posicao *atual = pilha->topo;
    while (atual != NULL) {
        caminho[contador++] = atual;
        atual = atual->proxima;
    }

    // Imprimir posições em ordem reversa
    for (int i = contador - 1; i >= 0; i--) {
        // Ajustar coordenadas: x = coluna, y = linha invertida
        int x = caminho[i]->coluna;
        int y = TAMANHO_LABIRINTO - 1 - caminho[i]->linha;
        printf("%d,%d\n", x, y);
    }
}

int main() {
    char labirinto[TAMANHO_LABIRINTO][TAMANHO_LABIRINTO] = {
        {'X', 'X', '0', '0', '0', '0', 'S', 'X', 'X', 'X'},
        {'0', '0', '0', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'0', 'X', '0', '0', '0', '0', 'X', '0', '0', '0'},
        {'0', 'X', '0', 'X', 'X', '0', 'X', '0', 'X', '0'},
        {'0', 'X', '0', 'X', 'X', '0', '0', '0', 'X', '0'},
        {'0', 'X', '0', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
        {'0', 'X', '0', '0', '0', '0', '0', 'X', 'X', 'X'},
        {'0', 'X', 'X', 'X', 'X', 'X', '0', 'X', 'X', 'X'},
        {'0', '0', '0', 'X', 'X', '0', '0', '0', 'X', 'X'},
        {'0', 'X', 'X', 'X', 'X', '0', 'X', 'E', 'X', 'X'}
    };

    int visitado[TAMANHO_LABIRINTO][TAMANHO_LABIRINTO];
    memset(visitado, 0, sizeof(visitado));

    int linhaInicio, colunaInicio, linhaFim, colunaFim;

    // Encontrar a posição inicial 'E' e a posição final 'S'
    for (int linha = 0; linha < TAMANHO_LABIRINTO; linha++) {
        for (int coluna = 0; coluna < TAMANHO_LABIRINTO; coluna++) {
            if (labirinto[linha][coluna] == 'E') {
                linhaInicio = linha;
                colunaInicio = coluna;
            }
            if (labirinto[linha][coluna] == 'S') {
                linhaFim = linha;
                colunaFim = coluna;
            }
        }
    }

    Pilha pilha;
    inicializarPilha(&pilha);

    // Empilhar a posição inicial na pilha
    empilhar(&pilha, linhaInicio, colunaInicio);
    visitado[linhaInicio][colunaInicio] = 1;

    int encontrouSaida = 0;

    // Movimentos possíveis: cima, baixo, esquerda, direita
    int movimentoLinha[] = {-1, 1, 0, 0};
    int movimentoColuna[] = {0, 0, -1, 1};

    while (!estaVazia(&pilha)) {
        Posicao *atual = topo(&pilha);

        if (atual->linha == linhaFim && atual->coluna == colunaFim) {
            // Encontrou a saída
            encontrouSaida = 1;
            break;
        }

        int moveu = 0;
        for (int i = 0; i < 4; i++) {
            int novaLinha = atual->linha + movimentoLinha[i];
            int novaColuna = atual->coluna + movimentoColuna[i];

            if (movimentoValido(labirinto, visitado, novaLinha, novaColuna)) {
                empilhar(&pilha, novaLinha, novaColuna);
                visitado[novaLinha][novaColuna] = 1;
                moveu = 1;
                break;
            }
        }

        if (!moveu) {
            // Sem movimentos válidos, retrocede
            desempilhar(&pilha);
        }
    }

    if (encontrouSaida) {
        imprimirCaminho(&pilha);
    } else {
        printf("Nenhum caminho encontrado de 'E' até 'S'.\n");
    }

    // Liberar a pilha
    while (!estaVazia(&pilha)) {
        desempilhar(&pilha);
    }

    return 0;
}
