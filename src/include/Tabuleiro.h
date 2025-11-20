#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Celula {
	bool estah_vivo[2]; 
} Celula;

typedef struct Tabuleiro {
	int linhas;
	int colunas;
	Celula **celulas;
	bool indice;
} Tabuleiro;

Tabuleiro* criar_tabuleiro(int linhas, int colunas);
void imprimir_tabuleiro(Tabuleiro *t);
void desalocar_tabuleiro(Tabuleiro *t);
void mudar_celula(Tabuleiro *t, int linha, int coluna, bool viva);
void trocar_camada(Tabuleiro *t);

#endif



