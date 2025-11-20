#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "include/Tabuleiro.h"
#include "include/Arquivo.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("ERRO: Você precisa passar o caminho do arquivo como parâmetro!\n");
        return 1;
    }

    char *caminho_arquivo = argv[1];

    int num_geracoes;
    Tabuleiro *tab = ler_tabuleiro(caminho_arquivo, &num_geracoes);
    if (!tab) return 1;

    printf("Número de gerações: %d\n", num_geracoes);
    printf("Tabuleiro inicial:\n");
    imprimir_tabuleiro(tab);
    escrever_tabuleiro(tab, num_geracoes);

    desalocar_tabuleiro(tab);
    return 0;
}
