#ifndef PILHA_H
#define PILHA_H
#define MAX 100
#include <stdio.h>
#include "tp_item.h"

typedef struct {
    int topo;  // inicialmente topo = -1
    tp_item item[MAX];
} tp_pilha;

void inicializa_pilha(tp_pilha *p) {
    p->topo = -1;
}

int pilha_vazia(tp_pilha *p) {    // Pilha vc está vazia?
    if (p->topo == -1) return 1;  // Sim, estou!
    return 0;                     // Não estou.
}

int pilha_cheia(tp_pilha *p) {         // Pilha vc está cheia?
    if (p->topo == MAX - 1) return 1;  // Sim, estou :/
    return 0;                          // Não estou :)
}

int push(tp_pilha *p, tp_item e) {  // push = EMPILHAR
    if (pilha_cheia(p)) return 0;   // verificar se esta cheia
    p->topo++;                      // incrementa 1 ao topo
    p->item[p->topo] = e;           // colocar o "e" no topo da pilha
    return 1;
}

int pop(tp_pilha *p, tp_item *e) {  // pop = DESEMPILHAR; retorna para a main o "e".
    if (pilha_vazia(p)) return 0;   // Verifica se esta cheia
    *e = p->item[p->topo];          // Coloca em "e" o item no topo
    p->topo--;                      // Decresce 1 do valor do topo
    return 1;
}

tp_item verificar(tp_jogador *jog) {
    tp_pilha paux;
    inicializa_pilha(&paux);
    tp_item peca_escolhida, e;
    int posicao;
    int altura = altura_pilha(&jog->mao);
    while(1){
        
        while (1) {
            printf("Digite a posicao da peca: ");
            scanf("%d", &posicao);
            printf("\n");

            if (posicao > 0 && posicao <= altura) {
                break;
            }

            printf("Tente novamente.\n");
        }
        
        while (posicao - 1) { 
            pop(&jog->mao , &e);
            push(&paux, e);
            posicao--;
        }
        
        pop(&jog->mao, &peca_escolhida);
        if(validar_peca(mesa, peca_escolhida)){
            while (!pilha_vazia(&paux)) { 
            pop(&paux, &e);
            push(&jog->mao, e);
            }
        return peca_escolhida;
        }
        else{
            printf("Opcao invalida. Nao é permitido gato.\n");
            push(&jog->mao, peca_escolhida);
            while (!pilha_vazia(&paux)) {
            pop(&paux, &e);
            push(&jog->mao, e);
            }
        }
    }  
    return peca_escolhida;
}

tp_item retirar_peca(tp_pilha *p, int posicao) {
    tp_pilha paux;
    inicializa_pilha(&paux);
    tp_item peca_escolhida;
    tp_item e;
    
    while (posicao - 1) {  // TIRAR O Q TA EM CIMA
        pop(p, &e);
        push(&paux, e);
        posicao--;
    }
    
    pop(p, &peca_escolhida);

    while (!pilha_vazia(&paux)) {  // DEVOLVE O Q TAVA EM CIMA
        pop(&paux, &e);
        push(p, e);
    }
    
    return peca_escolhida;  // RETORNA PECA ESCOLIDA
}

int top(tp_pilha *p, tp_item *e) {  // top: mostra quem ta no topo sem desempilhar
    if (pilha_vazia(p)) return 0;
    *e = p->item[p->topo];
    return 1;
}

void imprime_pilha(tp_pilha p) {
    tp_item e;
    printf("\n");
    while (!pilha_vazia(&p)) {
        pop(&p, &e);
        printf("|%d|%d| ", e.esquerda, e.direita);
    }
    printf("\n");
}

int altura_pilha(tp_pilha *p) {
    return p->topo + 1;
}

#endif

/*
Implementar uma função que receba uma pilha
como parâmetro e retire todos os
elementos ímpares dessa pilha.

int retira_impares(tp_pilha *p){
    if (pilha_vazia(p)) return 0;
    tp_pilha paux;
    inicializa_pilha(&paux);
    tp_item e;
    while (!pilha_vazia(p)){
        pop(p, &e);
        if (e % 2 == 0)
            push(&paux, e);
    }
    while(!pilha_vazia(&paux)){
        pop(&paux, &e);
        push(p, e);
    }
    return 1;
}


Implementar uma função que receba duas pilhas
como parâmetro e retorna 1 caso sejam
idênticas ou zero caso contrário.

int pilhas_iguais (tp_pilha p1, tp_pilha p2){
    if (altura_pilha(&p1) != altura_pilha(&p2)) return 0;
    tp_item e1, e2;
    while (!pilha_vazia(&p1)){
        pop(&p1, &e1);
        pop(&p2, &e2);
        if (e1 != e2) return 0;
    }
    return 1;
}

void empilhar(tp_pilha *p1, tp_pilha *p2){
    tp_pilha paux;
    inicializa_pilha(&paux);
    tp_item e;
    while(!pilha_vazia(p2)){
        pop(p2, &e);
        push(&paux, e);
    }
    while (!pilha_vazia(&paux)){
        pop(&paux, &e);
        push(p1, e);
    }
}
*/