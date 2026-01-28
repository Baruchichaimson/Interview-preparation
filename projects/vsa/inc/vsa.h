/**********
 Exercise:	Variable size allocation
 Date:	29/07/25
 Developer:  
 Reviewer:   
 Status: Approved
 **********/

#ifndef __ILRD_VSA_H__
#define __ILRD_VSA_H__

#include <stddef.h> /* size_t */

typedef struct VSA vsa_t;

/**
 * Description: Initialize Variable size allocator.
 *
 * Function Arguments : 
 *		 pool - memory block allocated by user.
 *		 pool_size - size of pool allocated.
 *
 * Return Value:
 *        - a pointer to the VSA.     
 *
 * General notes:
 *        - Behavior is undefined if pool pointer is NULL.
 *        - Behavior is undefined if pool_size is 0.
 * 
 * Complexity:
 *        - Time: O(1).
 **/
vsa_t* VSAInit(void* pool, size_t pool_size);

/**
 * Description: Allocate variable size block of memory.
 *
 * Function Arguments : 
 *        vsa_t* - a pointer to the VSA.
 *        block_size - requested block size.
 *
 * Return Value: 
 *        - a pointer to the new block.
 *        - NULL if no sufficent block is availabe.
 *
 * General notes: 
 *        - Behavior is undefined if vsa pointer is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
void* VSAAlloc(vsa_t* vsa, size_t block_size);

/**
 * Description: free block of memory.
 *
 * Function Arguments : 
 *		 block - block wanted to be freed.
 *
 * Return Value: None.
 *
 * General notes: 
 *        - block must be pointer recived by VSAAlloc.
 *        - block that is null will be ignored.
 *
 * Complexity:
 *        - Time: O(1).
 **/
void VSAFree(void* block);

/**
 * Description: Return the largest block available.
 *
 * Function Arguments :
 *        vsa - vsa to count free blocks in.        
 * Return Value: 
 *        - size of free block available.
 *
 * General notes: None.
 *
 * Complexity:
 *        - Time: O(n).
 **/
size_t VSALargestChunkAvailable(vsa_t* vsa);

#endif /* __ILRD_VSA_H__ */
