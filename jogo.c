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

int lerRespostas(const char *arquivoRespostas, Pergunta *items){
    FILE *arquivo = fopen(arquivoRespostas, "r");

    if(!arquivo){
        printf("ERRO ao abrir o arquivo");
        return -1;
    }

    char linha[MAXIMO_DE_LINHAS];
    int index = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        trim(linha);
        char *token = strtok(strchr(linha, ' ') + 1, ",");
        int indexResposta = 0;

        while (token != NULL){
            trim(token);
            strcpy(items[index].respostas[indexResposta], token);
            token = strtok(NULL, ",");
            indexResposta ++;
        }
        index++;
    }

    fclose(arquivo);

    return 0;
}

int lerRespostasCertas(const char *respostaCerta, Pergunta **items, int *qtdPerguntas) {
    FILE *respostas = fopen(respostaCerta, "r");
    if (respostas == NULL) {
        printf("Erro ao abrir o arquivo de respostas certas.\n");
        return 1;
    }

    char linha[MAXIMO_DE_LINHAS];
    int perguntaAtual = 0;

    while (fgets(linha, sizeof(linha), respostas)) {
        trim(linha);
        if (strlen(linha) == 0) {
            continue; // Pula linhas em branco
        }

        int numPergunta, respCerta;
        if (sscanf(linha, "%d. %d", &numPergunta, &respCerta) == 2) {
            if (numPergunta > 0 && numPergunta <= *qtdPerguntas) {
                if (respCerta >= 1 && respCerta <= 4) {
                    (*items)[numPergunta - 1].respostaCertaIndex = respCerta - 1;
                } else {
                    printf("Resposta certa fora do intervalo (1-4) para a pergunta %d: %d\n", numPergunta, respCerta);
                }
            } else {
                printf("Número da pergunta fora do intervalo: %d\n", numPergunta);
            }
        } else {
            printf("Formato inválido na linha: %s\n", linha);
        }

        perguntaAtual++;
    }

    fclose(respostas);

    return 0;
}