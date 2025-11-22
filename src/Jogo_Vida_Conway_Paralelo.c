#include "include/Jogo_Vida_Conway_Paralelo.h"

static pthread_barrier_t barreira;
static ThreadArgs *args_threads = NULL;
static pthread_t *threads = NULL;
static int N_THREADS = 1;

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


static void* processar_fatia(void *arg) {
    ThreadArgs *info = (ThreadArgs*) arg;
    Jogo *jogo = info->jogo;
    Tabuleiro *t = jogo->tabuleiro;
    int c_max = t->colunas;

    for (int g = 0; g < jogo->num_geracoes; g++) {

        int idx_atual = t->indice;
        int idx_novo = !t->indice;

        // Zera e processa sua fatia ao mesmo tempo
        for (int i = info->linha_inicio; i < info->linha_fim; i++) {
            for (int j = 0; j < c_max; j++) {
                t->celulas[i][j].estah_vivo[idx_novo] = false;

                int vivos = contar_vizinhos_vivos(jogo, i, j);
                bool atual = t->celulas[i][j].estah_vivo[idx_atual];

                if (atual) {
                    if (vivos == 2 || vivos == 3)
                        t->celulas[i][j].estah_vivo[idx_novo] = true;
                } else {
                    if (vivos == 3)
                        t->celulas[i][j].estah_vivo[idx_novo] = true;
                }
            }
        }

        // Apenas uma thread troca o índice e todas aguardam aqui
        if (info->linha_inicio == 0)
            t->indice = idx_novo;

        // Uma única barreira para sincronizar todas as threads antes da próxima geração
        pthread_barrier_wait(&barreira);
    }

    return NULL;
}

void simular_jogo_paralelo(Jogo *jogo, int num_threads) {

    N_THREADS = num_threads;
    Tabuleiro *t = jogo->tabuleiro;
    int linhas = t->linhas;

    threads = malloc(sizeof(pthread_t) * N_THREADS);
    args_threads = malloc(sizeof(ThreadArgs) * N_THREADS);

    pthread_barrier_init(&barreira, NULL, N_THREADS);

    int fatia = linhas / N_THREADS;

    for (int i = 0; i < N_THREADS; i++) {

        args_threads[i].jogo = jogo;
        args_threads[i].linha_inicio = i * fatia;
        args_threads[i].linha_fim =
            (i == N_THREADS - 1 ? linhas : (i + 1) * fatia);

        pthread_create(&threads[i], NULL, processar_fatia, &args_threads[i]);
    }

    for (int i = 0; i < N_THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_barrier_destroy(&barreira);

    free(threads);
    free(args_threads);
}
