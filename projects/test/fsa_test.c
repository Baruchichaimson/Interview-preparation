/************************************
 * Exercise: Fixed Size Allocator (FSA)
 * Date: 25/07/25
 * Developer: Baruch Haimson
 * Reviewer: avi
 * Status: In Progress
 ************************************/

#include <stdio.h>
#include <stdlib.h>
#include "fsa.h" /* fsa API */

#define BLOCK_SIZE 32
#define BLOCK_COUNT 10


void TestFSASuggestSize()
{
    size_t suggested = FSASuggestSize(BLOCK_COUNT, BLOCK_SIZE);
    size_t expected_min = sizeof(fsa_t*) + (BLOCK_COUNT * ((BLOCK_SIZE + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1)));

    if (suggested >= expected_min)
    {
        printf("FSASuggestSize: PASS\n");
    }
    else
    {
        printf("FSASuggestSize: FAIL (got %lu, expected >= %lu)\n", suggested, expected_min);
    }
}


void TestFSAInit()
{
    size_t pool_size = FSASuggestSize(BLOCK_COUNT, BLOCK_SIZE);
    void* pool = malloc(pool_size);
    fsa_t* fsa = FSAInit(pool, pool_size, BLOCK_SIZE);

    if (fsa != NULL && fsa == pool)
    {
        printf("FSAInit: PASS\n");
    }
    else
    {
        printf("FSAInit: FAIL\n");
    }

    free(pool);
}

void TestFSAAllocFree()
{
    size_t pool_size = FSASuggestSize(BLOCK_COUNT, BLOCK_SIZE);
    void* pool = malloc(pool_size);
    fsa_t* fsa = FSAInit(pool, pool_size, BLOCK_SIZE);

    void* blocks[BLOCK_COUNT];

    size_t i;
    for (i = 0; i < BLOCK_COUNT; ++i)
    {
        blocks[i] = FSAAlloc(fsa);
        if (blocks[i] == NULL)
        {
            printf("FSAAlloc: FAIL (block %lu is NULL)\n", i);
            free(pool);
            return;
        }
    }

    if (FSAAlloc(fsa) == NULL)
    {
        printf("FSAAlloc (full): PASS\n");
    }
    else
    {
        printf("FSAAlloc (full): FAIL (expected NULL)\n");
    }

    for (i = 0; i < BLOCK_COUNT; ++i)
    {
        FSAFree(fsa, blocks[i]);
    }

    printf("FSAFree: PASS\n");

    free(pool);
}

void TestFSACountFree()
{
    size_t pool_size = FSASuggestSize(BLOCK_COUNT, BLOCK_SIZE);
    void* pool = malloc(pool_size);
    fsa_t* fsa = FSAInit(pool, pool_size, BLOCK_SIZE);

    size_t count = FSACountFree(fsa);
    if (count == BLOCK_COUNT)
    {
        printf("FSACountFree (initial): PASS\n");
    }
    else
    {
        printf("FSACountFree (initial): FAIL (expected %d, got %lu)\n", BLOCK_COUNT, count);
    }

    void* b1 = FSAAlloc(fsa);
    void* b2 = FSAAlloc(fsa);

    count = FSACountFree(fsa);
    if (count == BLOCK_COUNT - 2)
    {
        printf("FSACountFree (after 2 allocs): PASS\n");
    }
    else
    {
        printf("FSACountFree (after 2 allocs): FAIL\n");
    }

    FSAFree(fsa, b1);
    FSAFree(fsa, b2);

    count = FSACountFree(fsa);
    if (count == BLOCK_COUNT)
    {
        printf("FSACountFree (after free): PASS\n");
    }
    else
    {
        printf("FSACountFree (after free): FAIL\n");
    }

    free(pool);
}

int main()
{
    /*TestFSASuggestSize();
    TestFSAInit();
    TestFSAAllocFree();*/
    TestFSACountFree();

    return 0;
}

