#include <stdio.h>
#include <stdlib.h>
#include "macros_correcoes.h"

/* Recebe duas strings e concatena em uma terceira */
char *mystrcat(char *str1, char *str2) {
    int counter1 = 0;
    char character1 = str1[counter1];
    while (character1 != '\0') {
        counter1++;
        character1 = str1[counter1];
    }

    int counter2 = 0;
    char character2 = str2[counter2];
    while (character2 != '\0') {
        counter2++;
        character2 = str2[counter2];
    }
    counter2++;

    int size = counter1 + counter2;
    char *strconcat; 
    strconcat = (char *) malloc(sizeof(char) * size);
    if (strconcat == NULL) {
        perror("malloc");
        exit(0);
    }

    for (int i = 0; i < size; i++) {
        if (i < counter1) {
            strconcat[i] = str1[i];
        } else {
            strconcat[i] = str2[i - counter1];
        }
    }

    return strconcat;
}

int main(int argc, char *argv[]) {
    # define teste1 "str1"
    # define teste2 "str2"
    # define teste3 "0 str 3"


    char *res = mystrcat(teste1, teste2);
    assertEquals("teste 1", strcmp(res, teste1 teste2), 0);
    free(res);

    res = mystrcat(teste1, teste1);
    assertEquals("teste 2", strcmp(res, teste1 teste1), 0);
    free(res);

    res = mystrcat(teste1, teste3);
    assertEquals("teste 3", strcmp(res, teste1 teste3), 0);
    free(res);

    res = mystrcat(teste3, teste1);
    assertEquals("teste 4", strcmp(res, teste3 teste1), 0);
    free(res);

    res = mystrcat("", teste2);
    assertEquals("teste vazio 1", strcmp(res, teste2), 0);
    free(res);

    res = mystrcat(teste1, "");
    assertEquals("teste vazio 2", strcmp(res, teste1), 0);
    free(res);

    res = mystrcat("", "");
    assertEquals("teste vazio 3", strcmp(res, ""), 0);
    free(res);

    printSummary

    return 0;
}
