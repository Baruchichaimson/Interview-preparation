/***************************
 * Exercise: PQ
 * Date:     21/07/25
 * Developer: Baruch Haimson
 * Reviewer: menny
 * Status:   In Progress
 ***************************/

#ifndef ILRD_PQ_H
#define ILRD_PQ_H

#include <stddef.h> /* size_t */

/*
 * Priority Queue (PQ) - A data structure that maintains elements in a sorted order
 * based on a user-provided comparison function. Internally uses a sorted list.
 */

typedef struct pq pq_t;

/*
 * Creates a new empty Priority Queue.
 *
 * Parameters:
 * - comp: pointer to comparison function (returns negative if data1 < data2).
 *
 * Return:
 * - Pointer to a new pq_t object on success.
 * - NULL on allocation failure.
 *
 * Time Complexity: O(1)
 */
pq_t* PQCreate(int(*comp)(const void* data1, const void* data2));

/*
 * Destroys the Priority Queue and frees all associated memory.
 *
 * Parameters:
 * - pq: pointer to the Priority Queue to destroy (must not be NULL).
 *
 * Time Complexity: O(n)
 */
void PQDestroy(pq_t* pq);

/*
 * PQEnqueue:
 * ---------------------
 * Inserts a new element into the Priority Queue based on priority order.
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 * - data: pointer to the data to be inserted.
 *
 * Return:
 * - 0 on success.
 * - 1 on failure (insert at end).
 *
 * Time Complexity: O(n)
 */
int PQEnqueue(pq_t* pq , void* data);

/*
 * Removes and returns the element with the highest priority (smallest according to comp).
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 *
 * Return:
 * - Pointer to the data removed, or NULL if the queue is empty.
 *
 * Time Complexity: O(1)
 */
void* PQRemove(pq_t* pq);

/*
 * Returns the data with the highest priority without removing it.
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 *
 * Return:
 * - Pointer to the data at the front of the queue.
 *
 * Time Complexity: O(1)
 */
void* PQPeek(const pq_t* pq);

/*
 * Checks whether the Priority Queue is empty.
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 *
 * Return:
 * - 1 if the queue is empty, 0 otherwise.
 *
 * Time Complexity: O(1)
 */
int PQIsEmpty(const pq_t* pq);

/*
 * Returns the number of elements in the Priority Queue.
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 *
 * Return:
 * - Number of elements in the queue.
 *
 * Time Complexity: O(n)
 */
size_t PQSize(const pq_t* pq);

/*
 * Removes all elements from the Priority Queue.
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 *
 * Time Complexity: O(n)
 */
void PQClear(pq_t* pq);

/*
 * Removes a specific element matching a condition from the Priority Queue.
 *
 * Parameters:
 * - pq: pointer to Priority Queue (must not be NULL).
 * - is_match_func: pointer to a matching function that returns non-zero on match.
 * - param: additional parameter passed to is_match_func.
 *
 * Time Complexity: O(n)
 */
void* PQErase(pq_t* pq, int (*is_match_func)(const void* data, const void* param), const void* param);


#endif /* ILRD_PQ_H */

