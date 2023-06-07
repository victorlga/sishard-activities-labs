/* Implementar função solucao_ex4 */
int solucao_ex4(short a, unsigned char b) {

    if (a <= 17) {
        return 18 - a;
    }

    if (b > 66) {
        return -1;
    }
    return a - 17;
}