#include <stdio.h>
#include "jogo.h"

int main(void) {
    Pergunta *perguntas;
    int quantidadePerguntas;

    if(lerPerguntas("C:\\Code\\Jogo_do_Milhao\\perguntas.txt", &perguntas, &quantidadePerguntas) != 0) return 1;
    if(lerRespostas("C:\\Code\\Jogo_do_Milhao\\respostas.txt", perguntas) != 0) return 1;
    if(lerRespostasCertas("C:\\Code\\Jogo_do_Milhao\\respostaCerta", &perguntas, &quantidadePerguntas) != 0) return 1;

    printf("TESTE 01 - Lendo as perguntas do arquivo: \n");
    for (int i = 0; i < quantidadePerguntas; ++i) {
        printf("Perguntas %d: %s\n", i + 1, perguntas[i].perguntas);
    }

    printf("TESTE 02 - Lendo as respostas do arquivo: \n");
    for (int i = 0; i < quantidadePerguntas; ++i) {
        printf("Pergunta %d: \n", i + 1);
        for (int j = 0; j < 4; ++j) {
            printf(" %s", perguntas[i].respostas[j]);
        }
        printf("\n");
    }


    printf("\nTESTE 03 - Lendo as respostas certas: \n");
    for (int i = 0; i < quantidadePerguntas; ++i) {
        printf("\nResposta certa: %d", perguntas[i].respostaCertaIndex);
    }

//    printf("\nTESTE 04 - Lendo as respostas certas: \n");
//    for (int i = 0; i < quantidadePerguntas; ++i) {
//        int respostaUsuario = 2;
//        if(perguntas[i].respostaCertaIndex == respostaUsuario){
//            printf("Resposta certa!\n");
//        }
//        respostaUsuario = 3;
//
//        if(perguntas[i].respostaCertaIndex != respostaUsuario){
//            printf("Resposta errada!\n");
//        }
//    }
    
}
