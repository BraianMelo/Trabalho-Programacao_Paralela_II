#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/Tabuleiro.h"

Tabuleiro* ler_tabuleiro(const char *caminho, int *num_geracoes) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return NULL;
    }

    int linhas, colunas, num_celulas;

    if (fscanf(arquivo, "%d", num_geracoes) != 1) {
        printf("Erro ao ler o número de gerações.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d %d", &linhas, &colunas) != 2) {
        printf("Erro ao ler linhas e colunas.\n");
        fclose(arquivo);
        return NULL;
    }

    Tabuleiro *t = criar_tabuleiro(linhas, colunas);
    if (!t) {
        printf("Erro ao criar o tabuleiro.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &num_celulas) != 1) {
        printf("Erro ao ler número de células vivas.\n");
        desalocar_tabuleiro(t);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < num_celulas; i++) {
        int x, y;
        if (fscanf(arquivo, "%d %d", &x, &y) != 2) {
            printf("Erro ao ler coordenadas da célula %d.\n", i);
            desalocar_tabuleiro(t);
            fclose(arquivo);
            return NULL;
        }
        
        
        
        mudar_celula(t, x, y, true);
    }

    fclose(arquivo);
    return t;
}
