/***************************
 * Exercise: Task
 * Date: 22/07/25
 * Developer: Baruch Haimson
 * Reviwer: Yael
 * Status: Approved
 ***************************/
 
#ifndef ILRD_TASK_H
#define ILRD_TASK_H

#include <sys/types.h>  /* ssize_t */
#include "uid.h"       /* ilrd_uid_t */

typedef struct task task_t;

/**
 * Description: Creates a new task object with operation, parameters,
 * execution interval, and optional cleanup.
 *
 * Function Arguments:
 *        op_func        - function to execute.
 *        op_param       - parameter to pass to op_func.
 *        interval_in_sec - number of seconds from now to run the task.
 *        cleanup_func   - optional function to cleanup after task.
 *        cleanup_param  - parameter to pass to cleanup_func.
 *
 * Return Value:
 *        - Pointer to the created task on success.
 *        - NULL on allocation failure or UID failure.
 *
 * General notes:
 *        - time_to_execute is set to current time + interval_in_sec.
 *        - cleanup_func can be NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
task_t* TaskCreate(ssize_t (*op_func)(void *param), void *op_param,
                   size_t interval_in_sec,
                   void (*cleanup_func)(void* param),
                   void* cleanup_param);

/**
 * Description: Destroys a task and frees all associated memory.
 *
 * Function Arguments:
 *        task - pointer to the task to destroy.
 *
 * Return Value: None.
 *
 * General notes:
 *        - Calls the cleanup function if it exists.
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
void TaskDestroy(task_t* task);

/**
 * Description: Returns the UID of the task.
 *
 * Function Arguments:
 *        task - pointer to the task.
 *
 * Return Value:
 *        - ilrd_uid_t of the task.
 *
 * General notes:
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
ilrd_uid_t TaskUID(const task_t* task);

/**
 * Description: Executes the task's operation function.
 *
 * Function Arguments:
 *        task - pointer to the task.
 *
 * Return Value:
 *        - The return value of the operation function.
 *        - -1 if op_func is NULL.
 *
 * General notes:
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: depends on user-defined function.
 **/
ssize_t TaskRun(task_t* task);

/**
 * Description: Executes the task's cleanup function if it exists.
 *
 * Function Arguments:
 *        task - pointer to the task.
 *
 * Return Value: None.
 *
 * General notes:
 *        - Safe to call even if cleanup_func is NULL.
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: depends on user-defined function.
 **/
void TaskCleanUp(task_t* task);

/**
 * Description: Sets the next execution time of the task based on the current time and interval.
 *
 * Function Arguments:
 *        task - pointer to the task.
 *        interval_in_sec - number of seconds from now to set the execution time.
 *
 * Return Value: None.
 *
 * General notes:
 *        - Useful for periodic tasks.
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
void TaskSetTimeToRun(task_t* task, size_t interval_in_sec);

/**
 * Description: Returns the time the task is scheduled to run.
 *
 * Function Arguments:
 *        task - pointer to the task.
 *
 * Return Value:
 *        - Epoch time (time_t) when the task is scheduled to run.
 *
 * General notes:
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
size_t TaskGetTimeToRun(const task_t* task);

/**
 * Description: Compares the task's UID to a given UID.
 *
 * Function Arguments:
 *        task - pointer to the task.
 *        uid  - UID to compare with.
 *
 * Return Value:
 *        - 1 if UIDs match.
 *        - 0 otherwise.
 *
 * General notes:
 *        - Behavior is undefined if task is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
int TaskIsMatch(const task_t* task, ilrd_uid_t uid);

/**
 * Description: Compares two tasks by their scheduled time.
 *
 * Function Arguments:
 *        task1 - first task.
 *        task2 - second task.
 *
 * Return Value:
 *        - 1 if times are equal.
 *        - 0 otherwise.
 *
 * General notes:
 *        - Does not sort; only equality comparison.
 *        - Behavior is undefined if either task is NULL.
 *
 * Complexity:
 *        - Time: O(1).
 **/
int TaskCmp(const task_t* task1, const task_t* task2);

#endif /* ILRD_TASK_H */

