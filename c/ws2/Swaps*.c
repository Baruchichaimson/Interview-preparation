#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void SwapSizeTPointers(size_t** a, size_t** b)
{
    size_t* temp = *a;
    *a = *b;
    *b = temp;
}

int main ()
{
	 size_t x = 100;
	 size_t y = 200;
         size_t* px = &x;
         size_t* py = &y;
         printf("Before swap:\n");
         printf("px points to: %zu\n", *px);
         printf("py points to: %zu\n", *py);
         SwapSizeTPointers(&px, &py);
         printf("After swap:\n");
         printf("px points to: %zu\n", *px);
         printf("py points to: %zu\n", *py);
         return 0;
}
