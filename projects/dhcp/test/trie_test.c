/************************************
 * Exercise: DHCP server
 * Date: 27/08/25
 * Developer: Baruch Haimson
 * Reviewer: Avi
 * Status: In Progress
 ************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trie.h"

static void TestCreateDestroy(void)
{
    trie_t *trie;

    printf("TestCreateDestroy... ");

    trie = TrieCreate();
    assert(trie);
    TrieDestroy(trie);

    printf("PASSED\n");
}

static void TestInsertAndCount(void)
{
    trie_t *trie;
    unsigned int allocated_ip;
    int res;
    long free_count;

    printf("TestInsertAndCount... ");

    trie = TrieCreate();
    assert(trie);

    allocated_ip = 0;
    res = TrieInsert(trie, 0xC0A80001, &allocated_ip); /* 192.168.0.1 */
    assert(res == 0);
    assert(allocated_ip == 0xC0A80001);

    allocated_ip = 0;
    res = TrieInsert(trie, 0xC0A80001, &allocated_ip); /* same IP again */
    assert(res == 0 || res == -1); /* should allocate same or next free */

    allocated_ip = 0;
    res = TrieInsert(trie, 0xC0A80002, &allocated_ip); /* 192.168.0.2 */
    assert(res == 0);

    free_count = TrieCountFree(trie);
    /* can't be bigger than max IPs */
    assert((unsigned long)free_count <= (1UL << 32));

    TrieDestroy(trie);

    printf("PASSED\n");
}

static void TestRemove(void)
{
    trie_t *trie;
    unsigned int allocated_ip;
    int free_before;
    int free_after;
    int free_final;

    printf("TestRemove... ");

    trie = TrieCreate();
    assert(trie);

    allocated_ip = 0;
    TrieInsert(trie, 0xC0A80001, &allocated_ip);
    TrieInsert(trie, 0xC0A80002, &allocated_ip);

    free_before = TrieCountFree(trie);

    TrieRemove(trie, 0xC0A80001); /* remove 192.168.0.1 */
    free_after = TrieCountFree(trie);
    assert(free_after > free_before); /* free count should increase */

    TrieRemove(trie, 0xC0A80002); /* remove 192.168.0.2 */
    free_final = TrieCountFree(trie);
    assert(free_final > free_after);

    TrieDestroy(trie);

    printf("PASSED\n");
}

static void TestAllocateAllAndFail(void)
{
    trie_t *trie;
    unsigned int allocated_ip;
    int res;
    unsigned int i;

    printf("TestAllocateAllAndFail... ");

    trie = TrieCreate();
    assert(trie);

    allocated_ip = 0;
    res = 0;

    /* allocate 4 IPs (simpler test, not 2^32) */
    for (i = 0; i < 4; i++)
    {
        allocated_ip = 0;
        res = TrieInsert(trie, i, &allocated_ip);
        assert(res == 0);
        assert(allocated_ip == i);
    }

    /* try inserting an already full IP */
    allocated_ip = 0;
    res = TrieInsert(trie, 0, &allocated_ip);
    assert(res == -1 || allocated_ip != 0); /* should fail or give next */

    TrieDestroy(trie);

    printf("PASSED\n");
}

int main(void)
{
    printf("Running Trie tests...\n");

    TestCreateDestroy();
    TestInsertAndCount();
    TestRemove();
    TestAllocateAllAndFail();

    printf("All tests PASSED!\n");
    return 0;
}
