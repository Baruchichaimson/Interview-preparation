pq_t* PQCreate(int(*comp)(const void* data1, const void* data2))
{
	sortedl_t* sort_list = (sortedl_t*)malloc(sizeof(sortedl_t));
    if (!sort_list)
    {
        return NULL;
    }

    sort_list->list = DLLCreate();
    if (!sort_list->list)
    {
        free(sort_list);
        return NULL;
    }

    sort_list->cmp = cmp;

    return sort_list;
}
}
void PQDestroy(pq_t* pq)
{
	assert(list);

    DLLDestroy(list->list);
    
    free(list);
    
    list = NULL;
}
int PQEnqueue(pq_t* pq const void* data)
{
	sorted_iter_t iter_for_insert;

    assert(list);

    dll_iter_t pos = FindInsertPosition(list, data);

    iter_for_insert.iter = DLLInsert(list->list, pos, data);

#ifndef NDEBUG
    iter_for_insert.list = list;
#endif

    return iter_for_insert;
}
void* PQRemove(pq_t* pq)
{
	assert(to_remove.iter);

    to_remove.iter = DLLRemove(to_remove.iter);

    return to_remove;
}
void* PQPeek(const pq_t* pq)
{
	assert(list);
    assert(!SortedLIsEmpty(list));

    return DLLPopFront(list->list);
}
int PQIsEmpty(const pq_t* pq)
{
	assert(list);

    return DLLIsEmpty(list->list);
}
size_t PQSize(const pq_t* pq)
{
	assert(list);

    return DLLCount(list->list);
}
void PQClear(pq_t* pq)
{
	
}
void PQErase(pq_t* pq, void* data)
{

}
