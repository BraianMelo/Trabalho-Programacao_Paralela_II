#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "include/Jogo_Vida_Conway.h"
#include "include/Jogo_Vida_Conway_Paralelo.h"

#define NUM_THREADS 4

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

    if (strcmp(modo, "seq") == 0) {
        printf("Modo Sequencial escolhido. \n");
        printf("Número de gerações: %d\n", jogo->num_geracoes);

        simular_jogo(jogo);

        salvar_resultado(jogo);
        destruir_jogo(jogo);

    } else if (strcmp(modo, "par") == 0) {
        printf("Modo Paralelo escolhido.\n");
        printf("Número de gerações: %d\n", jogo->num_geracoes);
        printf("Número de threads: %d\n", NUM_THREADS);
        
        simular_jogo_paralelo(jogo, NUM_THREADS);
        
        salvar_resultado(jogo);
        destruir_jogo(jogo);

    } else {
        printf("Modo inválido! Use 'seq' para sequencial ou 'par' para paralelo.\n");
        return 1;
    }

    return 0;
}
