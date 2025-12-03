/**************************************
Exercise: thread pool
Date: 03/12/2025
Developer: Baruch Haimson
Reviewer: 
Status:	waiting
**************************************/

#include "pool_thread.hpp" 

namespace ilrd
{

ThreadPool::WorkerThread::WorkerThread(ThreadPool* pool, TaskWaitableQueue& queue, std::mutex& run_mutex, std::condition_variable& run_cond, bool& is_running)
    : m_pool(pool), m_queue(queue), m_run_mutex(run_mutex), m_run_cond(run_cond), m_is_running(is_running), m_is_alive(true), m_thread(&WorkerThread::RunThread, this)
{
}

ThreadPool::WorkerThread::~WorkerThread()
{
    SetAlive(false);
    m_run_cond.notify_all();

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void ThreadPool::WorkerThread::SetAlive(bool value)
{
    m_is_alive = value;
}

bool ThreadPool::WorkerThread::IsAlive() const
{
    return m_is_alive;
}

void ThreadPool::WorkerThread::RunThread()
{
    m_pool->WorkerLoop(this);
}

ThreadPool::ThreadPool(std::size_t num_threads): m_is_running(true)
{
    m_threads.reserve(num_threads);

    for (std::size_t i = 0; i < num_threads; ++i)
    {
        m_threads.emplace_back(std::make_unique<WorkerThread>(this, m_tasks, m_run_mutex, m_run_cond, m_is_running));
    }
}

ThreadPool::~ThreadPool()
{
    Stop();
}

void ThreadPool::Add(TaskPtr task, priority priority)
{
    m_tasks.push(TaskEntry(priority, task));
    m_run_cond.notify_all();
}

void ThreadPool::Pause()
{
    m_is_running = false;
}

void ThreadPool::Resume()
{
    m_is_running = true;
    m_run_cond.notify_all();
}

void ThreadPool::Stop()
{
    if (!m_is_running)
        return;

    m_is_running = false;

    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i]->SetAlive(false);
    }

    m_run_cond.notify_all();

    m_threads.clear();   
}

void ThreadPool::SetNumOfThreads(std::size_t new_count)
{
    std::size_t current = m_threads.size();
    std::size_t remove_count = current - new_count;

    if (new_count > current)
    {
        for (std::size_t i = 0; i < new_count - current; ++i)
        {
            m_threads.emplace_back(std::make_unique<WorkerThread>(this, m_tasks, m_run_mutex, m_run_cond, m_is_running));
        }
    }
    else if (new_count < current)
    {
        for (std::size_t i = 0; i < remove_count; ++i)
        {
            m_threads[i]->SetAlive(false);
        }

        m_run_cond.notify_all();

        m_threads.erase(m_threads.begin(), m_threads.begin() + remove_count);
    }
}

void ThreadPool::WaitIfPaused(WorkerThread* self)
{
    std::unique_lock<std::mutex> lock(m_run_mutex);

    while (!m_is_running && self->IsAlive())
    {
        m_run_cond.wait(lock);
    }
}

void ThreadPool::WorkerLoop(WorkerThread* self)
{
    TaskEntry entry;

    while (self->IsAlive())
    {
        WaitIfPaused(self);
        if (!self->IsAlive()) 
        { 
            return; 
        }

        bool got = m_tasks.pop(&entry, std::chrono::milliseconds(100));

        if (!got)
        {
            continue;
        }

        WaitIfPaused(self);
        if (!self->IsAlive()) 
        { 
            return; 
        }

        entry.second->Execute();
    }
}

} // namespace ilrd
