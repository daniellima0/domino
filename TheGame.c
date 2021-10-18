#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "globais.h"
#include "pilha.h"

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

void embaralhar(tp_peca *monte){
    tp_pilha p1, p2, p3, p4, p5;
    tp_peca e;
    int num;
    inicializa_pilha(&p1);inicializa_pilha(&p2);inicializa_pilha(&p3);inicializa_pilha(&p4);inicializa_pilha(&p5);
    srand(time(NULL));
    while(!pilha_vazia(monte)){
        pop(monte, &e);
        num = rand() % 5;
        if(num==0) push (&p1, e);if(num==1) push (&p2, e);if(num==2) push (&p3, e);
        if(num==3) push (&p4, e);if(num==4) push (&p5, e);
    }
    while(!pilha_vazia(&p3)) {pop(&p3, &e); push(monte, e);}
    while(!pilha_vazia(&p2)) {pop(&p2, &e); push(monte, e);}
    while(!pilha_vazia(&p1)) {pop(&p1, &e); push(monte, e);}
    while(!pilha_vazia(&p4)) {pop(&p4, &e); push(monte, e);}
    while(!pilha_vazia(&p5)) {pop(&p5, &e); push(monte, e);}
}

int main(){
    system("cls");
    int i, j;
    int escolha;

    //regras(); Função pendente

    //Escolha do modo de jogo
    menu(&escolha);
    if(escolha == 2){
        printf("Voce escolheu jogar com dois jogadores.\n");
        printf("\nDigite o nome do primeiro jogador: "); scanf(" %[^\n]s", &nome_jogador1);
        printf("Digite o nome do segundo jogador: "); scanf(" %[^\n]s", &nome_jogador2);
    }
    if(escolha == 4){
        printf("Voce escolheu jogar com quatro jogadores.\n");
        printf("\nDigite o nome do primeiro jogador: "); scanf(" %[^\n]s", &nome_jogador1);
        printf("Digite o nome do segundo jogador: "); scanf(" %[^\n]s", &nome_jogador2);
        printf("Digite o nome do terceiro jogador: "); scanf(" %[^\n]s", &nome_jogador3);
        printf("Digite o nome do quarto jogador: "); scanf(" %[^\n]s", &nome_jogador4);
    }    
    if(escolha == 0){
        printf("Voce escolheu sair.\nTchau, ate a proxima!");
        return 0;
    }
    
    //Criando as pecas
    tp_peca pecas[28];
    int peca_atual = 0;
    for(i = 0; i <= 6; i++) {
        for(j = i; j <= 6; j++) {
            pecas[peca_atual].esquerda = i;
            pecas[peca_atual].direita = j;
            peca_atual++;
        }
    }

    //Empilhando as pecas
    tp_pilha monte;
    inicializa_pilha(&monte);
    for(i=0;i<28;i++){
        push(&monte, pecas[i]);
    }
	
//    imprime_pilha(monte);
//    printf("\n");

    //Embaralha o monte
    embaralhar(&monte);
    imprime_pilha(monte);

    //Distribuindo as pecas para cada jogador
    //talvez o jogo ocorra todo dentro desses dois ifs.
    tp_peca e;
    if(escolha==2){
        tp_pilha mao_j1, mao_j2;
        inicializa_pilha(&mao_j1); inicializa_pilha(&mao_j2); 
        for(i=0;i<7;i++) {pop(&monte, &e); push(&mao_j1, e);}
        for(i=0;i<7;i++) {pop(&monte, &e); push(&mao_j2, e);}
    
        //Criar função para ordenar pelo somatório dos números das peças.
        //ordenar_pecas();

    }
    else{
        if(escolha == 4){
        tp_pilha mao_j1, mao_j2, mao_j3, mao_j4;
        inicializa_pilha(&mao_j1); inicializa_pilha(&mao_j2);
        inicializa_pilha(&mao_j3); inicializa_pilha(&mao_j4); 
        for(i=0;i<7;i++) {pop(&monte, &e); push(&mao_j1, e);}
        for(i=0;i<7;i++) {pop(&monte, &e); push(&mao_j2, e);}
        for(i=0;i<7;i++) {pop(&monte, &e); push(&mao_j3, e);}
        for(i=0;i<7;i++) {pop(&monte, &e); push(&mao_j4, e);} 

        //Criar função para ordenar pelo somatório dos números das peças.
        //ordenar_pecas();  

        }
    }

    

return 0;
}
