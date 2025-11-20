#ifndef JOGO_VIDA_CONWAY_H
#define JOGO_VIDA_CONWAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Tabuleiro.h"
#include "Arquivo.h"

typedef struct Jogo {
    Tabuleiro *tabuleiro;
    int num_geracoes;
} Jogo;


Jogo* criar_jogo(const char *caminho_arquivo);
void simular_jogo(Jogo *jogo);
static int contar_vizinhos_vivos(Jogo *jogo, int linha, int coluna);
void destruir_jogo(Jogo *jogo);
void salvar_resultado(Jogo *jogo);

#endif
