#include <stdio.h>
#include <string.h>
#include "Exc2.h"

#define IS_LITTLE_ENDIAN()  (*(char*)&(int){1} == 1)

void TestAtoi(const char* str)
{
    int expected;
    int actual;
    expected = atoi(str);
    actual = atoi10(str);
    printf("Test atoi10: '%s' return %d ,expected is: %d\n", str, actual, expected);
}

int main()
{
	const char* a;
	const char* b;
	const char* c;
	char buf[32];
	printf("========Atoi=========\n");
    TestAtoi("123");
    TestAtoi("-42");
    TestAtoi("   +99");
    TestAtoi("0");

	printf("========Itoa=========\n");
    itoa10(0, buf);
    printf("itoa10(0): %s\n", buf);
    itoa10(123, buf);
    printf("itoa10(123): %s\n", buf);
    itoa10(-456, buf);
    printf("itoa10(-456): %s\n", buf);

	printf("========ItoaBase=========\n");
    ItoaBase(37, buf, 36);
    printf("itoa_base(37, 36): %s (expected: 11)\n", buf);
    ItoaBase(255, buf, 16);
    printf("itoa_base(255, 16): %s (expected: FF)\n", buf);
    ItoaBase(10, buf, 2);
    printf("itoa_base(10, 2): %s (expected: 1010)\n", buf);
    ItoaBase(12345, buf, 10);
    printf("itoa_base(12345, 10): %s (expected: 12345)\n", buf);
    ItoaBase(0, buf, 10);
    printf("itoa_base(0, 10): %s (expected: 0)\n", buf);
    ItoaBase(-42, buf, 10);
    printf("itoa_base(-42, 10): %s (expected: -42)\n", buf);
    ItoaBase(-42, buf, 16);
    printf("itoa_base(-42, 16): %s \n", buf);
    
	printf("========IsLittleEndian=========\n");
	a = "abcdefg";
    b = "bdfhij";
    c = "z";
    printf("Expected output: bdf\nActual output: ");
    PrintUniqueChars(a, b, c);

    a = "hello world";
    b = "hold";
    c = "x";
    printf("Expected output: dhlo\nActual output: ");
    PrintUniqueChars(a, b, c);

    a = "ABCabc123";
    b = "abc123";
    c = "3";
    printf("Expected output: abc12\nActual output: ");
    PrintUniqueChars(a, b, c);
	
	printf("========IsLittleEndian=========\n");
	if (IsLittleEndian())
    {
        printf("System is Little Endian\n");
    }
    else
    {
        printf("System is Big Endian\n");
    }
    printf("========IS_LITTLE_ENDIAN_MACRO=========\n");
	if (IS_LITTLE_ENDIAN())
    {
        printf("System is Little Endian (macro)\n");
    }
    else
    {
        printf("System is Big Endian (macro)\n");
    }

    return 0;
}
