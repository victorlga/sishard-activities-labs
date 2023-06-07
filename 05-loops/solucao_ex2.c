/* Implemente aqui sua versão em C da função soma_n
 * presente no arquivo ex2.o
 *
 * Chame sua função de soma_n_solucao */
long soma_n_solucao(int a) {
    long soma = 0;
    long cont = 0;
    
    while (cont < a) {
        soma += cont;
        cont++;
    }
    return soma;
}