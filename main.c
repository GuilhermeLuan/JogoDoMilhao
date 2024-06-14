#include <stdio.h>
#include "jogo.h"

int main(void) {
    Pergunta *perguntas;
    int quantidadePerguntas;

    if(lerPerguntas("perguntas.txt", &perguntas, &quantidadePerguntas) != 0) return 1;
    if(lerRespostas("respostas.txt", perguntas) != 0) return 1;
    if(lerRespostasCertas("respostaCerta.txt", &perguntas, &quantidadePerguntas) != 0) return 1;

    for (int i = 0; i < quantidadePerguntas; i++){
        printf("Pergunta %d: %s\n", i + 1, perguntas[i].perguntas);
        for (int j = 0; j < 4; j++)
        {
                printf("\n%d - %s ",j+1 ,perguntas[i].respostas[j]);
        }
        int respostaUsuario;

        do{
            printf("\nQual a sua resposta: ");
            scanf("%d", &respostaUsuario);
            fflush(stdin);


            while(respostaUsuario > 4 || respostaUsuario < 1){
                printf("Resposta invalida!");
                printf("\nQual a sua resposta: ");
                scanf("%d", &respostaUsuario);
                fflush(stdin);

            }

        } while(respostaUsuario > 4 || respostaUsuario < 1);

        respostaUsuario--;


        if(respostaUsuario == perguntas[i].respostaCertaIndex){
            printf("Resposta certa!\n");
        }
        else{
            printf("Resposta errada!\n");
            return -1;
        }
    }
}
