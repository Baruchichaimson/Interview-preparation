#ifndef ILRD_PQ_H
#define ILRD_PQ_H

typedef struct pq pq_t;

pq_t*   PQCreate(int(*comp)(const void* data1, const void* data2)); /* O(1) */
void    PQDestroy(pq_t* pq) /* O(n) */
int     PQEnqueue(pq_t* pq const void* data) /* O(n) */
void*   PQRemove(pq_t* pq) /* O(1) */
void*   PQPeek(const pq_t* pq) /* O(1) */
int     PQIsEmpty(const pq_t* pq) /* O(1) */
size_t  PQSize(const pq_t* pq) /* O(n) */
void    PQClear(pq_t* pq) /* O(n) */
void    PQErase(pq_t* pq, void* data) /* O(n) */ 

#endif /* ILRD_PQ_H */
