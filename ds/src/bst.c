/**************************************
Exercise: BST
Date: 07/08/2025
Developer: Baruchi haimson
Reviewer: guy
Status: Developing
**************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */ 

#include "bst.h" /* bst_iter_t */

/******************** helper functions ********************/

static void swap(void* data1, void* data2);
static bst_iter_t NodeToIter(bst_node_t* node);
static bst_node_t* IterToNode(bst_iter_t iter);
static int IsEnd(bst_iter_t iter);
static bst_node_t* CreateNode(void* data);

/*********************************************************/

typedef enum child_node_pos
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
} child_node_pos_t;

struct bst_node
{
    bst_node_t* parent;
    bst_node_t* children[NUM_OF_CHILDREN];
    void* data;
};

struct bst
{
    bst_node_t root_stub;    
    cmp_func_t cmp;
};

bst_t* BSTCreate(cmp_func_t cmp)
{
    bst_t* tree = NULL;

    assert(cmp);

    tree = (bst_t*)malloc(sizeof(bst_t));
    if (!tree)
    {
        return NULL;
    }

    tree->root_stub.parent = NULL;
    tree->root_stub.children[LEFT] = NULL;
    tree->root_stub.children[RIGHT] = NULL;
    tree->root_stub.data = NULL;
    tree->cmp = cmp;

    return tree;
}

void BSTDestroy(bst_t* tree)
{
    bst_node_t* current = tree->root_stub.children[LEFT];
    bst_node_t* parent = NULL;

    assert(tree);

    while (!BSTIsEmpty(tree))
    {
        while (current->children[LEFT] != NULL)
        {
            current = current->children[LEFT];
        }

        parent = current->parent;

        if (parent->children[LEFT] == current)
        {
            parent->children[LEFT] = NULL;
        }
        else if (parent->children[RIGHT] == current)
        {
            parent->children[RIGHT] = NULL;
        }

        free(current);

        current = parent;

        if (current->children[RIGHT] != NULL)
        {
            current = current->children[RIGHT];
        }
    }
    free(tree);
}

bst_iter_t BSTInsert(bst_t* tree, void* data)
{
    bst_node_t* new_node = NULL;
    bst_node_t* parent = &tree->root_stub;
    bst_node_t* current = tree->root_stub.children[LEFT];

    int status = 0;

    assert(tree);
    assert(data);

    new_node = CreateNode(data);
    if (!new_node)
    {
        return NodeToIter(NULL);
    }

    if (BSTIsEmpty(tree))
    {
        tree->root_stub.children[LEFT] = new_node;
        new_node->parent = &tree->root_stub;
        return NodeToIter(new_node);
    }

    while (current != NULL)
    {
        parent = current;

        status = tree->cmp(data, current->data);

        assert(status);

        current = current->children[status > 0];
    }

    new_node->parent = parent;

    parent->children[tree->cmp(data, parent->data) > 0] = new_node;

    return NodeToIter(new_node);
}

void BSTRemove(bst_iter_t to_remove)
{
    bst_iter_t target = to_remove;
    bst_iter_t successor = {NULL};
    bst_node_t *parent = NULL;
    bst_node_t *child = NULL;

    assert(to_remove.node);

    if (IsEnd(to_remove))
    {
        return;
    }

    if (to_remove.node->children[LEFT] && to_remove.node->children[RIGHT])
    {
        successor = BSTNext(to_remove);
        swap(to_remove.node->data, successor.node->data);
        target = successor; 
    }

    child = target.node->children[LEFT] ? target.node->children[LEFT] : target.node->children[RIGHT];
    parent = target.node->parent;

    if (parent->children[LEFT] == target.node)
    {
        parent->children[LEFT] = child;
    }
    else
    {
        parent->children[RIGHT] = child;
    }

    if (child)
    {
        child->parent = parent;
    }

    free(target.node);
}


size_t BSTSize(const bst_t* tree)
{   
    size_t size = 0;
    bst_iter_t iter = BSTBegin(tree);
    
    assert(tree);

    while (!BSTIterIsSame(iter, BSTEnd(tree)))
    {
        size++;
        iter = BSTNext(iter);
    }

    return size;
}

int BSTIsEmpty(const bst_t* tree)
{
    assert(tree);

    return (tree->root_stub.children[LEFT] == NULL);
}

bst_iter_t BSTBegin(const bst_t* tree)
{
    bst_node_t* current = NULL;

    assert(tree);

    current = tree->root_stub.children[LEFT];

    if(NULL == current)
    {
        return BSTEnd(tree);
    }

    while (current->children[LEFT])
    {
        current = current->children[LEFT];
    }

    return NodeToIter(current);
}

bst_iter_t BSTEnd(const bst_t* tree)
{
    assert(tree);
    return NodeToIter((bst_node_t*)&tree->root_stub);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
    bst_node_t* prev = NULL;

    assert(IterToNode(iter));

    prev = IterToNode(iter);

    if(prev->children[LEFT])
    {
        prev = prev->children[LEFT];
        while (prev->children[RIGHT])
        {
            prev = prev->children[RIGHT];
        }
    }
    else 
    {
        while (prev->parent && prev->parent->children[RIGHT] != prev)
        {
            prev = prev->parent;
        }
        prev = prev->parent;
    }
    return NodeToIter(prev);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
    bst_node_t* next = NULL;

    assert(IterToNode(iter));
    if (IsEnd(iter))
    {
        return iter;
    }

    next = iter.node;
    
    if(iter.node->children[RIGHT])
    {
        next = iter.node->children[RIGHT];
        while (next->children[LEFT])
        {
            next = next->children[LEFT];
        }
    }
    else 
    {
        while (iter.node->parent && iter.node->parent->children[LEFT] != iter.node)
        {
            iter = NodeToIter(iter.node->parent);
        }
        next = iter.node->parent;
    }
    return NodeToIter(next);
}

int BSTIterIsSame(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(IterToNode(iter1));
    assert(IterToNode(iter2));

    return IterToNode(iter1) == IterToNode(iter2);
}

void* BSTGetData(bst_iter_t iter)
{
    assert(IterToNode(iter));

    return IterToNode(iter)->data;
}

bst_iter_t BSTFind(const bst_t* bst, void* to_find)
{
    int cmp_result = 0;
    bst_node_t* current = bst->root_stub.children[LEFT];

    assert(bst);
    assert(to_find);

    while (current)
    {
        cmp_result = bst->cmp(to_find, current->data);
        if (cmp_result == 0)
        {
            return NodeToIter(current);
        }
        else if (cmp_result < 0)
        {
            current = current->children[LEFT];
        }
        else
        {
            current = current->children[RIGHT];
        }
    }

    return NodeToIter(NULL);
}

int BSTForEach(bst_iter_t from, bst_iter_t to, int(*action_func)(void* data, void* param), void* param)
{
    assert(IterToNode(from));
    assert(IterToNode(to));
    assert(action_func);

    while (!BSTIterIsSame(from, to))
    {
        if (action_func(BSTGetData(from), param) != 0)
        {
            return -1;
        }
        from = BSTNext(from);
    }
    return 0;
}

/******************** helper functions ********************/

static bst_node_t* CreateNode(void* data)
{
    bst_node_t* node = NULL;

    node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (!node)
    {
        return NULL;
    }

    node->data = data;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->parent = NULL;

    return node;
}

static bst_node_t* IterToNode(bst_iter_t iter)
{
    return iter.node;
}

static bst_iter_t NodeToIter(bst_node_t* node)
{
    bst_iter_t iter;
    iter.node = node;
    return iter;
}

static int IsEnd(bst_iter_t iter)
{
	return (NULL == IterToNode(iter)->parent);
}

static void swap(void* data1, void* data2)
{
    int temp = *(int*)data1;
    *(int*)data1 = *(int*)data2;
    *(int*)data2 = temp;
}

