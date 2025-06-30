#ifndef _ILRD_VECTOR_
#define _ILRD_VECTOR_

#define DEFAULT_CAPACITY (8)

typedef struct Vector vector_t;


#include <stddef.h>

vector_t* VectorCreate(size_t capacity, size_t element_size);
void VectorDestroy(vector_t* vec);
int VectorPushBack(vector_t* vec ,const void* data);
void VectorPopBack(vector_t* vec);
void* VectorGetAccessToElement(vector_t* vec, size_t index);
size_t VectorSize(const vector_t* vec);
size_t VectorCapacity(const vector_t* vec);
int VectorReserve(vector_t* vec, size_t new_capacity);
void VectorShrink(vector_t* vec);


#endif /* _ILRD_VECTOR_ */
