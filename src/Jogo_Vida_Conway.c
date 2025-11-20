#include "include/Jogo_Vida_Conway.h"

Jogo* criar_jogo(const char *caminho_arquivo) {
    Jogo *jogo = malloc(sizeof(Jogo));
    if (!jogo) return NULL;

    jogo->tabuleiro = ler_tabuleiro(caminho_arquivo, &jogo->num_geracoes);
    if (!jogo->tabuleiro) {
        free(jogo);
        return NULL;
    }

    return jogo;
}

static int contar_vizinhos_vivos(Jogo *jogo, int linha, int coluna) {
    int count = 0;
    int l_max = jogo->tabuleiro->linhas;
    int c_max = jogo->tabuleiro->colunas;
    int idx = jogo->tabuleiro->indice;

    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            if (i == linha && j == coluna) continue;
            if (i >= 0 && i < l_max && j >= 0 && j < c_max) {
                if (jogo->tabuleiro->celulas[i][j].estah_vivo[idx])
                    count++;
            }
        }
    }
    return count;
}

static void simular_uma_geracao(Jogo *jogo) {
    Tabuleiro *t = jogo->tabuleiro;
    int l_max = t->linhas;
    int c_max = t->colunas;
    int idx_atual = t->indice;
    int idx_novo = !t->indice;

    // Primeiro, zera a camada nova
    for (int i = 0; i < l_max; i++)
        for (int j = 0; j < c_max; j++)
            t->celulas[i][j].estah_vivo[idx_novo] = false;

    // Aplica regras do Jogo da Vida
    for (int i = 0; i < l_max; i++) {
        for (int j = 0; j < c_max; j++) {
            int vivos = contar_vizinhos_vivos(jogo, i, j);
            
            if (t->celulas[i][j].estah_vivo[idx_atual]) {
                // Célula viva
                if (vivos == 2 || vivos == 3)
                    t->celulas[i][j].estah_vivo[idx_novo] = true;
                    
                if (vivos > 3)
					t->celulas[i][j].estah_vivo[idx_novo] = false;
            } else {
                // Célula morta
                if (vivos == 3)
                    t->celulas[i][j].estah_vivo[idx_novo] = true;
            }
        }
    }

    t->indice = idx_novo;
}

void simular_jogo(Jogo *jogo) {
    for (int i = 0; i < jogo->num_geracoes; i++){
        simular_uma_geracao(jogo);
		imprimir_tabuleiro(jogo->tabuleiro);
	}
}

void salvar_resultado(Jogo *jogo) {
    escrever_tabuleiro(jogo->tabuleiro, jogo->num_geracoes);
}

void destruir_jogo(Jogo *jogo) {
    if (!jogo) return;
    if (jogo->tabuleiro)
        desalocar_tabuleiro(jogo->tabuleiro);
    free(jogo);
}
