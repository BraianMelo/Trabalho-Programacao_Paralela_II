#ifndef JOGO_VIDA_CONWAY_PARALELO_H
#define JOGO_VIDA_CONWAY_PARALELO_H

#include "Tabuleiro.h"
#include "Arquivo.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Tabuleiro *tabuleiro;
    int num_geracoes;
    int num_threads;
} JogoParalelo;

typedef struct {
    JogoParalelo *jogo;
    int linha_inicio;
    int linha_fim;
} ThreadArgs;

JogoParalelo* criar_jogo_paralelo(const char *caminho_arquivo, int num_threads);
void* processar_linhas(void *arg);
void simular_jogo_paralelo(JogoParalelo *jogo);
void salvar_resultado_paralelo(JogoParalelo *jogo);
void destruir_jogo_paralelo(JogoParalelo *jogo);

#endif
