#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <pthread.h> /* pthread_t */
#include <time.h> /* clock_gettime */
#include <unistd.h> /* sleep */

#define N 1000000

int *g_array;

static void *worker(void *arg) 
{
    int idx = *(int *)arg;
    g_array[idx] = idx;

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
    pthread_t th;
    size_t bad = 0;
    int printed = 0;
    struct timespec tstart;
    struct timespec tend;
    int *indices = NULL;

    g_array = malloc(sizeof(int) * N);
    if (!g_array) 
    {
        perror("malloc");
        return 1;
    }

    for (i = 0; i < N; ++i) 
    {
        g_array[i] = -1;
    }

    indices = malloc(sizeof(int) * N);
    if (!indices) 
    {
        perror("malloc");
        return 2;
    }

    for (i = 0; i < N; ++i) 
    {
        indices[i] = i;
    }

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    for (i = 0; i < N; ++i) 
    {
        pthread_create(&th, NULL, worker, &indices[i]);
        pthread_detach(th);
    }

    clock_gettime(CLOCK_MONOTONIC, &tend);

    ns = timespec_diff_ns(&tstart, &tend);
    ms = ns / 1e6;

    printf("Spawned %d threads in %.3f ms (%.0f us/thread)\n", N, ms, (ms*1000.0)/N);

    sleep(10);

    for (i = 0; i < N; ++i) 
    {
        if (g_array[i] != i) 
        {
            ++bad;
        }
    }

    if (bad == 0) 
    {
        printf("All %d entries are correct.\n", N);
    } 
    else 
    {
        printf("Verification failed: %zu incorrect entries out of %d.\n", bad, N);
        
        for (i = 0; i < N && printed < 10; ++i) 
        {
            if (g_array[i] != i) 
            {
                printf(" index %d => %d\n", i, g_array[i]);
                ++printed;
            }
        }
    }

    free(g_array);
    free(indices);
    return 0;
}