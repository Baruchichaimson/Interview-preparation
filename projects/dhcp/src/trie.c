/************************************
 * Exercise: DHCP server
 * Date: 27/08/25
 * Developer: Baruch Haimson
 * Reviewer: Avi
 * Status: In Progress
 ************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "trie.h" /* trie_t */

typedef struct TrieNode 
{
    struct TrieNode* children[2];
    int is_full;
    size_t free_count;
} trie_node_t;

struct Trie 
{
    trie_node_t* root;
    int max_depth;
};

/* ================ helper functions ======================================= */

static trie_node_t* NodeCreate(int depth, int max_depth);
static void TrieDestroyRec(trie_node_t* node);
static void UpdateNode(trie_node_t* node, int depth, int max_depth);
static int TrieInsertRec(trie_node_t *node, unsigned int ip, int depth, unsigned int *allocated_ip, int max_depth);
static int TrieRemoveRec(trie_node_t *node, unsigned int ip, int depth, int max_depth);
static int TrieSearchRec(trie_node_t *node, int depth, unsigned int ip, int max_depth);

/* ========================================================================== */

trie_t* TrieCreate(int max_depth) 
{
    trie_t* trie = NULL;

    trie = (trie_t*)malloc(sizeof(trie_t));
    if (!trie) 
    {
        return NULL;
    }

    trie->max_depth = max_depth;
    trie->root = NodeCreate(0, max_depth);
    if (!trie->root) 
    {
        free(trie);
        return NULL;
    }

    return trie;
}

void TrieDestroy(trie_t* trie) 
{
    assert(trie);

    TrieDestroyRec(trie->root);
    free(trie);
}

int TrieInsert(trie_t *trie, unsigned int requested_ip, unsigned int *allocated_ip) 
{
    assert(trie);
    assert(allocated_ip);

    return TrieInsertRec(trie->root, requested_ip, 0, allocated_ip, trie->max_depth);
}

int TrieRemove(trie_t *trie, unsigned int ip) 
{
    assert(trie);

    return TrieRemoveRec(trie->root, ip, 0, trie->max_depth);
}

int TrieSearch(trie_t* trie, unsigned int ip) 
{
    assert(trie);

    return TrieSearchRec(trie->root, 0, ip, trie->max_depth);
}

unsigned int TrieNextFree(trie_t* trie, unsigned int start_host)
{
    unsigned int max = (1U << trie->max_depth) - 1;
    unsigned int host;

    for (host = start_host; host <= max; ++host)
    {
        if (!TrieSearch(trie, host))
        {
            return host;
        }
    }

    return 0;
}

size_t TrieCountFree(const trie_t *trie) 
{
    assert(trie);
    
    return trie->root->free_count;
}

/* ================ helper functions ======================================= */

static trie_node_t* NodeCreate(int depth, int max_depth) 
{
    trie_node_t* node = NULL;

    node = (trie_node_t*)malloc(sizeof(trie_node_t));
    if (!node) 
    {
        return NULL;
    }

    node->children[0] = NULL;
    node->children[1] = NULL;
    node->is_full = 0;
    node->free_count = 1U << (max_depth - depth);

    return node;
}

static void TrieDestroyRec(trie_node_t* node) 
{
    if (!node) 
    {
        return;
    }

    TrieDestroyRec(node->children[0]);
    TrieDestroyRec(node->children[1]);

    free(node);
}

static void UpdateNode(trie_node_t* node, int depth, int max_depth) 
{
    size_t i = 0;
    size_t child_subtree_size = 0;
    node->free_count = 0;
    node->is_full = 1;
    
    if (depth == max_depth) 
    {
        if (node->is_full) 
        {
            node->free_count = 0;
        } 
        else 
        {
            node->free_count = 1;
        }
        return;
    }
    
    child_subtree_size = 1U << (max_depth - depth - 1);
    
    for (i = 0; i < 2; ++i) 
    {
        if (node->children[i]) 
        {
            node->free_count += node->children[i]->free_count;

            if (!node->children[i]->is_full) 
            {
                node->is_full = 0;
            }
        } 
        else 
        {
            node->free_count += child_subtree_size;
            node->is_full = 0;
        }
    }
}

static int TrieInsertRec(trie_node_t *node, unsigned int ip, int depth, unsigned int *allocated_ip, int max_depth) 
{
    int bit = 0;
    
    if (node->is_full) 
    {
        return 0;
    }
    
    if (depth == max_depth) 
    {
        node->is_full = 1;
        node->free_count = 0;
        *allocated_ip = ip;
        return 1;
    }

    bit = (ip >> (max_depth - 1 - depth)) & 1;
    
    if (!node->children[bit]) 
    {
        node->children[bit] = NodeCreate(depth + 1, max_depth);

        if (!node->children[bit]) 
        {
            return 0;
        }
    }

    if (TrieInsertRec(node->children[bit], ip, depth + 1, allocated_ip, max_depth)) 
    {
        UpdateNode(node, depth, max_depth);
        return 1;
    }

    return 0;
}

static int TrieRemoveRec(trie_node_t *node, unsigned int ip, int depth, int max_depth) 
{
    int bit = 0;
    int removed = 0;
    
    if (!node) 
    {
        return 0;
    }
    
    if (depth == max_depth) 
    {
        if (node->is_full) 
        {
            node->is_full = 0;
            node->free_count = 1;
            return 1;
        }
        return 0;  
    }

    bit = (ip >> (max_depth - 1 - depth)) & 1;

    if (!node->children[bit]) 
    {
        return 0;
    }

    removed = TrieRemoveRec(node->children[bit], ip, depth + 1, max_depth);

    if (removed) 
    {
        UpdateNode(node, depth, max_depth);
    }
    
    return removed;
}

static int TrieSearchRec(trie_node_t *node, int depth, unsigned int ip, int max_depth) 
{
    int bit = 0;
    
    if (!node) 
    {
        return 0;
    }
    
    if (depth == max_depth) 
    {
        return node->is_full;
    }

    bit = (ip >> (max_depth - 1 - depth)) & 1;

    return TrieSearchRec(node->children[bit], depth + 1, ip, max_depth);
}