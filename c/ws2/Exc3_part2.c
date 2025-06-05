#include <stdio.h>
/**********
 Exercise: 	WS2
 Date: 		05/06/25
 Developer:     Baruch Haimson
 Reviewer: 	Tal Hindi
 Status: 	Approved
 **********/

int contains_digit(int number)
{
    if (number < 0)
        number = -number; 

    while (number > 0)
    {
        if (number % 10 == 7)
            return 1;
        number /= 10;
    }
    return 0;
}

void BOOM(int start, int end)
{
	while(start < end)
	{
		if(start % 7 == 0 || contains_digit(start))
		{
			printf(" BOOM");
		}
		else
		{
			printf(" %d",start);
		}
		start++;
	}
}

int main()
{
	BOOM(-13,17);
	return 0;
}
