#include <stdio.h>

int Palindrom(char* str, size_t size)
{
    char* p = str;
    char* q = str + size - 1;

    while (p < q)
    {
        if (*p != *q)
        {
            printf("is not palindrome\n");
            return 0;
        }
        p++;
        q--;
    }

    printf("is palindrome\n");
    return 0;
}

int main()
{
    char word1[] = "radar";
    char word2[] = "hello";

    Palindrom(word1, sizeof(word1) - 1); 
    Palindrom(word2, sizeof(word2) - 1);

    return 0;
}

