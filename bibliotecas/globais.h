#ifndef GLOBAIS_H
#define GLOBAIS_H
#include "tp_item.h"
#include "pilha.h"
#include "lista_de.h"
#include "jogador.h"

char nome_jogador1[21];
char nome_jogador2[21];
char nome_jogador3[21];
char nome_jogador4[21];

int i, j, escolha = 0;

tp_item pecas[29], e;
int peca_atual = 0;

tp_pilha monte;

tp_listad *lista;

tp_jogador jogador1;
tp_jogador jogador2;
tp_jogador jogador3;
tp_jogador jogador4;

#endif