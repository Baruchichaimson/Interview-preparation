/***************************
 * Test File: Task
 * Date: 22/07/25
 * Developer: Baruch Haimson
 * Reviwer: 
 * Status: In Progress
 ***************************/
 
#ifndef ILRD_TASK_H
#define ILRD_TASK_H

#include <sys/types.h> /* ssize_t */
#include "uid.h" /* ilrd_uid_t */

typedef struct task task_t;

task_t* TaskCreate(ssize_t (*op_func)(void *param),  void *op_param,size_t interval_in_sec,void (*cleanup_func)(void* param),void* cleanup_param);

void TaskDestroy(task_t* task);
ilrd_uid_t TaskUID(const task_t* task);
ssize_t TaskRun(task_t* task);
void TaskCleanUp(task_t* task);
void TaskSetTimeToRun(task_t* task,size_t interval_in_sec);
size_t TaskGetTimeToRun(const task_t* task);
int TaskIsMatch(const task_t* task, ilrd_uid_t uid);
int TaskCmp(const task_t* task1, const task_t* task2);

#endif /* ILRD_TASK_H */
