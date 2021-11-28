#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "./bibliotecas/globais.h"

void embaralhar(tp_pilha *monte) {
    tp_pilha p1, p2, p3, p4, p5;
    tp_item e;
    int num;

    inicializa_pilha(&p1);
    inicializa_pilha(&p2);
    inicializa_pilha(&p3);
    inicializa_pilha(&p4);
    inicializa_pilha(&p5);
    srand(time(NULL));

    while (!pilha_vazia(monte)) {
        pop(monte, &e);
        num = rand() % 5;
        if (num == 0) push(&p1, e);
        if (num == 1) push(&p2, e);
        if (num == 2) push(&p3, e);
        if (num == 3) push(&p4, e);
        if (num == 4) push(&p5, e);
    }

    while (!pilha_vazia(&p3)) {
        pop(&p3, &e);
        push(monte, e);
    }

    while (!pilha_vazia(&p2)) {
        pop(&p2, &e);
        push(monte, e);
    }
    while (!pilha_vazia(&p1)) {
        pop(&p1, &e);
        push(monte, e);
    }
    while (!pilha_vazia(&p4)) {
        pop(&p4, &e);
        push(monte, e);
    }
    while (!pilha_vazia(&p5)) {
        pop(&p5, &e);
        push(monte, e);
    }
}

// SHELL SORT
void ordenar_pecas(tp_pilha *p) {
    tp_item aux[altura_pilha(p)];
    tp_item e;
    int n = 0, i, j, k;
    
    while(!pilha_vazia(p)){
        pop(p, &e);
        aux[n++] = e;
    }
    
    for(i = n/2; i>=1; i/=2){
        for(j = i; j < n; j++){
            for(k = j-i; k>=0 && ((aux[k+i].esquerda + aux[k+i].direita) > (aux[k].esquerda + aux[k].direita)); k-=i){
                e = aux[k+i];
                aux[k+i] = aux[k];
                aux[k] = e; 
            }
        }
    }

    for(i=0; i<n; i++){
        push(p, aux[i]);
    }
}

int is_string(char *string) {
    int string_len = strlen(string);
    int i;
    for (i = 0; i < string_len; ++i) {
        if (isdigit(string[i]))
            return 0;
    }

    return 1;
}

int ver_se_tem_como_jogar(tp_pilha p);

int checar_fim_do_jogo(tp_pilha *mao1, tp_pilha *mao2) {
    
    if((!ver_se_tem_como_jogar(*mao1) && lista_vazia(&monte)) || (!ver_se_tem_como_jogar(*mao2) && lista_vazia(&monte))){
        printf("Acabou, sem ganhadores.\nFechou o jogo");
        return 0;
    }

    int jog1 = 0, jog2 = 0; //Indicar quem ganhou

    if (pilha_vazia(mao1)) {
        jog1 = 1;
        printf("\t%s ganhou o jogo!", jogador1.nome);
    }

    if (pilha_vazia(mao2)) {
        jog2 = 1;
        printf("\t%s ganhou o jogo!", jogador2.nome);
    }

    if (jog1 || jog2)
        return 0;
    else
        return 1;
}

int validar_peca(tp_listad *mesa, tp_item peca) {
    if (lista_vazia(mesa)) return 1;

    tp_item ponta_esquerda = mesa->ini->info;
    tp_item ponta_direita = mesa->fim->info;

    if (ponta_esquerda.esquerda == peca.esquerda || ponta_esquerda.esquerda == peca.direita || ponta_direita.direita == peca.esquerda || ponta_direita.direita == peca.direita) {
        return 1;
    }

    return 0;
}

void inverte_posi(tp_item *peca){
    int temp = peca->esquerda;
    peca->esquerda = peca->direita;
    peca->direita = temp;
}

int destino(tp_item peca){
    
    if (lista_vazia(mesa)) {
        insere_listad_na_esquerda(mesa, peca);  
        return 1;
    }

    int ME = mesa->ini->info.esquerda;  // MESA ESQUERDA
    int MD = mesa->fim->info.direita;   // MESA DIREITA
    int PE = peca.esquerda;
    int PD = peca.direita;
    char destino;

    //1º CASO
    if ((PE == ME && PD == MD) || (PD == ME && PE == MD) || (PE == MD && PE == ME) || (PD == MD && PD == ME)) {

        while (1) {
            printf("Digite o destino da peca [ESQUERDA [E] OU DIREITA [D] DO TABULEIRO]: ");
            scanf(" %c", &destino);
            printf("\n");

            if (destino == 'E' || destino == 'D' || destino == 'e' || destino == 'd') break;

            printf("Tente novamente.\n");            
        }

        if(destino == 'E' || destino == 'e'){
            if(PE == ME){
                inverte_posi(&peca);
                insere_listad_na_esquerda(mesa, peca);
                return 0; 
            }else{
                insere_listad_na_esquerda(mesa, peca);
                return 0; 
            }
        }

        if(destino == 'D' || destino == 'd'){
            if(PD == MD){
                inverte_posi(&peca);
                insere_listad_na_direita(mesa, peca);
                return 0; 
            }else{
                insere_listad_na_direita(mesa, peca);
                return 0; 
            }
        }

    }

    //2º CASO
    if ((PE == ME || PE == MD) || (PD == ME || PD == MD)) {
        if(PE == ME){
            inverte_posi(&peca);
            insere_listad_na_esquerda(mesa, peca);
            return 0; 
        }
        if(PE == MD){
            insere_listad_na_direita(mesa, peca);
            return 0; 
        }
        if(PD == MD){
            inverte_posi(&peca);
            insere_listad_na_direita(mesa, peca);
            return 0; 
        }
        if(PD == ME){
            insere_listad_na_esquerda(mesa, peca);
            return 0; 
        }
    }
    return 0;
}

void cave (tp_jogador *jog){
    tp_item e;
    pop(&monte, &e);
    push(&jog->mao, e);
    ordenar_pecas(&jog->mao);
}

int ver_se_tem_como_jogar(tp_pilha p){

    if(lista_vazia(mesa)) return 0;

    int ME = mesa->ini->info.esquerda;
    int MD = mesa->fim->info.direita;
    
    tp_item aux[altura_pilha(&p)];
    tp_item e;
    int n = 0, i;
    
    while(!pilha_vazia(&p)){
        
        pop(&p, &e);
        aux[n++] = e;
    }
    for(i = 0; i<n; i++){
        if(aux[i].esquerda == ME || aux[i].esquerda == MD || aux[i].direita == ME || aux[i].direita == MD)  return 1;
    }return 0;
}

tp_item verificar(tp_jogador *jog) {
    tp_pilha paux;
    inicializa_pilha(&paux);
    tp_item peca_escolhida, e;
    int posicao;
    
    while(1){
        
        if(!lista_vazia(mesa) && !lista_vazia(&monte) &&!ver_se_tem_como_jogar(jog->mao)){
            do{
                printf("Cave!\n");
                system("pause");
                cave(jog);
                imprime_pilha(jog->mao);
            }while(!lista_vazia(mesa) && !lista_vazia(&monte) && !ver_se_tem_como_jogar(jog->mao));
        }

        int altura = altura_pilha(&jog->mao);
        
        while (1) {

            printf("\nDigite a posicao da peca: ");
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
            printf("Opcao invalida. Nao eh permitido gato.\n");
            push(&jog->mao, peca_escolhida);
            while (!pilha_vazia(&paux)) {
            pop(&paux, &e);
            push(&jog->mao, e);
            }
        }
    }  
    return peca_escolhida;
}


int main() {
    // regras(); Função pendente

    do {
        printf("\nDigite o nome do primeiro jogador: ");
        scanf(" %[^\n]s", jogador1.nome);

        while ((!is_string(jogador1.nome))) {
            system("cls");
            printf("Utilize apenas caracteres. Tente novamente. ");
            printf("\nDigite o nome do primeiro jogador: ");
            scanf(" %[^\n]s", jogador1.nome);
        }

        printf("\nDigite o nome do segundo jogador: ");
        scanf(" %[^\n]s", jogador2.nome);

        while ((!is_string(jogador2.nome))) {
            system("cls");
            printf("Utilize apenas caracteres. Tente novamente. ");
            printf("\nDigite o nome do segundo jogador: ");
            scanf(" %[^\n]s", jogador2.nome);
        }

        if (!strcmp(jogador1.nome, jogador2.nome)) {
            system("cls");
            printf("Utilize nomes diferentes. Tente novamente.\n");
        }

    } while (!strcmp(jogador1.nome, jogador2.nome));

    //Criando peças
    for (i = 0; i <= 6; i++) {
        for (j = i; j <= 6; j++) {
            pecas[peca_atual].esquerda = i;
            pecas[peca_atual].direita = j;
            peca_atual++;
        }
    }

    inicializa_pilha(&monte);

    //Populando monte com as peças
    for (i = 0; i < 28; i++) {
        push(&monte, pecas[i]);
    }

    // Embaralhando o monte
    embaralhar(&monte);

    // Distribuindo as peças para cada jogador

    inicializa_pilha(&jogador1.mao);
    inicializa_pilha(&jogador2.mao);

    for (i = 0; i < 7; i++) {
        pop(&monte, &e);
        push(&jogador1.mao, e);
    }

    for (i = 0; i < 7; i++) {
        pop(&monte, &e);
        push(&jogador2.mao, e);
    }

    ordenar_pecas(&jogador1.mao);
    ordenar_pecas(&jogador2.mao);

    int rodada = 0;

    mesa = inicializa_listad();
    
    while (checar_fim_do_jogo(&jogador1.mao, &jogador2.mao)) {
        system("cls");
        
        printf("\n");
        imprime_listad(mesa, 1);
        printf("\n\n");

        if (rodada % 2 == 0) {
            printf("Vez do jogador %s\n", jogador1.nome);
            
            imprime_pilha(jogador1.mao);
            
            tp_item peca_valida = verificar(&jogador1);
            
            destino(peca_valida);
        }

        else if (rodada % 2 != 0) {
            printf("Vez do jogador %s\n", jogador2.nome);
            imprime_pilha(jogador2.mao);

            tp_item peca_valida = verificar(&jogador2);
            
            destino(peca_valida);

        }
    rodada++;
    }
return 0;
}
