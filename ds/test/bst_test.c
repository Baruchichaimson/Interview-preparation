/*#include <stdio.h>

#include "bst.h"

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


static int action_func(void* data, void* param)
{
    return (*(int*)data == *(int*)param) ? 0 : 1;
}

static int cmp_func(const void* data1, const void* data2)
{
    return (*(int*)data1 - *(int*)data2);
}

void TestCreatDestroyBST(void)
{
    size_t i = 0;
    int values[] = {50, 30, 70, 20, 40, 23, 21, 24,60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    size_t n = sizeof(values) / sizeof(values[0]);
    bst_t* tree = BSTCreate(cmp_func);
    if (!tree)
    {
        printf("BSTCreate failed\n");
        return;
    }
    printf("BSTCreate passed\n");

    for (i = 0; i < n; ++i)
    {
        BSTInsert(tree, &values[i]);
    }

    printf("BSTInsert done\n");

    BSTDestroy(tree);
    printf("BSTDestroy passed\n");
    
}

void TestInsertRemoveBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    int data1 = 10, data2 = 20;
    bst_iter_t iter1, iter2;

    iter1 = BSTInsert(tree, &data1);
    if (iter1.node)
    {
        printf("%d\n", *(int*)BSTGetData(iter1));
        printf("BSTInsert passed for data1\n");
    }
    else
    {
        printf("BSTInsert failed for data1\n");
    }

    iter2 = BSTInsert(tree, &data2);
    if (iter2.node)
    {
        printf("BSTInsert passed for data2\n");
    }
    else
    {
        printf("BSTInsert failed for data2\n");
    }

    BSTRemove(iter1);
    printf("BSTRemove passed for data1\n");

    BSTDestroy(tree);
}

void TestSizeIsEmptyBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    if (BSTIsEmpty(tree))
    {
        printf("BSTIsEmpty passed\n");
    }
    else
    {
        printf("BSTIsEmpty failed\n");
    }

    BSTDestroy(tree);
}

void TestBeginEndBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    bst_iter_t begin = BSTBegin(tree);
    bst_iter_t end = BSTEnd(tree);

    if (begin.node == end.node && end.node->parent == NULL)
    {
        printf("BSTBegin and BSTEnd passed\n");
    }
    else
    {
        printf("BSTBegin or BSTEnd failed\n");
    }

    BSTDestroy(tree);
}

void TestNextPrevBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    int data1 = 10, data2 = 20;
    bst_iter_t iter1, iter2;
    bst_iter_t next_iter, prev_iter;

    iter1 = BSTInsert(tree, &data1);
    iter2 = BSTInsert(tree, &data2);

    next_iter = BSTNext(iter1);
    if (BSTIterIsSame(next_iter, iter2))
    {
        printf("BSTNext passed\n");
    }
    else
    {
        printf("BSTNext failed\n");
    }

    prev_iter = BSTPrev(iter2);
    if (BSTIterIsSame(prev_iter, iter1))
    {
        printf("BSTPrev passed\n");
    }
    else
    {
        printf("%d\n", *(int*)BSTGetData(prev_iter));
        printf("%d\n", *(int*)BSTGetData(iter1));
        printf("BSTPrev failed\n");
    }

    BSTDestroy(tree);
}

void TestIterIsSameBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    int data1 = 10, data2 = 20;
    bst_iter_t iter1, iter2;

    iter1 = BSTInsert(tree, &data1);
    iter2 = BSTInsert(tree, &data2);

    if (BSTIterIsSame(iter1, iter1) && !BSTIterIsSame(iter1, iter2))
    {
        printf("BSTIterIsSame passed\n");
    }
    else
    {
        printf("BSTIterIsSame failed\n");
    }

    BSTDestroy(tree);
}

void TestGetDataBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    int data1 = 10, data2 = 20;
    bst_iter_t iter1, iter2;

    iter1 = BSTInsert(tree, &data1);
    iter2 = BSTInsert(tree, &data2);

    if (*(int*)BSTGetData(iter1) == data1 && *(int*)BSTGetData(iter2) == data2)
    {
        printf("BSTGetData passed\n");
    }
    else
    {
        printf("BSTGetData failed\n");
    }

    BSTDestroy(tree);
}

void TestFindBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    int data1 = 10, data2 = 20;
    bst_iter_t iter1, iter2;
    bst_iter_t found_iter = {NULL};


    iter1 = BSTInsert(tree, &data1);
    iter2 = BSTInsert(tree, &data2);

    found_iter = BSTFind(tree, &data1);
    if (BSTIterIsSame(iter1, found_iter))
    {
        printf("BSTFind passed for data1\n");
    }
    else
    {
        printf("BSTFind failed for data1\n");
    }

    found_iter = BSTFind(tree, &data2);
    if (BSTIterIsSame(iter2, found_iter))
    {
        printf("BSTFind passed for data2\n");
    }
    else
    {
        printf("BSTFind failed for data2\n");
    }

    BSTDestroy(tree);
}

void TestForEachBST(void)
{
    bst_t* tree = BSTCreate(cmp_func);
    int data1 = 10, data2 = 20, param = 10;
    bst_iter_t iter1, iter2;

    iter1 = BSTInsert(tree, &data1);
    iter2 = BSTInsert(tree, &data2);

    if (BSTForEach(iter1, iter2, action_func, &param) == 0)
    {
        printf("BSTForEach passed\n");
    }
    else
    {
        printf("BSTForEach failed\n");
    }

    BSTDestroy(tree);
}

void TestRemoveBST(void)
{
    int vals[] = {50, 30, 70, 20, 40, 60, 80, 65};
    size_t n = sizeof(vals) / sizeof(vals[0]);
    bst_t *tree = BSTCreate(cmp_func);
    bst_iter_t it;
    size_t i;
    int val81 = 81;

    printf("\n--- TestRemoveBST ---\n");

    for (i = 0; i < n; ++i)
    {
        BSTInsert(tree, &vals[i]);
    }
    printf("Inserted %lu elements\n", (unsigned long)n);

    it = BSTFind(tree, &vals[7]);
    if (!BSTIterIsSame(it, BSTEnd(tree)))
    {
        BSTRemove(it);
        printf("Removed leaf 65 — Size: %lu\n", (unsigned long)BSTSize(tree));
    }
    else
    {
        printf("ERROR: Leaf 65 not found\n");
    }

    BSTInsert(tree, &val81);
    it = BSTFind(tree, &vals[6]); 
    BSTRemove(it);
    printf("Removed node 80 (had 1 child) — Size: %lu\n", (unsigned long)BSTSize(tree));

    it = BSTFind(tree, &vals[1]); 
    BSTRemove(it);
    printf("Removed node 30 (2 children) — Size: %lu\n", (unsigned long)BSTSize(tree));

    it = BSTFind(tree, &vals[0]); 
    BSTRemove(it);
    printf("Removed root 50 — Size: %lu\n", (unsigned long)BSTSize(tree));

    while (!BSTIsEmpty(tree))
    {
        it = BSTBegin(tree);
        printf("Removing %d\n", *(int*)BSTGetData(it));
        BSTRemove(it);
    }
    printf("Tree is empty: %s\n", BSTIsEmpty(tree) ? "YES" : "NO");

    BSTDestroy(tree);
}


int main()
{
    TestCreatDestroyBST();
    TestInsertRemoveBST();
    TestSizeIsEmptyBST();
    TestBeginEndBST();
    TestNextPrevBST();
    TestIterIsSameBST();
    TestGetDataBST();
    TestFindBST();
    TestForEachBST();
    TestRemoveBST();

    return 0;
}*/

#include <stdio.h>
#include <assert.h>
#include <time.h>   /* rime */ 
#include "bst.h"

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define MIN(a,b)		(((a) > (b)) ? (b) : (a))
#define SIZE	(200)
struct bst_node
{
    bst_node_t* parent;
    bst_node_t* children[2];
    void* data;
};

struct bst
{
    bst_node_t root_stub;    
    cmp_func_t cmp;
};

/* global vars */
static int global_result = 1;
static int current_test = 1; 
static char* TestPrintStr = "";
static int arr[10] = {0,10,20,30,40,50,60,70,80,90};
static int arr_rand[SIZE] = {0};

/* helper funcs */
static int PrintResults(int result, char* test_info);
static void PrintTestResults(void);

/* action funcs */
static int CmpInts(const void* data1, const void* data2);
static int IsTreeLegit(bst_t* tree);
static int ActionPrintInt(void* data, void* param);
static int ActionAddInt(void* data, void* param);

/* test funcs */
static void Test1(void);
static void Test2(void);
static void Test3(void);
static void Test4(void);


int main()
{
	srand(time(NULL));
	Test1();
	Test2();
	Test3();
	Test4();
	
	PrintResults(global_result," ALL TESTS");

	return 0;
}
/****************************************/
/*	STATIC TEST FUNCS		*/
/****************************************/

static void Test4(void)
{
	bst_t* bst = BSTCreate(&CmpInts);		
	bst_iter_t iter = {NULL};
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t next = 0;
	current_test = 1;
	
	printf("#### TEST 4\n");
	TestPrintStr = "TEST 4";
	for (k = 0; k < 10; ++k)
	{
		for (i = 0; i < SIZE; ++i)
		{
			arr_rand[i] = rand();
			BSTInsert(bst,arr_rand + i);
		}
		
		BSTRemove(BSTPrev(BSTEnd(bst)));
		BSTRemove(BSTBegin(bst));
		
		for (i = 0; i < SIZE -2; ++i)
		{
			if (i % 10 == 0)
			{
				current_test = MIN(current_test, IsTreeLegit(bst));
			}
			
			iter = BSTBegin(bst);
			next = rand() % (SIZE - i - 2);
			for (j = 0; j < next; ++j)
			{
				iter = BSTNext(iter);
			}
			
			BSTRemove(iter);
		}
	}
			
	PrintResults(BSTIsEmpty(bst),"empty tree");
	PrintResults(current_test, "Tree was ordered all the way");
	BSTDestroy(bst);
	
	PrintTestResults();
}


static void Test3(void)
{
	bst_t* bst = BSTCreate(&CmpInts);	
	bst_iter_t iter = BSTBegin(bst);
	int x = 2;
	current_test = 1;
	
	printf("#### TEST 3\n");
	TestPrintStr = "TEST 3";
	printf("inserting 10 elements...\n");
	
	BSTInsert(bst, arr+1);
	BSTInsert(bst, arr);
	BSTInsert(bst, arr+6);
	BSTInsert(bst, arr+2);
	BSTInsert(bst, arr+5);
	BSTInsert(bst, arr+3);
	BSTInsert(bst, arr+4);
	BSTInsert(bst, arr+8);
	BSTInsert(bst, arr+7);
	BSTInsert(bst, arr+9);
	
	PrintResults(IsTreeLegit(bst), "tree is ordered");
	printf("printing tree:\n");
	BSTForEach(BSTBegin(bst), BSTEnd(bst), &ActionPrintInt, "before");
	BSTForEach(BSTBegin(bst), BSTEnd(bst), &ActionAddInt, &x);	
	printf("\n");
	BSTForEach(BSTBegin(bst), BSTEnd(bst), &ActionPrintInt, "after");

	printf("removing...\n");
	
	iter = BSTBegin(bst);
	iter = BSTNext(BSTNext(BSTNext(iter)));
	BSTRemove(iter);
	PrintResults(IsTreeLegit(bst), "removed a node");

	iter = BSTBegin(bst);
	iter = BSTNext(iter);
	BSTRemove(iter);
	PrintResults(IsTreeLegit(bst), "removed a node");

	BSTForEach(BSTBegin(bst), BSTEnd(bst), &ActionPrintInt, "");
	PrintResults(BSTSize(bst), "size = 8");
	
	BSTDestroy(bst);

	PrintResults(1, "destroyed (check vlg)");	
	
	PrintTestResults();
}


static void Test2(void)
{
	bst_t* bst = BSTCreate(&CmpInts);	
	bst_iter_t iter = BSTBegin(bst);
	current_test = 1;
	printf("#### TEST 2\n");
	TestPrintStr = "TEST 2";
	
	iter = BSTInsert(bst, arr+1);
	iter = BSTInsert(bst, arr);
	
	PrintResults(arr == BSTGetData(iter), "new node inserted");	
	PrintResults(!BSTIsEmpty(bst), "!IsEmpty");
	PrintResults((2 == BSTSize(bst)), "size = 2");
	PrintResults(BSTIterIsSame(iter, BSTFind(bst,arr)), "found: arr ");
	
	BSTDestroy(bst);

	PrintResults(1, "destroyed (check vlg)");	
	
	PrintTestResults();
}

static void Test1(void)
{
	bst_t* bst = BSTCreate(&CmpInts);		
	current_test = 1;
	printf("#### TEST 1\n");
	TestPrintStr = "TEST 1";
	
	PrintResults((NULL != bst), "creating a bst!");
	PrintResults(BSTIsEmpty(bst), "IsEmpty");
	PrintResults((0 == BSTSize(bst)), "size = 0");
	
	BSTDestroy(bst);
	
	PrintTestResults();
}

/****************************************/
/*	STATIC HELPER FUNCS		*/
/****************************************/

static void PrintTestResults(void)
{
	if (current_test)
	{
		printf(GREEN"============ PASSED ALL TEST IN %s ============"RESET"\n\n", TestPrintStr);
	}
	else
	{
		printf(RED"============ FAILED SOME TEST IN %s ============"RESET"\n\n", TestPrintStr);	
	}
}

static int PrintResults(int result, char* test_info)
{
	if (result)
	{
		printf(GREEN"Passed %s"RESET"\n",test_info);
	}
	else
	{
		global_result = 0;
		current_test = 0;
		printf(RED"Failed %s"RESET"\n",test_info);		
	}
	
	return result;
}

static int CmpInts(const void* data1, const void* data2)
{
	assert(data1);
	assert(data2);
	
	return *(int*)data1 - *(int*)data2;
}

static int ActionPrintInt(void* data, void* param)
{
	assert(data);
	assert(param);
	
	printf("%d %s\n", *(int*)data, (char*)param);
	return 0;
}

static int ActionAddInt(void* data, void* param)
{
	*(int*)data += *(int*)param;
	return 0;
}

static int IsTreeLegit(bst_t* tree)
{
	bst_iter_t iter = {NULL};
	bst_iter_t next = {NULL}; 
	
	assert(tree);

	iter = BSTBegin(tree);
	
	while ((NULL != iter.node->parent) && (NULL != (BSTNext(iter)).node->parent))
	{
		next = BSTNext(iter);
		
		if (0 < tree->cmp(iter.node->data, next.node->data))
		{
			return 0;
		}
		
		iter = next;
	}
	
	return 1;
}


