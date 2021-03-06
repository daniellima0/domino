#ifndef LISTA_DE_H
#define LISTA_DE_H
#include <stdio.h>
#include <stdlib.h>
#include "tp_item.h"

typedef struct tp_no_aux {
    struct tp_no_aux *ant;
    tp_item info;
    struct tp_no_aux *prox;
} tp_no;

typedef struct {
    tp_no *ini;
    tp_no *fim;
    int tamanho;
} tp_listad;

tp_listad *inicializa_listad() {
    tp_listad *lista = (tp_listad *)malloc(sizeof(tp_listad));
    lista->ini = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

int lista_vazia(tp_listad *lista) {
    if (lista->ini == NULL) return 1;
    return 0;
}

tp_no *aloca() {
    tp_no *pt;
    pt = (tp_no *)malloc(sizeof(tp_no));
    return pt;
}

//insere_listad_no_fim
int insere_listad_na_direita(tp_listad *lista, tp_item e) {
    tp_no *novo;
    novo = aloca();
    if (!novo) return 0;
    novo->info = e;
    if (lista_vazia(lista)) {
        novo->prox = NULL;
        novo->ant = NULL;
        lista->ini = lista->fim = novo;
    } else {
        novo->prox = NULL;
        novo->ant = lista->fim;
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    lista->tamanho++;
    return 1;
}

// Insere_listade_no_inicio
int insere_listad_na_esquerda(tp_listad *lista, tp_item e) {
    tp_no *novo;
    novo = aloca();
    if (!novo) return 0;
    novo->info = e;
    if (lista_vazia(lista)) {
        novo->prox = NULL;
        novo->ant = NULL;
        lista->ini = lista->fim = novo;
    } else {
        novo->prox = lista->ini;
        novo->ant = NULL;
        lista->ini->ant = novo;
        lista->ini = novo;
    }
    lista->tamanho++;
    return 1;
}

void imprime_listad(tp_listad *lista, int ordem) {
    tp_no *atu;

    if (lista_vazia(lista)) return;

    switch (ordem) {
        case 1:
            atu = lista->ini;
            while (atu != NULL) {
                printf("|%d|%d| ", atu->info.esquerda, atu->info.direita);
                atu = atu->prox;
            }
            break;
        case 2:
            atu = lista->fim;
            while (atu != NULL) {
                printf("|%d|%d| ", atu->info.esquerda, atu->info.direita);
                atu = atu->ant;
            }
            break;

        default:
            printf("codigo invalido");
    }
}

int remove_listad(tp_listad *lista, tp_item e) {
    tp_no *atu = lista->ini;

    while ((atu != NULL) && ((atu->info.esquerda != e.esquerda) || (atu->info.direita != e.direita))) {
        atu = atu->prox;
    }

    if (atu == NULL) return 0;

    if (lista->ini == lista->fim) {
        lista->ini = lista->fim = NULL;
    } else {
        if (lista->ini == atu) {
            lista->ini = atu->prox;
            atu->prox->ant = NULL;
        } else {
            if (lista->fim == atu) {
                lista->fim = atu->ant;
                atu->ant->prox = NULL;
            } else {
                atu->prox->ant = atu->ant;
                atu->ant->prox = atu->prox;
            }
        }
    }
    free(atu);
    return 1;
}

tp_no *busca_listad(tp_listad *lista, tp_item e) {
    tp_no *atu;
    atu = lista->ini;
    while ((atu != NULL) && ((atu->info.esquerda != e.esquerda) || (atu->info.direita != e.direita))) {
        atu = atu->prox;
    }
    return atu;
}

tp_listad *destroi_listad(tp_listad *lista) {
    tp_no *atu;
    atu = lista->ini;
    while (atu != NULL) {
        lista->ini = atu->prox;
        free(atu);
        atu = lista->ini;
    }
    free(lista);
    return NULL;
}

#endif