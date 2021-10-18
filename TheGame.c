#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "globais.h"
#include "int_pilha.h"

void menu(int *x){
    printf("Dois[2] ou Quatro[4] Jogadores?\nDigite zero[0] para sair.\n->");
    scanf("%d", x);
    while(1){
        if(*x==2 || *x==4 || *x==0) break;
        else{
            system("cls");
            printf("Tente novamente.\nDois[2] ou Quatro[4] Jogadores?\nDigite zero[0] para sair.\n->");
            scanf("%d", x);  
        }
    }
}

int main(){
    int i, j;
    int escolha;

    menu(&escolha);
    //printf("%d\n", escolha);
    if(escolha == 2){
        printf("Voce escolheu jogar com dois jogadores.\n");
    }
    if(escolha == 4){
        printf("Voce escolheu jogar com quatro jogadores.\n");
    }    
    if(escolha == 0){
        printf("Voce escolheu sair.\nTchau, ate a proxima!");
        return 0;
    }
    
    tp_peca pecas[28];
    int peca_atual = 0;
    for(i = 0; i <= 6; i++) {
        for(j = i; j <= 6; j++) {
            pecas[peca_atual].esquerda = i;
            pecas[peca_atual].direita = j;
            peca_atual++;
        }
    }

    for(i=0;i<28;i++){
        printf("|%d|", pecas[i].esquerda);
        printf("%d|", pecas[i].direita);        
    }

    tp_pilha monte;
    inicializa_pilha(&monte);
    for(i=0;i<28;i++){
        push(&monte, pecas[i]);
    }

    imprime_pilha(monte);

return 0;
}
