#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "int_pilha.h"
#include "int_fila.h"

char nome_jogador1[21];
char nome_jogador2[21];

typedef struct{
    int esquerda;
    int direita;
}tp_peca;

int main(){
    int i, num1, num2;

    //Criando as peças.
    tp_peca pecas[28];
    for(i=0;i<28;i++){
        pecas[i].esquerda = 0;
        pecas[i].direita = 0;
    }

    srand(time(NULL));
    for(i=0;i<28;i++){
        num1 = rand() % 6;
        num2 = rand() % 6;
        pecas[i].esquerda = num1;
        pecas[i].direita = num2;
    }
    
    for(i=0;i<28;i++){
        printf("|%d|",pecas[i].esquerda );
        printf("%d|", pecas[i].direita);        
    }
    printf("\n");

return 0;
}

/*
    //Para dois jogadores
    printf("Nome do Jogador 1: ");
    scanf(" %[\n]s", nome_jogador1);
    printf("Nome do Jogador 2: ");
    scanf(" %[\n]s", nome_jogador2);
*/