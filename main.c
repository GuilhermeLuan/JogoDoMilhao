#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include "jogo.h"

int numThreads = 1;
void *extraChance();
sem_t semaf;   
int chance = 1;

int main(void) {

    int premios[] = {
        1000,
        2000,
        3000,
        4000,
        5000,
        10000,
        20000,
        30000,
        40000,
        50000,
        100000,
        200000,
        300000,
        400000,
        500000
    };

    pthread_t threads[numThreads];
    Pergunta *perguntas;
    int quantidadePerguntas;

    if(lerPerguntas("perguntas.txt", &perguntas, &quantidadePerguntas) != 0) return 1;
    if(lerRespostas("respostas.txt", perguntas) != 0) return 1;
    if(lerRespostasCertas("respostaCerta.txt", &perguntas, &quantidadePerguntas) != 0) return 1;

    for (int i = 0; i < quantidadePerguntas; i++){
        
        if (chance > 0) {
            chance--;
        }

        printf("Pergunta %d: %s\n", i + 1, perguntas[i].perguntas);
        for (int j = 0; j < 4; j++)
        {
                printf("\n%d - %s ",j+1 ,perguntas[i].respostas[j]);
        }
        int respostaUsuario;

        clock_t start = clock();
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
        clock_t end = clock();
        double ts = (double)(end - start) / CLOCKS_PER_SEC;
        
    if (ts > 17.37 && ts < 17.73) {
            sem_init(&semaf, 0, 1);
            // iniciar as threads
    for (int i = 0; i < numThreads; i++) {
        if (pthread_create(&threads[i], NULL, extraChance, NULL) != 0) {
            perror("pthread_create");
            printf("\nerro ao criar as threads\n");
            exit(1);
        }
    }

    // encerrar as threads
    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            printf("\nerro ao encerrar as threads\n");
            exit(1);
        }
    }
    sem_destroy(&semaf);
        }
        
        respostaUsuario--;


        if(respostaUsuario == perguntas[i].respostaCertaIndex){
            printf("Resposta certa!\n");
        }
        else{
            if (chance <= 0) {
                printf("Resposta errada!\n");
                return -1;
            }
            else {
                printf("Resposta errada!\n");
            }
        }

        if(i == 15){
            printf("Voce ganhou a premiacao de 1 milhao de reais!");
            return -1;
        }

        printf("Voce deseja desistir e levar uma premiacao de  %d ?\n1 - SIM\n2 - NAO\n", premios[i]);
        int opcao;

        do{
            printf("Qual a sua opcao: ");
            scanf("%d", &opcao);
            fflush(stdin);


            while(opcao > 2 || opcao < 1){
                printf("Resposta invalida!");
                printf("\nQual a sua opcao: ");
                scanf("%d", &opcao);
                fflush(stdin);

            }

        } while(opcao > 2 || opcao < 1);

        if(opcao == 1){
            printf("Voce acaba de levar uma premiacao de %d para casa!", premios[i]);
            exit(1);
        }

    }
}

void *extraChance() {

    sem_init(&semaf, 0, 1);
    sem_wait(&semaf); 
    printf("\n\nVocê ganhou uma chance extra! Continue jogando!\n\n");
    chance++;
    sem_post(&semaf);

}