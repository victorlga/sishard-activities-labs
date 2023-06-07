#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

int num_barrier = 0;
struct _arg_t
{
    pthread_mutex_t mutex;
    sem_t *sid;
};

typedef struct _arg_t arg_t;

void *thread_barreira(void *arg)
{
    arg_t *local_arg = (arg_t *)arg;
    // NÃO altere este print, ele simula uma tarefa
    printf("Antes da barreira\n");

    // TODO: implemente a barreira aqui

    if (num_barrier == 3)
    {
        sem_post(local_arg->sid);
    }
    else
    {
        pthread_mutex_lock(&local_arg->mutex);
        num_barrier++;
        pthread_mutex_unlock(&local_arg->mutex);
        sem_wait(local_arg->sid);
        sem_post(local_arg->sid);
    }

    // NÃO altere este print, ele simula uma tarefa
    printf("Depois da barreira\n");

    return NULL;
}

int main()
{
    // TODO: crie 4 threads rodando o código acima

    int quant_thread = 4;
    pthread_t *tid = malloc(sizeof(pthread_t) * quant_thread);
    pthread_mutex_t mutex_barrier = PTHREAD_MUTEX_INITIALIZER;
    sem_t *sid = malloc(sizeof(sem_t));
    sem_init(sid, 0, 0);

    arg_t *arg = malloc(sizeof(arg_t));
    arg->mutex = mutex_barrier;
    arg->sid = sid;

    for (int i = 0; i < quant_thread; i++)
    {
        pthread_create(&tid[i], NULL, thread_barreira, arg);
    }
    
    // TODO: espere por elas

    for (int i = 0; i < quant_thread; i++)
    {
        pthread_join(tid[i], NULL);
    }

    free(tid);
    free(sid);
    free(arg);

    return 0;
}
