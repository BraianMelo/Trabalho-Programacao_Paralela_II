#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARQ_SAIDA "saida.txt"

Tabuleiro* ler_tabuleiro(const char *caminho, int *num_geracoes);
void escrever_tabuleiro(Tabuleiro *t, int num_geracoes);

#endif
