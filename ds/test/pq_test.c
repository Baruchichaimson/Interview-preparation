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
int IsMatch(const void *data, const void *param);
/************************************************************************/


void TestCreateDestroy()
{
    printf("\n=== TestCreateDestroy ===\n");
    pq_t *pq = PQCreate(CompareInts);
    printf("PQCreate: %s\n", (pq != NULL) ? "PASS" : "FAIL");
    PQDestroy(pq);
    printf("PQDestroy: PASS (no crash)\n");
}

void TestEnqueuePeek()
{
    printf("\n=== TestEnqueuePeek ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 5, b = 1, c = 10;

    PQEnqueue(pq, &a);
    printf("Peek (Expect 1 smallest): %d\n", *(int *)PQPeek(pq));

    PQEnqueue(pq, &b);
    printf("Peek after insert 1: %d (Expected 1)\n", *(int *)PQPeek(pq));

    PQEnqueue(pq, &c);
    printf("Peek after insert 10: %d (Expected 1)\n", *(int *)PQPeek(pq));

    PQDestroy(pq);
}

void TestRemove()
{
    printf("\n=== TestRemove ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 3, b = 7, c = 1;
    void *data;

    printf("Remove empty: %s\n", PQRemove(pq) == NULL ? "PASS" : "FAIL");

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);

    data = PQRemove(pq);
    printf("Remove first: %d (Expected 1)\n", *(int *)data);

    data = PQRemove(pq);
    printf("Remove second: %d (Expected 3)\n", *(int *)data);

    data = PQRemove(pq);
    printf("Remove third: %d (Expected 7)\n", *(int *)data);

    printf("Remove after empty: %s\n", PQRemove(pq) == NULL ? "PASS" : "FAIL");

    PQDestroy(pq);
}

void TestIsEmptyAndSize()
{
    printf("\n=== TestIsEmptyAndSize ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 4, b = 2;

    printf("Empty on create: %d (Expected 1)\n", PQIsEmpty(pq));
    printf("Size empty: %lu (Expected 0)\n", PQSize(pq));

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    printf("IsEmpty after enqueue: %d (Expected 0)\n", PQIsEmpty(pq));
    printf("Size after enqueue: %lu (Expected 2)\n", PQSize(pq));

    PQRemove(pq);
    printf("Size after remove: %lu (Expected 1)\n", PQSize(pq));

    PQRemove(pq);
    printf("Empty after remove all: %d (Expected 1)\n", PQIsEmpty(pq));

    PQDestroy(pq);
}

void TestClear()
{
    printf("\n=== TestClear ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 10, b = 20, c = 30;

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);

    printf("Size before clear: %lu (Expected 3)\n", PQSize(pq));
    PQClear(pq);
    printf("Size after clear: %lu (Expected 0)\n", PQSize(pq));
    printf("IsEmpty after clear: %d (Expected 1)\n", PQIsEmpty(pq));

    PQDestroy(pq);
}

void TestErase()
{
    printf("\n=== TestErase ===\n");
    pq_t *pq = PQCreate(CompareInts);
    int a = 4, b = 8, c = 2, erase_val = 4;

    PQEnqueue(pq, &a);
    PQEnqueue(pq, &b);
    PQEnqueue(pq, &c);
    printf("Size before erase: %lu (Expected 3)\n", PQSize(pq));

    PQErase(pq, IsMatch, &erase_val);
    printf("Size after erase 4: %lu (Expected 2)\n", PQSize(pq));

    printf("Peek after erase: %d (Expected 2)\n", *(int *)PQPeek(pq));

    PQClear(pq);
    PQErase(pq, IsMatch, &erase_val);
    printf("Erase on empty queue: PASS (no crash)\n");

    PQDestroy(pq);
}

int main()
{
    TestCreateDestroy();
    TestEnqueuePeek();
    TestRemove();
    TestIsEmptyAndSize();
    TestClear();
    TestErase();

    printf("\nAll Priority Queue tests completed.\n");
    return 0;
}

/*************************** Compare Functions **************************/

int CompareInts(const void *data1, const void *data2)
{
    int num1 = *(const int *)data1;
    int num2 = *(const int *)data2;
    return num2 - num1; 
}

int IsMatch(const void *data, const void *param)
{
    return (*(int *)data == *(int *)param);
}
