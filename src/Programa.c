#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/Jogo_Vida_Conway.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("ERRO: Você precisa passar o caminho do arquivo como parâmetro!\n");
        return 1;
    }

    char *caminho = argv[1];

    Jogo *jogo = criar_jogo(caminho);
    if (!jogo) {
        printf("Falha ao inicializar o jogo!\n");
        return 1;
    }

    printf("Número de gerações: %d\n", jogo->num_geracoes);
    printf("Tabuleiro inicial:\n");
    imprimir_tabuleiro(jogo->tabuleiro);

    simular_jogo(jogo);

    printf("\nTabuleiro final:\n");
    imprimir_tabuleiro(jogo->tabuleiro);

    salvar_resultado(jogo);

    destruir_jogo(jogo);

    return 0;
}
