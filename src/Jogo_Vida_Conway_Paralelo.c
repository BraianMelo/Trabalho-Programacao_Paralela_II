#include "include/Jogo_Vida_Conway_Paralelo.h"

JogoParalelo* criar_jogo_paralelo(const char *caminho_arquivo, int num_threads) {
    JogoParalelo *jogo = malloc(sizeof(JogoParalelo));
    if (!jogo) return NULL;

    jogo->tabuleiro = ler_tabuleiro(caminho_arquivo, &jogo->num_geracoes);
    if (!jogo->tabuleiro) {
        free(jogo);
        return NULL;
    }

    jogo->num_threads = num_threads;
    return jogo;
}

static int contar_vizinhos_vivos(JogoParalelo *jogo, int linha, int coluna) {
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

void* processar_linhas(void *arg) {
    ThreadArgs *args = (ThreadArgs*) arg;
    JogoParalelo *jogo = args->jogo;

    Tabuleiro *t = jogo->tabuleiro;
    int idx_atual = t->indice;
    int idx_novo = !t->indice;

    for (int i = args->linha_inicio; i < args->linha_fim; i++) {
        for (int j = 0; j < t->colunas; j++) {
            int vivos = contar_vizinhos_vivos(jogo, i, j);

            if (t->celulas[i][j].estah_vivo[idx_atual]) {
                if (vivos == 2 || vivos == 3)
                    t->celulas[i][j].estah_vivo[idx_novo] = true;
                else
                    t->celulas[i][j].estah_vivo[idx_novo] = false;
            } else {
                if (vivos == 3)
                    t->celulas[i][j].estah_vivo[idx_novo] = true;
            }
        }
    }

    return NULL;
}

static void simular_uma_geracao(JogoParalelo *jogo) {
    pthread_t threads[jogo->num_threads];
    ThreadArgs args[jogo->num_threads];

    Tabuleiro *t = jogo->tabuleiro;
    int l_max = t->linhas;
    int idx_novo = !t->indice;

    // Zera camada nova
    for (int i = 0; i < l_max; i++)
        for (int j = 0; j < t->colunas; j++)
            t->celulas[i][j].estah_vivo[idx_novo] = false;

    int linhas_por_thread = l_max / jogo->num_threads;

    // Cria threads
    for (int i = 0; i < jogo->num_threads; i++) {
        args[i].jogo = jogo;
        args[i].linha_inicio = i * linhas_por_thread;

        if (i == jogo->num_threads - 1)
            args[i].linha_fim = l_max;  
        else
            args[i].linha_fim = (i + 1) * linhas_por_thread;

        pthread_create(&threads[i], NULL, processar_linhas, &args[i]);
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < jogo->num_threads; i++)
        pthread_join(threads[i], NULL);

    t->indice = idx_novo;
}

void simular_jogo_paralelo(JogoParalelo *jogo) {
    for (int i = 0; i < jogo->num_geracoes; i++) {
        simular_uma_geracao(jogo);
    }
}

void salvar_resultado_paralelo(JogoParalelo *jogo) {
    escrever_tabuleiro(jogo->tabuleiro, jogo->num_geracoes);
}

void destruir_jogo_paralelo(JogoParalelo *jogo) {
    if (!jogo) return;
    if (jogo->tabuleiro)
        desalocar_tabuleiro(jogo->tabuleiro);
    free(jogo);
}
