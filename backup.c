void escolher_modo(int *x) {
    printf("Dois [2] ou Quatro [4] Jogadores?\n(digite zero [0] para sair)\n-> ");
    scanf("%d", x);
    while (1) {
        if (*x == 2 || *x == 4 || *x == 0)
            break;
        else {
            system("cls");
            printf("Tente novamente.\nDois [2] ou Quatro [4] Jogadores?\n(digite zero [0] para sair)\n->");
            scanf("%d", x);
        }
    }
}
/*
tp_item peca_retirada = verificar_peca(&jogador1.mao, posicao);
if (validar_peca(mesa, peca_retirada)) break;

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

*/