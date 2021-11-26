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

// transfere todos os items de uma pilha à outra no mesmo sentido (1) ou no sentido inverso (2)
void transferir_entre_pilhas(tp_pilha *pilha_emissora, tp_pilha *pilha_receptora, int tipo) {
    if (pilha_vazia(pilha_emissora) || pilha_cheia(pilha_receptora)) return;

    tp_item e;
    tp_pilha pilha_auxiliar;
    inicializa_pilha(&pilha_auxiliar);

    if (tipo == 1) {
        while (!pilha_vazia(pilha_emissora)) {
            pop(pilha_emissora, &e);
            push(&pilha_auxiliar, e);
        }
        while (!pilha_vazia(&pilha_auxiliar)) {
            pop(&pilha_auxiliar, &e);
            push(pilha_receptora, e);
        }
    } else if (tipo == 2) {
        while (!pilha_vazia(pilha_emissora)) {
            pop(pilha_emissora, &e);
            push(pilha_receptora, e);
        }
    }
}

// ordenas peças de uma pilha de acordo com o somatório individual de forma crescente
void ordenar_pecas(tp_pilha *pilha_original) {
    int referencia, somatorio, contador = 0;
    tp_item e1, e2;
    tp_pilha pilha_ordenada, pilha_auxiliar;

    inicializa_pilha(&pilha_ordenada);
    inicializa_pilha(&pilha_auxiliar);

    tp_pilha *pilha_emissora, *pilha_receptora;

    while (altura_pilha(&pilha_ordenada) < 7) {
        // A cada loop, os ponteiros pilha_emissora e pilha_receptora alternarão entre pilha original e auxiliar
        if (contador % 2 == 0) {
            pilha_emissora = pilha_original;
            pilha_receptora = &pilha_auxiliar;
        } else if (contador % 2 != 0) {
            pilha_emissora = &pilha_auxiliar;
            pilha_receptora = pilha_original;
        }

        referencia = 0;
        somatorio = 0;

        // o loop só acabará quando a pilha emissora estiver vazia
        while (!pilha_vazia(pilha_emissora)) {
            pop(pilha_emissora, &e1);
            somatorio = e1.esquerda + e1.direita;

            // Aqui existem 4 casos
            // Caso 1: a peça removida da pilha emissora vai direto para a pilha ordenada, pois esta última está vazia
            if (somatorio > referencia && pilha_vazia(&pilha_ordenada)) {
                push(&pilha_ordenada, e1);
                referencia = somatorio;

                // Caso 2: a peça removida da pilha emissora tem um somatório maior que o somatório da última peça colocada na pilha ordenada (este segundo somatório entende-se como o valor armazenado na variável referência), então a(s) peça(s) com valor de somatório igual ao da variável referência é(são) removida(s) da pilha ordenada e armazenada(s) na pilha receptora e a peca removida da pilha emissora vai para a pilha ordenada
            } else if (somatorio > referencia && !pilha_vazia(&pilha_ordenada)) {
                while (1 && !pilha_vazia(&pilha_ordenada)) {
                    pop(&pilha_ordenada, &e2);

                    if (referencia != (e2.esquerda + e2.direita)) {
                        push(&pilha_ordenada, e2);
                        break;
                    }

                    push(pilha_receptora, e2);
                }
                push(&pilha_ordenada, e1);
                referencia = somatorio;
                // Caso 3: a peça removida da pilha emissora tem um somatório igual ao somatório da última peça colocada na pilha ordenada, logo vai direto para a pilha ordenada
            } else if (somatorio == referencia) {
                push(&pilha_ordenada, e1);

                // Caso 4: a peça removida da pilha emissora tem um somatório menor ao somatório da última peça colocada na pilha ordenada, logo vai direto para a pilha receptora
            } else if (somatorio < referencia) {
                push(pilha_receptora, e1);
            }
        }

        contador++;
    }

    // ao longo do looping, todas as peças se depositaram na pilha ordenada, logo elas tem que voltar para a pilha original
    transferir_entre_pilhas(&pilha_ordenada, pilha_original, 1);
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

int checar_fim_do_jogo(tp_pilha *mao1, tp_pilha *mao2) {  //adicionar checagem para finalizar o jogo quando não houver mais peça para jogar
    int jog1 = 0, jog2 = 0;                               //Indicar quem ganhou

    if (pilha_vazia(mao1)) {
        jog1 = 1;
        printf("O %s ganhou o jogo!", jogador1.nome);
    }

    if (pilha_vazia(mao2)) {
        jog2 = 1;
        printf("O %s ganhou o jogo!", jogador2.nome);
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

int validar_destino(tp_listad *mesa, tp_item peca) {
    if (lista_vazia(mesa)) return 1;

    int ME = mesa->ini->info.esquerda;  // MESA ESQUERDA
    int MD = mesa->fim->info.direita;   // MESA DIREITA
    int PE = peca.esquerda;
    int PD = peca.direita;

    //1º CASO
    if ((PE == ME || PE == MD) && (PD == ME || PD == MD)) {
        printf("Digite o destino da peca [ESQUERDA [E] OU DIREITA [D] DO TABULEIRO]: ");
        scanf(" %c", &destino);
        printf("\n");

        while (1) {
            if (destino == 'E' || destino == 'D') {
                if (validar_destino(mesa, peca, 'E')) {
                    break;
                } else {
                    printf("Tente novamente.\nDigite o destino da peca [ESQUERDA [E] OU DIREITA [D] DO TABULEIRO]: ");
                    scanf(" %c", &destino);
                    printf("\n");
                }

                system("pause");
                // imprime_tabuleiro();
            }
        }
    }
    return 0;
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
    // talvez o jogo ocorra todo dentro desses dois ifs.

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

    int contador_temp = 0;  //variável temporária
    int posicao = 0;
    char destino;

    mesa = inicializa_listad();

    //populando mesa para testar
    tp_item peca_teste1;
    peca_teste1.esquerda = 6;
    peca_teste1.direita = 6;

    tp_item peca_teste2;
    peca_teste2.esquerda = 6;
    peca_teste2.direita = 2;

    tp_item peca_teste3;
    peca_teste3.esquerda = 1;
    peca_teste3.direita = 6;

    insere_listad_na_direita(mesa, peca_teste1);
    insere_listad_na_direita(mesa, peca_teste2);
    insere_listad_na_esquerda(mesa, peca_teste3);

    while (checar_fim_do_jogo(&jogador1.mao, &jogador2.mao)) {
        system("cls");

        // if (contador_temp > 0) imprime_listad(mesa, 1);

        imprime_listad(mesa, 1);
        printf("\n");

        if (contador_temp % 2 == 0) {
            printf("Vez do jogador %s\n", jogador1.nome);
            imprime_pilha(jogador1.mao);
            jogador1.num_pecas = altura_pilha(&jogador1.mao);

            //looping para obrigar o usuário a escolher uma posição existente
            while (1) {
                printf("Digite a posicao da peca: ");
                scanf("%d", &posicao);
                printf("\n");

                if (posicao > 0 && posicao <= jogador1.num_pecas) {
                    tp_item peca_retirada = verificar_peca(&jogador1.mao, posicao);
                    if (validar_peca(mesa, peca_retirada)) break;
                }

                printf("Tente novamente.\n");
            }
        }
    }
    else if (contador_temp % 2 != 0) {
        printf("Vez do jogador %s\n", jogador2.nome);
        imprime_pilha(jogador2.mao);
        jogador2.num_pecas = altura_pilha(&jogador2.mao);

        //looping para obrigar o usuário a escolher uma posição existente
        while (1) {
            printf("Digite a posicao da peca: ");
            scanf("%d", &posicao);
            printf("\n");

            if (posicao > 0 && posicao <= jogador2.num_pecas) {
                tp_item peca_retirada = verificar_peca(&jogador2.mao, posicao);
                if (validar_peca(mesa, peca_retirada)) break;
            }

            printf("Tente novamente.\n");
        }

        printf("Digite o destino da peca [ESQUERDA [E] OU DIREITA [D] DO TABULEIRO]: ");
        scanf(" %c", &destino);
        printf("\n");

        while (1) {
            if (destino == 'E' || destino == 'D')
                break;
            else {
                printf("Tentdestinoente.\nDigite o destino da peca [ESQUERDA [E] OU DIREITA [D] DO TABULEIRO]: ");
                scanf(" %c", &destino);
                printf("\n");
            }
        }

        system("pause");
        // imprime_tabuleiro();
    }
    /* tp_item ilv;
            pop(&jogador1.mao, &ilv);pop(&jogador1.mao, &ilv);pop(&jogador1.mao, &ilv); */
    contador_temp++;
}

return 0;
}
