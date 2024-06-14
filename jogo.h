#ifndef JOGO_H
#define JOGO_H

#define MAXIMO_DE_LINHAS 256

typedef struct {
    char perguntas[MAXIMO_DE_LINHAS];
    char respostas[4][MAXIMO_DE_LINHAS];
    int respostaCertaIndex;
} Pergunta;

int lerPerguntas(const char *arquivoPergunta, Pergunta **items, int *qtdPerguntas);
int lerRespostas(const char *arquivoRespostas, Pergunta *items);
int lerRespostasCertas(const char *respostaCerta, Pergunta **items, int *qtdPerguntas);
void trim(char *str);

#endif