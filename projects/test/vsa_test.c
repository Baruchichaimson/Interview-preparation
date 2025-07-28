#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define POOL_SIZE 128

#include "vsa.h"

void TestVSAInit()
{
    char pool[POOL_SIZE] = {0};
    vsa_t* vsa = VSAInit(pool, POOL_SIZE);

    assert(vsa != NULL);

    size_t largest = VSALargestChunkAvailable(vsa);
    assert(largest > 0 && largest <= POOL_SIZE);

    printf("TestVSAInit passed\n");
}

void TestVSAAlloc()
{
    char pool[POOL_SIZE] = {0};
    vsa_t* vsa = VSAInit(pool, POOL_SIZE);

    void* p1 = VSAAlloc(vsa, 16);
    assert(p1 != NULL);

    void* p2 = VSAAlloc(vsa, 8);
    assert(p2 != NULL);

    void* p3 = VSAAlloc(vsa, POOL_SIZE);  
    assert(p3 == NULL);

    printf("TestVSAAlloc passed\n");
}

void TestVSAFree()
{
    char pool[POOL_SIZE] = {0};
    vsa_t* vsa = VSAInit(pool, POOL_SIZE);

    void* p1 = VSAAlloc(vsa, 16);
    void* p2 = VSAAlloc(vsa, 8);

    VSAFree(p1);
    VSAFree(p2);

    void* p3 = VSAAlloc(vsa, 24);  
    assert(p3 != NULL);

    printf("TestVSAFree passed\n");
}

void TestVSALargestChunkAvailable()
{
    char pool[POOL_SIZE] = {0};
    vsa_t* vsa = VSAInit(pool, POOL_SIZE);

    size_t before = VSALargestChunkAvailable(vsa);
	printf("%zu \n" ,before);
    assert(before > 0);

    void* p1 = VSAAlloc(vsa, 16);
    void* p2 = VSAAlloc(vsa, 9);

    size_t mid = VSALargestChunkAvailable(vsa);
    printf("%zu \n" ,before);
	printf("%zu \n" ,mid);
    assert(mid < before);

    VSAFree(p1);
    VSAFree(p2);

    size_t after = VSALargestChunkAvailable(vsa);
    assert(after >= mid);

    printf("TestVSALargestChunkAvailable passed\n");
}

int main()
{
    TestVSAInit();
    TestVSAAlloc();
    TestVSAFree();
    TestVSALargestChunkAvailable();

    printf("\nAll tests passed successfully!\n");
    return 0;
}
