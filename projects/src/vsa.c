#include <aassert.h>

#define ALIGN_UP(x)  (((x) + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1))

struct VSA 
{
	void* end_pool;
}vsa_t;

struct Header
{
	long block_size;
	#ifndef NDEBUG
		size_t magic_number;	
	#endif
}header_t;


vsa_t* VSAInit(void* pool, size_t pool_size)
{
	vsa_t* vsa = (vsa_t*)pool;
	vsa_t* vsaAligen = ALIGNEUP(vsa);
	
	header_t* header = (header_t*)(vsaAligen + sizeof(vsa_t));
	
	vsaAligen->end_pool = (char*)vsaAligen + pool_size;

	header->block_size = pool_size - (sizeof(vsaAligen) + sizeof(header));
	#ifndef NDEBUG
		header->magic_number = 0;
	#endif
	
	return vsaAligen;
}

void* VSAAlloc(vsa_t* vsa, size_t block_size)
{
	while(header->block_size < block_size)
	{
		
	}
	header->block_size = pool_size - (sizeof(pool) + sizeof(header) + block_size);
}

void VSAFree(void* block)
{

}

size_t VSALargestChunkAvailable(vsa_t* vsa)
{

}
