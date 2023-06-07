int ex5_solucao () {
    // implemente sua resposta aqui.
    // TODO: conserte valor de retorno e argumentos, se for necessário
    int a = 1;
    int b = 0;

    while (a > 0) {
        scanf("%d", &a);
        if (a > 0) {
            b += a;
        }
    }

    return b;
}
