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
                    */