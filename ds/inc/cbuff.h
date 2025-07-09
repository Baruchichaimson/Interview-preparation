/***************************
 Exercise:  cbuff
 Date: 	    07/07/25
 Developer: Baruch Haimson
 Reviewer:  Avi
 Status:    Approved
***************************/

#ifndef _ILRD_CBUFF_
#define _ILRD_CBUFF_

#define DEFAULT_CAP (8)

#include <stddef.h>
#include <sys/types.h>

typedef struct cbuff cbuff_t;

/*---------------------------------------------------------
 * Receives: 
 *     - size_t capacity: the total size in bytes to allocate for the buffer.
 * 
 * Does:
 *     - Allocates and initializes a circular buffer of the given capacity.
 * 
 * Returns:
 *     - Pointer to the created circular buffer.
 *     - NULL if allocation fails.
 * 
 * Undefined Behavior:
 *     - If capacity is 0.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
cbuff_t* CBuffCreate(size_t capacity);

/*---------------------------------------------------------
 * Function: CBuffDestroy
 * --------------------------------------------------------
 * Receives:
 *     - cbuff_t* cbuff: pointer to the circular buffer to destroy.
 * 
 * Does:
 *     - Frees all memory allocated for the circular buffer.
 * 
 * Returns:
 *     - Nothing.
 * 
 * Undefined Behavior:
 *     - If cbuff is NULL.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
void CBuffDestroy(cbuff_t* cbuff);

/*---------------------------------------------------------
 * Receives:
 *     - cbuff_t* cbuff: pointer to the circular buffer.
 *     - const void* src: source buffer to write from.
 *     - size_t bytes: number of bytes to write.
 * 
 * Does:
 *     - Writes up to `bytes` from src into the circular buffer.
 *     - If not enough space, writes as much as possible.
 * 
 * Returns:
 *     - Number of bytes successfully written.
 *     - -1 on error (e.g. cbuff is NULL, src is NULL, or buffer is full).
 * 
 * Undefined Behavior:
 *     - If cbuff or src is NULL.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
ssize_t CBuffWrite(cbuff_t* cbuff, const void* src, size_t bytes);

/*---------------------------------------------------------
 * Receives:
 *     - cbuff_t* cbuff: pointer to the circular buffer.
 *     - void* dst: destination buffer to read into.
 *     - size_t bytes: number of bytes to read.
 * 
 * Does:
 *     - Reads up to `bytes` from the circular buffer into dst.
 *     - If not enough data, reads as much as available.
 * 
 * Returns:
 *     - Number of bytes successfully read.
 *     - -1 on error (e.g. cbuff is NULL, dst is NULL, or buffer is empty).
 * 
 * Undefined Behavior:
 *     - If cbuff or dst is NULL.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
ssize_t CBuffRead(cbuff_t* cbuff, void* dst, size_t bytes);

/*---------------------------------------------------------
 * Receives:
 *     - cbuff_t* cbuff: pointer to the circular buffer.
 * 
 * Does:
 *     - Checks if the circular buffer is empty.
 * 
 * Returns:
 *     - 1 if the buffer is empty.
 *     - 0 if not empty.
 * 
 * Undefined Behavior:
 *     - If cbuff is NULL.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
int CBuffIsEmpty(const cbuff_t* cbuff);

/*---------------------------------------------------------
 * Function: CBuffFreeSpace
 * --------------------------------------------------------
 * Receives:
 *     - cbuff_t* cbuff: pointer to the circular buffer.
 * 
 * Does:
 *     - Calculates how many free bytes are left for writing.
 * 
 * Returns:
 *     - Number of bytes available to write.
 * 
 * Undefined Behavior:
 *     - If cbuff is NULL.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
size_t CBuffFreeSpace(const cbuff_t* cbuff);

/*---------------------------------------------------------
 * Function: CBuffSize
 * --------------------------------------------------------
 * Receives:
 *     - cbuff_t* cbuff: pointer to the circular buffer.
 * 
 * Does:
 *     - Calculates how many bytes are currently stored and ready to read.
 * 
 * Returns:
 *     - Number of bytes currently in the buffer.
 * 
 * Undefined Behavior:
 *     - If cbuff is NULL.
 * 
 * Time Complexity:
 *     - O(1)
 ---------------------------------------------------------*/
size_t CBuffSize(const cbuff_t* cbuff);

#endif /* _ILRD_CBUFF_ */

