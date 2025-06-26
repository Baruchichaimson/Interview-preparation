#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/bit_arr.h"

#define BUFFER_SIZE 65

void TestSetAndGet()
{
    bit_arr_t bits = BitArrSetAllOff(0);
    bits = BitArrSetOn(bits, 0);
    bits = BitArrSetOn(bits, 5);
    bits = BitArrSetOn(bits, 63);

    assert(BitArrGetBit(bits, 0) == 1);
    assert(BitArrGetBit(bits, 5) == 1);
    assert(BitArrGetBit(bits, 63) == 1);

    bits = BitArrSetOff(bits, 5);
    assert(BitArrGetBit(bits, 5) == 0);
}

void TestSetBit()
{
    bit_arr_t bits = BitArrSetAllOff(0);
    bits = BitArrSetBit(bits, 3, 1);
    assert(BitArrGetBit(bits, 3) == 1);
    bits = BitArrSetBit(bits, 3, 0);
    assert(BitArrGetBit(bits, 3) == 0);
}

void TestFlipBit()
{
    bit_arr_t bits = BitArrSetAllOff(0);
    bits = BitArrFlipBit(bits, 4);
    assert(BitArrGetBit(bits, 4) == 1);
    bits = BitArrFlipBit(bits, 4);
    assert(BitArrGetBit(bits, 4) == 0);
}

void TestRotate()
{
    bit_arr_t bits = 1;
    bits = BitArrRotateLeft(bits, 1);
    assert(BitArrGetBit(bits, 1) == 1);
    bits = BitArrRotateRight(bits, 1);
    assert(BitArrGetBit(bits, 0) == 1);
}

void TestCount()
{
    bit_arr_t bits = BitArrSetAllOff(0);
    bits = BitArrSetOn(bits, 0);
    bits = BitArrSetOn(bits, 1);
    bits = BitArrSetOn(bits, 63);
    assert(BitArrCountOn(bits) == 3);
    assert(BitArrCountOff(bits) == 61);
}

void TestMirror()
{
    bit_arr_t bits = 1;
    bit_arr_t mirrored = BitArrMirror(bits);
    assert(BitArrGetBit(mirrored, 63) == 1);
    assert(BitArrGetBit(mirrored, 0) == 0);
}

void TestToString()
{
    bit_arr_t bits = BitArrSetAllOff(0);
    bits = BitArrSetOn(bits, 0);
    bits = BitArrSetOn(bits, 63);
    char buffer[BUFFER_SIZE];
    BitArrToString(bits, buffer);
    assert(buffer[0] == '1');
    assert(buffer[63] == '1');
    assert(buffer[1] == '0');
    assert(buffer[62] == '0');
    assert(buffer[64] == '\0');
}

int main()
{
    TestSetAndGet();
    TestSetBit();
    TestFlipBit();
    TestRotate();
    TestCount();
    TestMirror();
    TestToString();

    printf("All tests passed successfully!\n");
    return 0;
}
