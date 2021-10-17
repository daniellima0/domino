#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "globais.h"
#include "int_pilha.h"
#include "int_fila.h"

typedef struct{
    int esquerda;
    int direita;
}tp_peca;

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
    int i, j, num1, num2;
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

    //Criando as peças.
    tp_peca pecas[28];
    pecas[0].esquerda=0;pecas[0].direita=0;
    pecas[1].esquerda=0;pecas[1].direita=1;
    pecas[2].esquerda=1;pecas[2].direita=1;
    pecas[3].esquerda=0;pecas[3].direita=2;
    pecas[4].esquerda=1;pecas[4].direita=2;
    pecas[5].esquerda=2;pecas[5].direita=2;
    pecas[6].esquerda=0;pecas[6].direita=3;
    pecas[7].esquerda=1;pecas[7].direita=3;
    pecas[8].esquerda=2;pecas[8].direita=3;
    pecas[9].esquerda=3;pecas[9].direita=3;
    pecas[10].esquerda=0;pecas[10].direita=4;
    pecas[11].esquerda=1;pecas[11].direita=4;
    pecas[12].esquerda=2;pecas[12].direita=4;
    pecas[13].esquerda=3;pecas[13].direita=4;
    pecas[14].esquerda=4;pecas[14].direita=4;
    pecas[15].esquerda=0;pecas[15].direita=5;
    pecas[16].esquerda=1;pecas[16].direita=5;
    pecas[17].esquerda=2;pecas[17].direita=5;
    pecas[18].esquerda=3;pecas[18].direita=5;
    pecas[19].esquerda=4;pecas[19].direita=5;
    pecas[20].esquerda=5;pecas[20].direita=5;
    pecas[21].esquerda=0;pecas[21].direita=6;
    pecas[22].esquerda=1;pecas[22].direita=6;
    pecas[23].esquerda=2;pecas[23].direita=6;
    pecas[24].esquerda=3;pecas[24].direita=6;
    pecas[25].esquerda=4;pecas[25].direita=6;
    pecas[26].esquerda=5;pecas[26].direita=6;
    pecas[27].esquerda=6;pecas[27].direita=6;

    for(i=0;i<28;i++){
        printf("|%d|", pecas[i].esquerda);
        printf("%d|", pecas[i].direita);        
    }

/*    tp_pilha monte;
    inicializa_pilha(&monte);
    for(i=0;i<28;i++){
        push(&monte, pecas[i]);
    }*/

return 0;
}
