#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "linear_sorting.h"

#define COUNTING_SIZE 5000 
#define RADIX_SIZE 5000
#define MIN_COUNTING 1
#define MAX_COUNTING 100
#define MIN_RADIX 1000000
#define MAX_RADIX 9999999

static void TestSortCounting()
{
    int arr[COUNTING_SIZE] = {0};
    size_t i = 0;

    srand((unsigned)time(NULL));

    for (i = 0; i < COUNTING_SIZE; ++i)
    {
        arr[i] = MIN_COUNTING + rand() % (MAX_COUNTING - MIN_COUNTING + 1);
    }

    SortCounting(arr, COUNTING_SIZE);

    for (i = 1; i < COUNTING_SIZE; ++i)
    {
        assert(arr[i - 1] <= arr[i]);
    }

    printf("TestSortCounting passed successfully.\n");
}

static void TestSortRadix()
{
    int arr[RADIX_SIZE] = {0};
    size_t i = 0;

    srand((unsigned)time(NULL) + 1); 

    for (i = 0; i < RADIX_SIZE; ++i)
    {
        arr[i] = MIN_RADIX + rand() % (MAX_RADIX - MIN_RADIX + 1);
    }

    SortRadix(arr, RADIX_SIZE);

    for (i = 1; i < RADIX_SIZE; ++i)
    {
        assert(arr[i - 1] <= arr[i]);
    }

    printf("TestSortRadix passed successfully.\n");
}

int main(void)
{
    TestSortCounting();
    TestSortRadix();

    return 0;
}
