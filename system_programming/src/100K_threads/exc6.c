/**************************************
Exercise: milion threads
Date: 11/09/2025
Developer: Baruchi haimson
Reviewer: Tamar
Status: Approved
**************************************/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <omp.h>  /* omp_get_wtime */

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

int main(void) 
{
    size_t i = 0;
    double tend = 0;
    size_t number = 1000000LL; 
    size_t total_sum = 0;

    double tstart = omp_get_wtime();  

    #pragma omp parallel for reduction(+:total_sum)
    for (i = 1; i <= number; i++) 
    {
        total_sum += sum_divisors(i);
    }

    tend = omp_get_wtime();  

    printf("OpenMP: Sum of divisors from 1 to %ld = %ld\n", number, total_sum);
    printf("Time taken with OpenMP: %.6f seconds\n", tend - tstart);

    return 0;
}

