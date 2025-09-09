#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <pthread.h> /* pthread_t */
#include <time.h> /* clock_gettime */
#include <unistd.h> /* sleep */

#define N 1000000        
#define NTHREADS 8      

int *g_array;

static void *worker(void *arg)
{
    int i = 0;
    int tid = *(int *)arg;
    int block_size = N / NTHREADS;
    int start = tid * block_size;
    int end = (tid == NTHREADS - 1) ? N : start + block_size;

    for (i = start; i < end; i++)
    {
        g_array[i] = i;
    }

    return NULL;
}

static long timespec_diff_ns(const struct timespec *a, const struct timespec *b)
{
    long sec = b->tv_sec - a->tv_sec;
    long nsec = b->tv_nsec - a->tv_nsec;
    return sec * 1000000000L + nsec;
}

int main(void)
{
    int i = 0;
    long ns = 0;
    double ms = 0;
    size_t bad = 0;
    pthread_t threads[NTHREADS];
    int tids[NTHREADS];
    struct timespec tstart;
    struct timespec tend;

    g_array = malloc(sizeof(int) * N);
    if (!g_array)
    {
        perror("malloc");
        return 1;
    }

    for (i = 0; i < N; i++)
    {
        g_array[i] = -1;
    }

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    for (i = 0; i < NTHREADS; i++)
    {
        tids[i] = i;
        if (pthread_create(&threads[i], NULL, worker, &tids[i]) != 0)
        {
            perror("pthread_create");
            return 2;
        }

        pthread_detach(threads[i]);
    }

    sleep(1);

    clock_gettime(CLOCK_MONOTONIC, &tend);

    ns = timespec_diff_ns(&tstart, &tend);
    ms = ns / 1e6;

    printf("Thread pool with %d detached threads filled %d entries in %.3f ms\n", NTHREADS, N, ms);
    
    for (i = 0; i < N; i++)
    {
        if (g_array[i] != i)
        {
            bad++;
        }
    }

    if (bad == 0)
    {
        printf("All %d entries are correct.\n", N);
    }
    else
    {
        printf("Verification failed: %zu incorrect entries.\n", bad);
    }

    free(g_array);
    return 0;
}
