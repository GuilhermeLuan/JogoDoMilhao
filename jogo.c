#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"

void trim(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int lerPerguntas(const char *arquivoPergunta, Pergunta **items ,int *qtdPerguntas){
    FILE *arquivo = fopen(arquivoPergunta, "r");

    if(!arquivo){
        printf("ERRO ao abrir o arquivo");
        return -1;
    }

    char linha[MAXIMO_DE_LINHAS];
    int index = 0;
    *qtdPerguntas = 0;

    while (fgets(linha, sizeof(linha), arquivo)){
        (*qtdPerguntas)++;
    }

    rewind(arquivo);
    *items = (Pergunta *)malloc(*qtdPerguntas * sizeof(Pergunta));

    while (fgets(linha, sizeof(linha), arquivo)) {
        trim(linha);
        strcpy((*items)[index].perguntas, strchr(linha, ' ') + 1);
        index++;
    }


    fclose(arquivo);

    return 0;
}