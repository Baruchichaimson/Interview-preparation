#include <stdlib>

#include "pq.h"
#include "uid.h"
#include "task.h"

sched_t* SchedCreate(void)
{

}

void SchedDestroy(sched_t* sch)
{

}

int SchedRun(sched_t* sch)
{

}

void SchedStop(sched_t* sch)
{

}

ilrd_uid_t SchedAdd(sched_t* sch, int(op_func*)(void* param), void* param, size_t time_exe, void(cleanup_func*), void* cleanup_param)
{

}

void SchedRemove(sched_t* sch, ilrd_uid_t uid)
{

}

int SchedIsEmpty(const sched_t* sch)
{

}

void SchedClear(sched_t* sch)
{

}

size_t SchedSize(const sched_t* sch)
{

}
