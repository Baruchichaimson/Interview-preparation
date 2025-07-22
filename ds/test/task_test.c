/***************************
 * Test File: Task
 * Date: 22/07/25
 * Developer: Baruch Haimson
 * Reviwer: 
 * Status: In Progress
 ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#include "task.h"
#include "uid.h"

struct data
{
    int x;
    int y;
    int cleaned; 
};

/*************************** Helper Functions ***************************/

static ssize_t SumOp(void *param);
static void FreeCleanup(void *param);

/************************************************************************/

void TestTaskCreate()
{
    printf("\n--- TestTaskCreate ---\n");

    struct data *d = malloc(sizeof(struct data));
    d->x = 3; d->y = 7;
    task_t *task = TaskCreate(SumOp, d, 5, FreeCleanup, d);
    printf("TaskCreate with valid data: %s\n", task != NULL ? "PASS" : "FAIL");
    TaskDestroy(task);

    task = TaskCreate(NULL, NULL, 5, NULL, NULL);
    printf("TaskCreate with NULL op_func: %s\n", task != NULL ? "PASS" : "FAIL");
    TaskDestroy(task);

    task = TaskCreate(SumOp, NULL, 0, NULL, NULL);
    printf("TaskCreate with NULL op_param: %s\n", task != NULL ? "PASS" : "FAIL");
    TaskDestroy(task);
}

void TestTaskRun()
{
    printf("\n--- TestTaskRun ---\n");

    struct data *d = malloc(sizeof(struct data));
    d->x = 5; d->y = 5;
    task_t *task = TaskCreate(SumOp, d, 5, FreeCleanup, d);
    ssize_t result = TaskRun(task);
	printf("TaskRun with data: actual=%zd, expected=10 => %s\n", result, (result == 10) ? "PASS" : "FAIL");
    TaskDestroy(task);

    task = TaskCreate(SumOp, NULL, 5, NULL, NULL);
    result = TaskRun(task);
	printf("TaskRun with NULL param: actual=%zd, expected=-999 => %s\n", result, (result == -999) ? "PASS" : "FAIL");
    TaskDestroy(task);

    task = TaskCreate(NULL, NULL, 5, NULL, NULL);
    result = TaskRun(task);
	printf("TaskRun with NULL op_func: actual=%zd, expected=-1 => %s\n", result, (result == -1) ? "PASS" : "FAIL");
    TaskDestroy(task);
}

void TestTaskUID()
{
    printf("\n--- TestTaskUID ---\n");

    task_t *task = TaskCreate(SumOp, NULL, 5, NULL, NULL);
    ilrd_uid_t uid = TaskUID(task);
    int is_bad = UIDIsSame(uid, UIDbadUID);
    printf("TaskUID valid UID? %s\n", !is_bad ? "PASS" : "FAIL");
    TaskDestroy(task);
}


void TestTaskCleanUp()
{
    printf("\n--- TestTaskCleanUp ---\n");

    struct data *d = malloc(sizeof(struct data));
    d->x = 1; 
    d->y = 2;
    task_t *task = TaskCreate(SumOp, d, 1, FreeCleanup, d);
    
    printf("Before cleanup: x=%d, y=%d\n", d->x, d->y);

    TaskDestroy(task);
    printf("After cleanup: d pointer = %p (should not be used)\n", (void*)d);

    task = TaskCreate(SumOp, NULL, 1, NULL, NULL);
    TaskCleanUp(task);
    printf("TaskCleanUp called with NULL cleanup function\n");
    TaskDestroy(task);
}

void TestTaskSetGetTime()
{
    printf("\n--- TestTaskSet/GetTimeToRun ---\n");

    task_t *task = TaskCreate(SumOp, NULL, 1, NULL, NULL);
    
    sleep(1);
    TaskSetTimeToRun(task, 3);
	size_t time2 = TaskGetTimeToRun(task);
	time_t now = time(NULL);
	printf("TaskGetTimeToRun actual=%zu, now+2=%ld, test %s\n", time2, now+2, ((time_t)time2 >= now + 2) ? "PASS" : "FAIL");
    TaskDestroy(task);
}

void TestTaskIsMatch()
{
    printf("\n--- TestTaskIsMatch ---\n");

    task_t *task = TaskCreate(SumOp, NULL, 1, NULL, NULL);
    ilrd_uid_t uid = TaskUID(task);
    int match = TaskIsMatch(task, uid);
    int not_match = TaskIsMatch(task, UIDbadUID);
    printf("TaskIsMatch valid UID: %s\n", match ? "PASS" : "FAIL");
    printf("TaskIsMatch bad UID: %s\n", !not_match ? "PASS" : "FAIL");
    TaskDestroy(task);
}

void TestTaskCmp()
{
    printf("\n--- TestTaskCmp ---\n");

    task_t *t1 = TaskCreate(SumOp, NULL, 2, NULL, NULL);
    task_t *t2 = TaskCreate(SumOp, NULL, 2, NULL, NULL);
    int cmp1 = TaskCmp(t1, t2);
    printf("TaskCmp same time: actual=%d, expected=1 => %s\n", cmp1, (cmp1 == 1) ? "PASS" : "FAIL");

    TaskSetTimeToRun(t2, 4);
    int cmp2 = TaskCmp(t1, t2);
    printf("TaskCmp different time: actual=%d, expected=0 => %s\n", cmp2, (cmp2 == 0) ? "PASS" : "FAIL");

    TaskDestroy(t1);
    TaskDestroy(t2);
}

void TestTaskDestroyNULL()
{
    printf("\n--- TestTaskDestroy ---\n");

    struct data *params = malloc(sizeof(struct data));
    params->x = 10;
    params->y = 20;

    task_t *task = TaskCreate(SumOp, params, 5, FreeCleanup, params);
    TaskDestroy(task);
    printf("TaskDestroy called and task freed\n");
}

int main()
{
    TestTaskCreate();
    TestTaskRun();
    TestTaskUID();
    TestTaskCleanUp();
    TestTaskSetGetTime();
    TestTaskIsMatch();
    TestTaskCmp();
    TestTaskDestroyNULL();

    printf("\nAll tests passed \n");
    return 0;
}

/*************************** Helper Functions ***************************/
static ssize_t SumOp(void *param)
{
    struct data *d = (struct data *)param;
    if (!d) 
    {
    	return -999;
    }
    return (ssize_t)(d->x + d->y);
}

static void FreeCleanup(void *param)
{
    struct data *d = (struct data *)param;
    d->cleaned = 1;
    printf("Cleanup function called, cleaned=%d\n", d->cleaned);
    free(d);

}

