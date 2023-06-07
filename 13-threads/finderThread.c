// gcc finderThread.c -o finderThread -pthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// implemente aqui sua solução!

typedef struct 
{
    int *vetor;
    int k;
    int tamanho;
    int elemento;
    int indice;
    int thread;
} thread_arg;

void *thread_function(void *arg)
{
    sleep(5);
    thread_arg *t_arg = (thread_arg *)arg;
    int *vetor = t_arg->vetor;
    int k = t_arg->k;
    int tamanho = t_arg->tamanho;
    int inicio = (tamanho / k) * t_arg->thread;
    int fim = inicio + (tamanho / k);
    int elemento = t_arg->elemento;

    for (int i = inicio; i < fim; i++)
    {
        if (vetor[i] == elemento)
        {
            printf("Elemento encontrado na posição %d\n", i);
            t_arg->indice = i;
            return NULL;
        }
    }
    t_arg->indice = -1;

    return NULL;
}

int main()
{
    int elemento;
    scanf("%d", &elemento);

    int tamanho;
    scanf("%d", &tamanho);

    int vetor[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        scanf("%d", &vetor[i]);
    }

    int k;
    scanf("%d", &k);

    pthread_t *tid = malloc(sizeof(pthread_t) * k);
    thread_arg *arg = malloc(sizeof(thread_arg) * k);

    for (int thread = 0; thread < k; thread++)
    {
        arg[thread].k = k;
        arg[thread].vetor = vetor;
        arg[thread].tamanho = tamanho;
        arg[thread].elemento = elemento;
        arg[thread].thread = thread;
        pthread_create(&tid[thread], NULL, &thread_function, &arg[thread]);
    }

    elemento = -1;
    int indice = -1;
    int thread = -1;

    for (int thread = 0; thread < k; thread++)
    {
        pthread_join(tid[thread], NULL);
        if (arg[thread].indice != -1 && elemento == -1)
        {
            elemento = arg[thread].elemento;
            indice = arg[thread].indice;
            thread = arg[thread].thread;
        }
    }

    if (elemento != -1)
    {
        printf("Elemento %d encontrado pela thread %d na posição %d!\n", elemento, thread, indice);
    }
    else
    {
        printf("Elemento não encontrado!\n");
    }
    
    free(tid);
    free(arg);
    return 0;
}