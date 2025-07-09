/***************************
 Exercise:  cbuff
 Date: 	    07/07/25
 Developer: Baruch Haimson
 Reviewer:  Avi
 Status:    Approved
***************************/

#include <sys/types.h> 	/* ssize_t */
#include <stdlib.h> 	/* malloc() free() size_t */
#include <assert.h> 	/* assert */
#include <string.h> 	/* memcpy */

#include "cbuff.h" /* CBuffCreate() */

struct cbuff
{
    size_t front;
    size_t size;
    size_t capacity;
    char buffer[1];
};

cbuff_t* CBuffCreate(size_t capacity)
{
	cbuff_t* cbuff = NULL;
	capacity = (DEFAULT_CAP < capacity) ? capacity : DEFAULT_CAP;
	cbuff = (cbuff_t*)malloc(sizeof(cbuff) + (capacity * sizeof(char) - DEFAULT_CAP));
	if(!cbuff)
	{
		return NULL;
	}
	cbuff->front = 0;
    cbuff->size = 0;
    cbuff->capacity = capacity;
    return cbuff;
}

void CBuffDestroy(cbuff_t* cbuff)
{
	assert(cbuff);
	free(cbuff);
	cbuff = NULL;
}


ssize_t CBuffWrite(cbuff_t* cbuff, const void* src, size_t bytes)
{
	size_t amount_write = 0;
	size_t start = 0;
	size_t space_in_end = 0;
	
	assert (cbuff); 
	
	if (src == NULL) 
    {
    	return -1;
    }
	
	amount_write = (bytes < CBuffFreeSpace(cbuff)) ? bytes : CBuffFreeSpace(cbuff);
    start = (cbuff->front + cbuff->size) % cbuff->capacity;
    
    if (amount_write == 0)
	{
		return 0;
	}

    if (start + amount_write <= cbuff->capacity)
    {
        memcpy(cbuff->buffer + start, src, amount_write);
    }
    else
    {
        space_in_end = cbuff->capacity - start;
        memcpy(cbuff->buffer + start, src, space_in_end);
        memcpy(cbuff->buffer, (char *)src + space_in_end, amount_write - space_in_end);
    }

    cbuff->size += amount_write;
    
    return (ssize_t)amount_write;
}


ssize_t CBuffRead(cbuff_t* cbuff, void* dst, size_t bytes)
{
	size_t amount_read = 0;
	size_t space_in_end = 0;
	
    assert(cbuff);
	
	amount_read = (bytes < cbuff->size) ? bytes : cbuff->size;
    
    if (amount_read == 0)
	{
		return 0;
	}
	
    if (dst == NULL) 
    {
    	return -1;
	}
	
    if (cbuff->front + amount_read <= cbuff->capacity)
    {
        memcpy(dst, cbuff->buffer + cbuff->front, amount_read);
    }
    else
    {
        space_in_end = cbuff->capacity - cbuff->front;
        memcpy(dst, cbuff->buffer + cbuff->front, space_in_end);
        memcpy((char *)dst + space_in_end, cbuff->buffer, amount_read - space_in_end);
    }

    cbuff->front = (cbuff->front + amount_read) % cbuff->capacity;
    
    cbuff->size -= amount_read;
    
    return (ssize_t)amount_read;
}

int CBuffIsEmpty(const cbuff_t* cbuff)
{
	assert(cbuff);
	return (cbuff->size == 0);
}


size_t CBuffFreeSpace(const cbuff_t* cbuff)
{
	assert(cbuff);
	return (cbuff->capacity - cbuff->size);
}

size_t CBuffSize(const cbuff_t* cbuff)
{
	assert(cbuff);
	return cbuff->size;
}


