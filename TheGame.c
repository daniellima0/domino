#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "int_pilha.h"
#include "int_fila.h"

char nome_jogador1[21];
char nome_jogador2[21];
char nome_jogador3[21];
char nome_jogador4[21];

typedef struct{
    int esquerda;
    int direita;
}tp_peca;

void menu(int *x){
    int n=1;
    printf("Dois[2] ou Quatro[4] Jogadores?\nDigite zero[0] para sair.\n->");
    scanf("%d", x);
    while(n){
        if(*x==2 || *x==4 || *x==0) break;
        else{
            printf("Tente novamente.\nDois[2] ou Quatro[4] Jogadores?\nDigite zero[0] para sair.\n->");
            scanf("%d", x);  
        }
    }
}

int main(){
    int i, num1, num2;
    int escolha;

    menu(&escolha);
    printf("%d\n", escolha);
    if(escolha == 2){
        printf("Dois jogadores.\n");
    }
    if(escolha == 4){
        printf("Quatro jogadores.\n");
    }    
    if(escolha == 0){
        printf("Vazante.\n");
    }    

    //Criando as peças.
    tp_peca pecas[28];
    for(i=0;i<28;i++){
        pecas[i].esquerda = 0;
        pecas[i].direita = 0;
    }

    //Ainda falta criar corretamente todas as pecas
    srand(time(NULL));
    for(i=0;i<28;i++){
        num1 = rand() % 6;
        num2 = rand() % 6;
        pecas[i].esquerda = num1;
        pecas[i].direita = num2;
    }
    for(i=0;i<28;i++){
        printf("|%d|", pecas[i].esquerda);
        printf("%d|", pecas[i].direita);        
    }
/*
    Criando o cava
    Não ta rolando... tp_peca ainda não é compativel com a pilha

    tp_pilha monte;
    inicializa_pilha(&monte);
    for(i=0;i<28;i++){
        push(&monte, pecas[i]);
    }
*/

return 0;
}
