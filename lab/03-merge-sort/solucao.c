#include "sort-merge.h"
// ... aqui começa sua solucao.
// para compilar use
// gcc -g -Og -Wall sort.o solucao.c -o sort -pthread

#define MAX_LINE 21

void getLines(FILE *fp, int startLine, int nLines, char **buffer, pthread_mutex_t *mutex_file)
{
    char line[MAX_LINE];
    int lineCount = 0;

    pthread_mutex_lock(mutex_file);
    rewind(fp);
    fscanf(fp,"%s",line);

    while (lineCount < (startLine + nLines + 1))
    {
        if (lineCount >= startLine && lineCount < startLine + nLines)
        {
            strcpy(buffer[lineCount - startLine], line);
        }

        lineCount++;
    
        fscanf(fp,"%s",line);
    }

    pthread_mutex_unlock(mutex_file);
}

void insertion_sort(int size, char **buffer)
{
    for (int i = 1; i < size; i++) {
        char temp[MAX_LINE];
        strcpy(temp, buffer[i]);

        int j = i;
        while (j > 0 && strcmp(buffer[j - 1], temp) > 0) {
            strcpy(buffer[j], buffer[j - 1]);
            j--;
        }

        strcpy(buffer[j], temp);
    }
}

void count_lines(FILE *fp, int *lineFiles)
{
    char line[MAX_LINE];
    *lineFiles = 0;

    while (fscanf(fp,"%s",line) != EOF)
    {
        (*lineFiles)++;
    }
}

void * sort(void *args)
{
    struct sort_args *vet_sort = (struct sort_args *) args;

    int idxThread = vet_sort->idxThread;
    int nThreads = vet_sort->nThreads;
    int lineFiles = vet_sort->lineFiles;
    FILE *fp = vet_sort->fp;
    pthread_mutex_t *mutex_file = vet_sort->mutex_file;
    int size = lineFiles / nThreads;
    int startLine = idxThread * size;

    // Cria uma lista para receber todas as strings da área entre startLine e startLine + nThreads
    char **buffer = malloc(sizeof(char *) * size);
    for (int i = 0; i < size; i++) {
        buffer[i] = malloc(sizeof(char) * MAX_LINE);
    }

    getLines(fp, startLine, size, buffer, mutex_file);
    
    // Ordena a lista
    insertion_sort(size, buffer);

    // Escreve a lista ordenada em um arquivo chamado "%d.txt", onde %d é o número da thread
    char filename[10];
    sprintf(filename, "%d.txt", idxThread);
    FILE *fp2 = fopen(filename, "w+");

    for (int i = 0; i < size; i++) {
        fprintf(fp2, "%s\n", buffer[i]);
    }

    for (int i = 0; i < size; i++) {
        free(buffer[i]);
    }
    free(buffer);
    
    return fp2;
}

void * merge(void *args)
{
    struct merge_args * merge_arg = (struct merge_args *) args;
    int idxThread = merge_arg->idxThread;
    int nThreads = merge_arg->nThreads;
    FILE *fp1 = merge_arg->fp1;
    FILE *fp2 = merge_arg->fp2;

    rewind(fp1);
    rewind(fp2);

    char filename[10];
    sprintf(filename, "%d%d.txt", nThreads, idxThread);
    FILE *fp3 = fopen(filename, "w+");

    char line1[MAX_LINE];
    char line2[MAX_LINE];

    int fp1_ret = fscanf(fp1, "%s", line1);
    int fp2_ret = fscanf(fp2, "%s", line2);

    while (fp1_ret > 0 || fp2_ret > 0) {

        if (fp1_ret < 0) {
            fprintf(fp3, "%s\n", line2);
            fp2_ret = fscanf(fp2, "%s", line2);
        }
        else if (fp2_ret < 0) {
            fprintf(fp3, "%s\n", line1);
            fp1_ret = fscanf(fp1, "%s", line1);
        }
        else if (strcmp(line1,line2) > 0) {
            fprintf(fp3, "%s\n", line2);
            fp2_ret = fscanf(fp2, "%s", line2);
        }
        else {
            fprintf(fp3, "%s\n", line1);
            fp1_ret = fscanf(fp1, "%s", line1);
        }
    }
    
    fclose(fp1);
    fclose(fp2);
    return fp3;
}

