/* Implementar função solucao_ex1 */

int solucao_ex1 (long a, long b, long c) {
    long comp = a + b + c * 4;
    c += a * a + b * 2;
    return comp >= c;
}