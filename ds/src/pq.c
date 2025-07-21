/***************************
 * Exercise: PQ
 * Date:     21/07/25
 * Developer: Baruch Haimson
 * Reviewer: menny
 * Status:   In Progress
 ***************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "sortedl.h" /* sortedlCreate */
#include "pq.h" /* pq_t */

struct pq
{
	sortedl_t* queue;
};

pq_t* PQCreate(int(*comp_func)(const void* data1, const void* data2))
{
	pq_t* priority_queue = (pq_t*)malloc(sizeof(pq_t));
	if (!priority_queue)
    {
        return NULL;
    }
	
	priority_queue->queue = SortedLCreate(comp_func);
	if (!priority_queue->queue)
    {
        free(priority_queue);
        return NULL;
    }

    return priority_queue;
}
void PQDestroy(pq_t* pq)
{
	assert(pq);

    SortedLDestroy(pq->queue);
    
    free(pq);
    
    pq = NULL;
}

int PQEnqueue(pq_t* pq , void* data)
{
	sorted_iter_t iter_to_insert = {0};

    assert(pq);

	iter_to_insert = SortedLInsert(pq->queue, data);
	
	return (SortedLIsEqual(iter_to_insert, SortedLEnd(pq->queue))) ? 1 : 0;
}

void* PQRemove(pq_t* pq)
{
	void *data = NULL;
    sorted_iter_t iter;

    assert(pq);
    
    if (PQIsEmpty(pq))
    {
        return NULL;
    }
    
    iter = SortedLBegin(pq->queue);
    data = SortedLGetData(iter);

    SortedLRemove(iter);

    return data;
}

void* PQPeek(const pq_t* pq)
{
	assert(pq);
    assert(!PQIsEmpty(pq));

    return SortedLGetData(SortedLBegin(pq->queue));
}

int PQIsEmpty(const pq_t* pq)
{
	assert(pq);

    return SortedLIsEmpty(pq->queue);
}

size_t PQSize(const pq_t* pq)
{
	assert(pq);
	
	return SortedLSize(pq->queue);
}

void PQClear(pq_t* pq)
{
	assert(pq);
		
	while(!PQIsEmpty(pq))
	{
		PQRemove(pq);
	}
}
void PQErase(pq_t* pq, int (*is_match_func)(const void* data, const void* param), const void* param)
{
	sorted_iter_t iter = {0};
	assert(pq);
	assert(is_match_func);

	iter = SortedLFindIf(SortedLBegin(pq->queue), SortedLEnd(pq->queue), is_match_func, param);
	if (!SortedLIsEqual(iter, SortedLEnd(pq->queue)))
	{
		SortedLRemove(iter);
	}
}
