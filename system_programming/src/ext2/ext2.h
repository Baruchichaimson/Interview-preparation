#ifndef __EXT2_H__
#define __EXT2_H__

#include <stddef.h>

int Open(char* device, char* filename); 
int Read(int file_inode, char* buffer, size_t count);

#endif /* __EXT2_H__ */

