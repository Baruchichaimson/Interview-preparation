#include <stdio.h>

void Swap (int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int a = 5;
	int b = 7;
	Swap(&a, &b);
        printf("a = %d, b = %d\n", a, b);
	return 0;
}
