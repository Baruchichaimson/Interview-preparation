#include <stdio.h>

void CopyArray (int arr[], size_t size, int newArr[])
{
	for(size_t i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
}

int main()
{
	int arr[] =  {1,2,3,4,5};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	int newArr[size];
	CopyArray(arr, size, newArr);
	printf("newArr is = ");
	for (size_t i = 0; i < size; ++i)
	{
		printf("%d", newArr[i]);
	}
}
