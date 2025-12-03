/**************************************
Exercise: thread pool
Date: 03/12/2025
Developer: Baruch Haimson
Reviewer: 
Status:	waiting
**************************************/

#ifndef __ILRD_THREAD_POOL_HPP__
#define __ILRD_THREAD_POOL_HPP__

#include <thread>             // thread
#include <memory>             // shared_ptr
#include <vector>             // vector
#include <mutex>              // m_run_mutex
#include <condition_variable> // condition_variable

#include "waitable_queue.hpp" // WaitableQueue

namespace ilrd
{

class ThreadPool
{
public:

    // -------- Priority --------
    enum priority
    {
        LOW    = 1,
        MEDIUM = 2,
        HIGH   = 3
    };

    // -------- Base Task Interface --------
    class ITPTask
    {
    public:
        virtual ~ITPTask() = default;
        virtual void Execute() = 0;
    };

private:

    // -------- Task typedefs --------
    using TaskPtr   = std::shared_ptr<ITPTask>;
    using TaskEntry = std::pair<priority, TaskPtr>;

    struct TaskComparator
    {
        bool operator()(const TaskEntry& lhs, const TaskEntry& rhs) const
        {
            return lhs.first < rhs.first; 
        }
    };

    using TaskQueue = std::priority_queue<TaskEntry, std::vector<TaskEntry>, TaskComparator>;
    using TaskWaitableQueue = WaitableQueue<TaskEntry, TaskQueue>;

public:

    explicit ThreadPool(std::size_t num_threads);
    ~ThreadPool();

    void Add(TaskPtr task, priority priority = MEDIUM);
    void Pause();
    void Resume();
    void Stop();
    void SetNumOfThreads(std::size_t new_count);

    ThreadPool(const ThreadPool&)            = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&)                 = delete;
    ThreadPool& operator=(ThreadPool&&)      = delete;

private:

    class WorkerThread;

    void WaitIfPaused(WorkerThread* self);
    void WorkerLoop(WorkerThread* self);

    class WorkerThread
    {
    public:

        WorkerThread(ThreadPool* pool, TaskWaitableQueue& queue, std::mutex& run_mutex, std::condition_variable& run_cond, bool& is_running);
        ~WorkerThread();

        void SetAlive(bool value);
        bool IsAlive() const;

    private:
        void RunThread();

    private:
        ThreadPool* m_pool;
        TaskWaitableQueue& m_queue;
        std::mutex& m_run_mutex;
        std::condition_variable& m_run_cond;

        bool& m_is_running;
        bool m_is_alive;

        std::thread m_thread;
    };

private:

    std::vector<std::unique_ptr<WorkerThread>> m_threads;
    TaskWaitableQueue m_tasks;

    bool m_is_running; 

    std::mutex m_run_mutex;
    std::condition_variable m_run_cond;
};

} // namespace ilrd

#endif // __ILRD_THREAD_POOL_HPP__
