#include <stdio.h>
#include "strings1.h"
#include <assert.h>

int main()
{
    const char* Nullable = NULL;
    assert(StrLen("baruch haimson") == 14);
    assert(StrLen("") == 0);
    assert(StrLen(Nullable) == 0);
    printf("All the test passed successfully!\n");
    return 0;
}
