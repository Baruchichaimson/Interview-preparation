#include <stdio.h>

/***************************
 Exercise:  WS3
 Date: 	    05/08/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    Approved
***************************/
enum ExampleEnum { A, B, C };
struct ExampleStruct { int x; float y; };
union ExampleUnion { int i; float f; };

int main() 
{
    printf("Size of char: %zu\n", sizeof(char));
    printf("Size of unsigned char: %zu\n", sizeof(unsigned char));

    printf("Size of short: %zu\n", sizeof(short));
    printf("Size of unsigned short: %zu\n", sizeof(unsigned short));

    printf("Size of int: %zu\n", sizeof(int));
    printf("Size of unsigned int: %zu\n", sizeof(unsigned int));

    printf("Size of long: %zu\n", sizeof(long));
    printf("Size of unsigned long: %zu\n", sizeof(unsigned long));

    printf("Size of long long: %zu\n", sizeof(long long));
    printf("Size of unsigned long long: %zu\n", sizeof(unsigned long long));

    printf("Size of float: %zu\n", sizeof(float));
    printf("Size of double: %zu\n", sizeof(double));
    printf("Size of long double: %zu\n", sizeof(long double));

    printf("Size of _Bool: %zu\n", sizeof(_Bool));
    printf("Size of void*: %zu\n", sizeof(void*));

    printf("Size of enum: %zu\n", sizeof(enum ExampleEnum));
    printf("Size of struct: %zu\n", sizeof(struct ExampleStruct));
    printf("Size of union: %zu\n", sizeof(union ExampleUnion));

    printf("Size of int pointer: %zu\n", sizeof(int*));
    printf("Size of char pointer: %zu\n", sizeof(char*));
    printf("Size of float pointer: %zu\n", sizeof(float*));

    return 0;
}

