/* Implemente aqui sua versão em C da função ex3
 * presente no arquivo ex3.o
 * 
 * Chame sua função de ex3_solucao */

long ex3_solucao (long rdi, long rsi) {
    long rcx = 0;
    long r8 = 0;
    long rdx;

    goto jump;

    soma_reg:
    rcx += 1;

    jump:
    if (rcx >= rdi) goto maiorigual;

    rdx = rcx % rsi;

    if (rdx != 0) goto soma_reg;
    r8 += rcx;
    goto soma_reg;

    maiorigual:
    return r8;
}