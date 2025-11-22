#ifndef JOGO_VIDA_CONWAY_PARALELO_H
#define JOGO_VIDA_CONWAY_PARALELO_H

#include "Jogo_Vida_Conway.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    Jogo *jogo;
    int linha_inicio;
    int linha_fim;
} ThreadArgs;

void simular_jogo_paralelo(Jogo *jogo, int num_threads);

#endif
