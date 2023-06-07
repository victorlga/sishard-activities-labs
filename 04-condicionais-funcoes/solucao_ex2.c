long vezes2(long a);

/* Implementar função solucao_ex2 */

long solucao_ex2(long a, long b) {
    long b2 = vezes2(b);
    if (b2 > a) {
        a += a;
    }
    return b2 + a;
}