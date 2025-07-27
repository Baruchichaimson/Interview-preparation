/************************************
 * Exercise: Fixed Size Allocator (FSA)
 * Date: 25/07/25
 * Developer: Baruch Haimson
 * Reviewer: avi
 * Status: In Progress
 ************************************/

#include <stdlib.h> /* size_t */
#include <assert.h> /* assert */

#include "fsa.h" /* fsa API */

#define WORD_SIZE (sizeof(size_t))

#define ALIGN_UP(x)  (((x) + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1))

#define MIN_BLOCK_SIZE sizeof(void*)

typedef struct FSA
{
    size_t next_free;
}fsa_t;


size_t FSASuggestSize(size_t block_amount, size_t block_size)
{
	return sizeof(fsa_t) + (ALIGN_UP(block_size) * block_amount);
}

fsa_t* FSAInit(void* fsa, size_t fsa_size, size_t block_size)
{
	size_t i = 0;
    size_t* curr = NULL;
    
    size_t aligned_block_size = ALIGN_UP(block_size < MIN_BLOCK_SIZE ? MIN_BLOCK_SIZE : block_size);
    
    size_t num_of_blocks = (fsa_size - sizeof(fsa_t)) / aligned_block_size;

    fsa_t* pool = (fsa_t*)fsa;

	size_t current_offset = sizeof(fsa_t);
    pool->next_free = current_offset;

     for (i = 0; i < num_of_blocks - 1; ++i)
    {
        curr = (size_t*)((char*)fsa + current_offset);
        current_offset += aligned_block_size;
        *curr = current_offset;  
    }
    
    *(size_t*)((char*)fsa + current_offset) = 0;

    return pool;
}

void* FSAAlloc(fsa_t* fsa)
{
	void* block = NULL;
	size_t curr_offset = fsa->next_free;
	
    assert(fsa);

    if (curr_offset == 0)
    {
        return NULL; 
    }
	
	block = (size_t*)((char*)fsa + curr_offset);
    fsa->next_free = *(size_t*)block;

    return ((char*)block + sizeof(size_t));
}

void FSAFree(fsa_t* fsa, void* block)
{
	size_t* block_header = NULL;

    assert(fsa);
    if (block == NULL)
    {
        return;
    }

    block_header = (size_t*)((char*)block - sizeof(size_t));
    
    *block_header = fsa->next_free;

    fsa->next_free = (char*)block_header - (char*)fsa;
}

size_t FSACountFree(const fsa_t* fsa)
{
    size_t count = 0;
    size_t offset = fsa->next_free;

    while (offset != 0)
    {
        ++count;
        offset = *(size_t*)((char*)fsa + offset);
    }

    return count;
}
