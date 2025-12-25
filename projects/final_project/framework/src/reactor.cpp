/**************************************
Exercise: 	final project - reactor
Date:		16/12/2025
Developer:	baruch haimson
Reviewer: 	
Status:		
**************************************/
#include <stdexcept> // std::runtime_error

#include "reactor.hpp"
#include "logger.hpp"

namespace ilrd
{

Reactor::Reactor(const std::shared_ptr<IListener> listener)
    : m_listener(listener)
    , m_is_running(false)
{
    LOG_DEBUG("Reactor ctor entered");
    LOG_DEBUG("Reactor ctor exit");
}

void Reactor::Add(int fd, Mode mode, std::function<void(int, Mode)> callback)
{
    LOG_DEBUG("Reactor::Add entered");
    fd_pair key(fd, mode);
    m_callbacks[key] = callback;
    LOG_DEBUG("Reactor::Add exit");
}

void Reactor::Remove(int fd, Mode mode)
{
    LOG_DEBUG("Reactor::Remove entered");
    fd_pair key(fd, mode);
    if (m_callbacks.find(key) != m_callbacks.end())
    {
        m_callbacks.erase(key);
    }
    LOG_DEBUG("Reactor::Remove exit");
}

void Reactor::Run()
{
    LOG_DEBUG("Reactor::Run entered");
    if (m_is_running)
    {
        throw std::runtime_error("reactor is already running");
    }

    m_is_running = true;

    while (m_is_running && !m_callbacks.empty())
    {
        std::vector<fd_pair> fds;
        fds.reserve(m_callbacks.size());

        for (const auto& entry : m_callbacks)
        {
            fds.push_back(entry.first);
        }

        if (fds.empty())
        {
            break;
        }

        fds = m_listener->Listen(fds);

        for (const auto& fd : fds)
        {
            if (!m_is_running)
            {
                break;
            }

            auto it = m_callbacks.find(fd);

            if (it != m_callbacks.end())
            {
                it->second(fd.first, fd.second);
            }
        }
    }
    LOG_DEBUG("Reactor::Run exit");
}

void Reactor::Stop()
{
    LOG_DEBUG("Reactor::Stop entered");
    m_is_running = false;
    LOG_DEBUG("Reactor::Stop exit");
}

} // namespace ilrd
