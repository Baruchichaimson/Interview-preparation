#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "queue.h"
#include "sll.h"

struct queue
{
    sll_t* queue;
};


queue_t* QueueCreate(void)
{
	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
    if (!queue)
    {
        return NULL;
    }

    queue->queue = SLLCreate();
    if (!queue->queue)
    {
        free(queue);
        return NULL;
    }

    return queue;
} 
void QueueDestroy(queue_t* queue) 
{
	if (!queue)
    {
        return;
    }

    SLLDestroy(queue->queue);
    free(queue);
} 
int QueueEnqueue(queue_t* queue, void* data)
{
	return (NULL != SLLInsert(SLLEnd(queue->queue), data));
} 
void QueueDequeue(queue_t* queue)
{
	if(!QueueIsEmpty(queue))
	{
		SLLRemove(SLLBegin(queue->queue));
	}
} 
int QueueIsEmpty(const queue_t* queue)
{
	return SLLIsEmpty(queue->queue);
} 
size_t QueueSize(const queue_t* queue)
{
	return SLLCount(queue->queue);
} 
void* QueuePeek(const queue_t* queue)
{
    if (QueueIsEmpty(queue))
    {
        return NULL;
    }

	return SLLGetData(SLLBegin(queue->queue));
} 
queue_t* QueueAppend(queue_t* src, queue_t* dst)
{
	SLLAppend(src->queue, dst->queue);
    return dst;
} 
