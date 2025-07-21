/***************************
 * Exercise: PQ
 * Date:     21/07/25
 * Developer: Baruch Haimson
 * Reviewer: menny
 * Status:   In Progress
 ***************************/

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

/*************************** Compare Functions **************************/

int CompareInts(const void *data1, const void *data2);

/********************************************************************/

void TestCreateDestroy()
{
    printf("\n=== TestCreateDestroy ===\n");
    pq_t *pq = PQCreate(CompareInts);
    printf("PQCreate: %s\n", (pq != NULL) ? "PASS" : "FAIL");

    PQDestroy(pq);
    printf("PQDestroy (valid pq): PASS (no crash)\n");
}

void TestEnqueuePeek()
{
    printf("\n=== TestEnqueuePeek ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 5, b = 1, c = 10;

    PQEnqueue(pq, &a);
    printf("Peek after 1 insert: %d (Expected 5)\n", *(int *)PQPeek(pq));

    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);
    printf("Peek after 3 inserts: %d (Expected 1)\n", *(int *)PQPeek(pq));

    PQDestroy(pq);
}

void TestRemove()
{
    printf("\n=== TestRemove ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 3, b = 7, c = 1;
    void *data;

    data = PQRemove(pq);
    printf("Remove empty queue: %s\n", (data == NULL) ? "PASS" : "FAIL");

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);

    data = PQRemove(pq);
    printf("First remove: %d (Expected 1)\n", *(int *)data);

    data = PQRemove(pq);
    printf("Second remove: %d (Expected 3)\n", *(int *)data);

    data = PQRemove(pq);
    printf("Third remove: %d (Expected 7)\n", *(int *)data);

    data = PQRemove(pq);
    printf("Remove after emptying: %s\n", (data == NULL) ? "PASS" : "FAIL");

    PQDestroy(pq);
}

void TestIsEmpty()
{
    printf("\n=== TestIsEmpty ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int val = 10;

    printf("Empty on new queue: %d (Expected 1)\n", PQIsEmpty(pq));

    PQEnqueue(pq, &val);
    printf("Not empty after enqueue: %d (Expected 0)\n", PQIsEmpty(pq));

    PQRemove(pq);
    printf("Empty after remove: %d (Expected 1)\n", PQIsEmpty(pq));

    PQDestroy(pq);
}

void TestSize()
{
    printf("\n=== TestSize ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 2, b = 4, c = 6;

    printf("Size empty: %lu (Expected 0)\n", PQSize(pq));

    PQEnqueue(pq, &a);
    printf("Size after 1: %lu (Expected 1)\n", PQSize(pq));

    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);
    printf("Size after 3: %lu (Expected 3)\n", PQSize(pq));

    PQRemove(pq);
    printf("Size after 1 remove: %lu (Expected 2)\n", PQSize(pq));

    PQDestroy(pq);
}

void TestClear()
{
    printf("\n=== TestClear ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 1, b = 3;

    PQClear(pq); 
    printf("Clear empty queue: PASS (no crash)\n");

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    printf("Size before clear: %lu (Expected 2)\n", PQSize(pq));

    PQClear(pq);
    printf("Size after clear: %lu (Expected 0)\n", PQSize(pq));
    printf("IsEmpty after clear: %d (Expected 1)\n", PQIsEmpty(pq));

    PQDestroy(pq);
}

int IsMatch(const void *data, const void *param)
{
    return (*(int *)data == *(int *)param);
}

void TestErase()
{
    printf("\n=== TestErase ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 2, b = 4, c = 6, to_erase = 4;

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);
    printf("Size before erase: %lu (Expected 3)\n", PQSize(pq));

    PQErase(pq, IsMatch, &to_erase);
    printf("Size after erase of 4: %lu (Expected 2)\n", PQSize(pq));

    printf("Peek after erase (Expected 2): %d\n", *(int *)PQPeek(pq));

    PQClear(pq);
    PQErase(pq, IsMatch, &to_erase); 
    printf("Erase from empty queue: PASS (no crash)\n");

    PQDestroy(pq);
}

int main()
{
    TestCreateDestroy();
    TestEnqueuePeek();
    TestRemove();
    TestIsEmpty();
    TestSize();
    TestClear();
    TestErase();

    printf("All PQ tests completed.\n");
    return 0;
}

/*************************** Compare Functions **************************/
int CompareInts(const void *data1, const void *data2)
{
    int num1 = *(const int *)data1;
    int num2 = *(const int *)data2;
    return num1 - num2;
}


