#include <stdio.h>
#include "jogo.h"

int main(void) {
    Pergunta *perguntas;
    int quantidadePerguntas;

    if(lerPerguntas("C:\\Code\\Jogo_do_Milhao\\perguntas.txt", &perguntas, &quantidadePerguntas) != 0) return 1;

    printf("TESTE 01 - Lendo as perguntas do arquivo: \n");
    for (int i = 0; i < quantidadePerguntas; ++i) {
        printf("Perguntas %d: %s\n", i + 1, perguntas[i].perguntas);
    }
}
