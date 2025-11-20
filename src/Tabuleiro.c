#include "include/Tabuleiro.h"

Tabuleiro* criar_tabuleiro(int linhas, int colunas) {
    Tabuleiro *t = malloc(sizeof(Tabuleiro));
    if (!t) return NULL;

    t->linhas = linhas;
    t->colunas = colunas;
    t->indice = false; 

    t->celulas = malloc(linhas * sizeof(Celula*));
    if (!t->celulas) {
        free(t);
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {
        t->celulas[i] = calloc(colunas, sizeof(Celula));
        if (!t->celulas[i]) {
            for (int j = 0; j < i; j++)
                free(t->celulas[j]);
            free(t->celulas);
            free(t);
            return NULL;
        }
    }

    return t;
}

void imprimir_tabuleiro(Tabuleiro *t) {
    for (int i = 0; i < t->linhas; i++) {
        for (int j = 0; j < t->colunas; j++) {
            if (t->celulas[i][j].estah_vivo[t->indice])
                printf("O "); // célula viva
            else
                printf(". "); // célula morta
        }
        printf("\n");
    }
}

void desalocar_tabuleiro(Tabuleiro *t) {
    if (!t) return;
    for (int i = 0; i < t->linhas; i++)
        free(t->celulas[i]);
    free(t->celulas);
    free(t);
}


void mudar_celula(Tabuleiro *t, int linha, int coluna, bool viva) {
    if (linha < 0 || linha >= t->linhas || coluna < 0 || coluna >= t->colunas) return;
    t->celulas[linha][coluna].estah_vivo[t->indice] = viva;
}

// Alterna a camada atual
void trocar_camada(Tabuleiro *t) {
    t->indice = !t->indice;
}
