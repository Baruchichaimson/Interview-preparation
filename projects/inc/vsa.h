#ifndef __ILRD_VSA_H__
#define __ILRD_VSA_H__

#include <stddef.h> /* size_t */

typedef struct VSA vsa_t;

vsa_t* VSAInit(void* pool, size_t pool_size);

void* VSAAlloc(vsa_t* vsa, size_t block_size);

void VSAFree(void* block);

size_t VSALargestChunkAvailable(vsa_t* vsa);

#endif /* __ILRD_VSA_H__ */
