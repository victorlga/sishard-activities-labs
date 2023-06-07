// implemente aqui sua solução!
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int x;
    int n;
    printf("Qual o elemento a ser buscado? ");
    scanf("%d", &x);
    printf("Qual o tamanho do array? ");
    scanf("%d", &n);

    int e;
    int A[n];
    printf("Digite os %d elementos do array:\n", n);
    for (int i = 0; i < n; i++) {
        //printf("Qual o elemento %d: ", i);
        scanf("%d", &e);
        A[i] = e;
    }
    
    int k;
    printf("Qual a quantidade de processos? ");
    scanf("%d", &k);
    int part_size = n / k;
    int quant_filhos = 0;
    int e_aval;
    pid_t filhos[k];

    while (quant_filhos < k) {
        pid_t filho = fork();
        quant_filhos++;

        if (filho == 0) {
            sleep(5);
            for (int i = 0; i < part_size; i++) {
                int pos = i + (quant_filhos-1) * part_size;
                e_aval = A[pos];
                if (e_aval == x)
                    exit(i);
            }
            exit(-1);
        } else {
            filhos[quant_filhos-1] = filho;
            printf("Criou filho %d com PID=%d, r=[%d,%d)\n", quant_filhos-1, filho, (quant_filhos-1) * part_size, quant_filhos * part_size);
        }
    }
    
    printf("Processo pai esperando os filhos finalizarem...\n");
    int status;
    int filho_encontrou = -1;
    int indice = -1;
    
    for (int i = 0; i < k; i++) {
        waitpid(filhos[i], &status, 0);
        if (WIFEXITED(status)) {
            char exit_status = WEXITSTATUS(status);
            if (exit_status != -1) {
                filho_encontrou = i;
                indice = exit_status + i * part_size;
                break;    
            }
        }
    }
    if (filho_encontrou != -1)
        printf("Elemento %d encontrado pelo processo %d no indice %d\n", x, filho_encontrou, indice);
    else
        printf("Elemento não encontrado!\n", x);

    return 0;
}