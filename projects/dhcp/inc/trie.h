/************************************
 * Exercise: DHCP server
 * Date: 27/08/25
 * Developer: Baruch Haimson
 * Reviewer: Avi
 * Status: In Progress
 ************************************/

#ifndef __ILRD_TRIE_H__
#define __ILRD_TRIE_H__

#include <stddef.h> /* size_t */

typedef struct Trie trie_t;

trie_t* TrieCreate(int max_depth);
void TrieDestroy(trie_t* trie);
int TrieInsert(trie_t *trie, unsigned int requested_ip, unsigned int *allocated_ip);
int TrieRemove(trie_t *trie, unsigned int ip);
int TrieSearch(trie_t* trie, unsigned int ip);
unsigned int TrieNextFree(trie_t* trie, unsigned int ip);
size_t TrieCountFree(const trie_t* trie);

#endif /* __ILRD_TRIE_H__ */
