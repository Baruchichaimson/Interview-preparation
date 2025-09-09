#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <pthread.h> /* pthread_t */
#include <time.h> /* clock_gettime */
#include <unistd.h> /* sleep */

#define NTHREADS 8  

typedef struct 
{
    long long start;       
    long long end;        
    long long partial_sum;

} thread_data_t;

static void *worker(void *arg)
{
    long long num = 0;
    long long sum = 0;
    long long i = 0;
    thread_data_t *data = (thread_data_t *)arg;
    data->partial_sum = 0;

    for (num = data->start; num <= data->end; num++)
    {
        sum = 0;
        for (i = 1; i * i <= num; i++) 
        {
            if (num % i == 0) 
            {
                sum += i;
                if (i != num / i)
                {
                    sum += num / i;
                }
            }
        }
        data->partial_sum += sum;
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
    long ns_elapsed = 0;
    double elapsed = 0;
    long long total_sum = 0;
    pthread_t threads[NTHREADS];
    thread_data_t thread_data[NTHREADS];
    struct timespec tstart;
    struct timespec tend;

    long long number = 1000000LL;
    long long range = number / NTHREADS;

    for (i = 0; i < NTHREADS; i++)
    {
        thread_data[i].start = i * range + 1;
        thread_data[i].end = (i == NTHREADS - 1) ? number : (i + 1) * range;
        thread_data[i].partial_sum = 0;
    }

    clock_gettime(CLOCK_MONOTONIC, &tstart);

    for (i = 0; i < NTHREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, worker, &thread_data[i]) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &tend);
    
    for (i = 0; i < NTHREADS; i++)
    {
        total_sum += thread_data[i].partial_sum;
    }

    ns_elapsed = timespec_diff_ns(&tstart, &tend);
    elapsed = ns_elapsed / 1e9;

    printf("Sum of divisors from 1 to %lld using %d threads = %lld\n", number, NTHREADS, total_sum);
    printf("Time taken: %.6f seconds\n", elapsed);

    return 0;
}
