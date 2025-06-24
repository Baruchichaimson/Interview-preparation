#ifndef __EXC1_H__
#define __EXC1_H__

#include <stddef.h>
#include <stdlib.h>

void itoa10(int value, char* str);
int atoi10(const char* str);
void ItoaBase(int value, char* str, int base);
int AtoiBase(const char *str, int base); 
void test_atoi(const char* str);
void run_tests(void);
void PrintUniqueChars(const char* a, const char* b, const char* c);
int IsLittleEndian();

#endif 

