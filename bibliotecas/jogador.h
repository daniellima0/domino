#ifndef JOGADOR_H
#define JOGADOR_H
#include "pilha.h"

typedef struct {
    char nome[101];
    tp_pilha mao;
} tp_jogador;

#endif