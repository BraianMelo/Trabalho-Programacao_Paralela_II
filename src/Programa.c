#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/Jogo_Vida_Conway.h"
#include "include/Jogo_Vida_Conway_Paralelo.h"

#define NUM_THREADS 2

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso correto: %s <arquivo_entrada> <seq|par>\n", argv[0]);
        return 1;
    }

    char *caminho = argv[1];
    char *modo = argv[2];
    
    Jogo *jogo = criar_jogo(caminho);
    if (!jogo) {
		printf("Falha ao inicializar o jogo!\n");
        return 1;
    }
    
    printf("Tamanho do tabuleiro: %d x %d\n", jogo->tabuleiro->linhas, jogo->tabuleiro->colunas);
    printf("Número de gerações: %d\n", jogo->num_geracoes);
    

    if (strcmp(modo, "seq") == 0) {
        printf("Modo Sequencial escolhido. \n");

        simular_jogo(jogo);


    } else if (strcmp(modo, "par") == 0) {
        printf("Modo Paralelo escolhido.\n");
        printf("Número de gerações: %d\n", jogo->num_geracoes);
        printf("Número de threads: %d\n", NUM_THREADS);
        
        simular_jogo_paralelo(jogo, NUM_THREADS);
        
    } else {
        printf("Modo inválido! Use 'seq' para sequencial ou 'par' para paralelo.\n");
        return 1;
    }
    
    salvar_resultado(jogo);
    destruir_jogo(jogo);
    
    printf("Jogo simulado! Resultado salvo em saida.txt\n");

    return 0;
}
