/**************************************
Exercise: milion threads
Date: 11/09/2025
Developer: Baruchi haimson
Reviewer: Tamar
Status: Approved
**************************************/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <pthread.h> /* pthread_t */
#include <time.h> /* clock_gettime */

typedef struct 
{
    size_t start;
    size_t end;
    size_t partial_sum;
} thread_data_t;

static long sum_divisors(size_t n) 
{
    size_t sum = 0;
    size_t i = 0;

    for (i = 1; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            sum += i;
            if (i != n / i)
            {
                sum += n / i;
            }
        }
    }
    return sum;
}

void* worker(void* arg) 
{
    size_t num = 0;
    thread_data_t* data = (thread_data_t*)arg;
    data->partial_sum = 0;

    for (num = data->start; num <= data->end; num++) 
    {
        data->partial_sum += sum_divisors(num);
    }

    return NULL;
}

static double timespec_diff_sec(const struct timespec* start, const struct timespec* end) 
{
    return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e9;
}

int main(void) 
{
    int t = 0;
    int i = 0;
    double elapsed = 0;
    struct timespec tstart;
    struct timespec tend;
    size_t total_sum = 0;
    size_t number = 1000000LL; 
    int thread_options[] = {1, 3, 5, 8, 10, 12, 15};
    int n_options = sizeof(thread_options) / sizeof(thread_options[0]);

    for (t = 0; t < n_options; t++) 
    {
        int NTHREADS = thread_options[t];
        pthread_t threads[NTHREADS];
        thread_data_t thread_data[NTHREADS];

        size_t range = number / NTHREADS;

        total_sum = 0;

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

        elapsed = timespec_diff_sec(&tstart, &tend);

        if (NTHREADS == 1)
        {
            printf("Single-threaded: Sum of divisors = %ld, Time = %.6f sec\n", total_sum, elapsed);
        }
        else
        {
            printf("%2d threads: Sum of divisors = %ld, Time = %.6f sec\n", NTHREADS, total_sum, elapsed);
        }
    }

    return 0;
}
