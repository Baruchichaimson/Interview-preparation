/************************************
 * Exercise: sorting (bubble, insertion, selection)
 * Date: 05/08/25
 * Developer: Baruch Haimson
 * Reviewer: guy
 * Status: 
 ************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "cmp_sorting.h"

#define SIZE  (5000)

void InitArray(int* arr, size_t size);
int IsSorted(const int* arr, size_t size);
int CompareInts(const void* a, const void* b);

int main()
{
    int arr[SIZE] = {0};
    clock_t start, end;
    double duration_ms = 0.0;

    printf("====== Sorting Bubble =======\n");
    InitArray(arr, SIZE);
    start = clock();
    SortingBubble(arr, SIZE);
    end = clock();
    assert(IsSorted(arr, SIZE));
    duration_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    printf("Bubble Sort time: %.2f ms\n", duration_ms);

    printf("\n====== Sorting Insertion =======\n");
    InitArray(arr, SIZE);
    start = clock();
    SortingInsertion(arr, SIZE);
    end = clock();
    assert(IsSorted(arr, SIZE));
    duration_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    printf("Insertion Sort time: %.2f ms\n", duration_ms);

    printf("\n====== Sorting Selection =======\n");
    InitArray(arr, SIZE);
    start = clock();
    SortingSelection(arr, SIZE);
    end = clock();
    assert(IsSorted(arr, SIZE));
    duration_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;
    printf("Selection Sort time: %.2f ms\n", duration_ms);

    printf("\n====== Sorting with qsort =======\n");
    InitArray(arr, SIZE);
    start = clock();
    qsort(arr, SIZE, sizeof(int), CompareInts);
    end = clock();
    assert(IsSorted(arr, SIZE));
    duration_ms = 1000.0* (end - start) / CLOCKS_PER_SEC;
    printf("qsort time: %.2f ms\n", duration_ms);

    return 0;
}

void InitArray(int* arr, size_t size)
{
    size_t i = 0;
    for(i = 0; i < size; ++i)
    {
        arr[i] = 1 + rand() % 10000;
    }
}

int IsSorted(const int* arr, size_t size)
{
    size_t i;
    for (i = 1; i < size; ++i)
    {
        if (arr[i - 1] > arr[i])
        {
            return 0;
        }
    }
    return 1;
}

int CompareInts(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

