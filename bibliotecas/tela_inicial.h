#include <stdio.h>
#include <stdlib.h>

void menu();
void menu_jogar();
void menu_regras();
void menu_sobre_nos();
int sair();

void tela_inicial() {
    int opcao;
    menu();
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            menu_jogar();
            scanf("%d", &opcao);
            break;
        case 2:
            menu_regras();
            scanf("%d", &opcao);
            break;
        case 3:
            menu_sobre_nos();
            scanf("%d", &opcao);

            break;
        case 4:
            sair();
            break;

        default:
            break;
    }
}

void menu() {
    system("cls");
    printf("\n");
    printf("*************************\n");
    printf("*      JOGO DOMINO      *\n");
    printf("*                       *\n");
    printf("*  [1] - JOGAR          *\n");
    printf("*  [2] - REGRAS         *\n");
    printf("*  [3] - SOBRE NOS      *\n");
    printf("*  [4] - SAIR           *\n");
    printf("*                       *\n");
    printf("*************************\n");
}

void menu_jogar() {
    system("cls");
    printf("\n");
    printf("*************************\n");
    printf("*         JOGAR         *\n");
    printf("*                       *\n");
    printf("*  [1] - 2 JOGADORES    *\n");
    printf("*  [2] - 4 JOGADORES    *\n");
    printf("*  [3] - VOLTAR         *\n");
    printf("*                       *\n");
    printf("*************************\n");
}

void menu_regras() {
    printf("*************************\n");
    printf("*        REGRAS         *\n");
    printf("*                       *\n");
    printf("*  [1] - VOLTAR         *\n");
    printf("*************************\n");
}

void menu_sobre_nos() {
    printf("*************************\n");
    printf("*       SOBRE NOS       *\n");
    printf("*                       *\n");
    printf("*  [1] - VOLTAR         *\n");
    printf("*************************\n");
}

int sair() {
    printf("\nFim de Jogo.\n");
    return 0;
}