#include <stddef.h>
#include <stdio.h>

void func(int arr[],size_t size, void* index1, void* index2)
{
	*(int*)index1 = arr[2];
    *(int*)index2 = arr[0];
}

int main()
{
	size_t index1;
	size_t index2;
	int arr[] = {1,2,3};
	size_t size = 3;
	func(arr,size, &index1, &index2);
	printf("%ld %ld\n" , index1, index2);
}
