#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "include/Tabuleiro.h"


int main(int argc, char *argv[]) {
	
	if(argc != 2) {
		printf("ERRO: Você precisa passar o caminho do arquivo como parâmetro! \n");
		return 1;
	}
	
	char *caminho_arquivo = argv[1];
	
	printf("%s \n", caminho_arquivo);
	
	return 0;
}
