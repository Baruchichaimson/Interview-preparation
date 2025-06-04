#include <stdio.h>


int contains_digit(int number, int digit)
{
    if (digit < 0 || digit > 9)
        return 0; 

    if (number < 0)
        number = -number; 

    while (number > 0)
    {
        if (number % 10 == digit)
            return 1;
        number /= 10;
    }
    return 0;
}

void BOOM(int start, int end)
{
	while(start < end)
	{
		if(start % 7 != 0 || (!contains_digit(start, 7)))
		{
			printf(" %d",start);
		}
		else
		{
			printf(" BOOM");
		}
		start++;
	}
}

int main()
{
	BOOM(1,10);
	return 0;
}
