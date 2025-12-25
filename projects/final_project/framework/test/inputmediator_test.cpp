/**************************************
Exercise: 	final project - input mediator
Date:		23/12/2025
Developer:	baruch haimson
Reviewer: 	
Status:		
**************************************/
/* 
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude test/inputmediator_test.cpp 
src/inputmediator.cpp src/reactor.cpp src/pool_thread.cpp src/handleton.cpp
src/scheduler.cpp src/asyncinjection.cpp src/logger.cpp -pthread
*/
#include <iostream>
#include <memory>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include <unistd.h>  
#include <fcntl.h> 

#include "reactor.hpp"
#include "icommand.hpp"
#include "pool_thread.hpp"
#include "handleton.hpp"
#include "singleton.hpp"
#include "inputmediator.hpp"
#include "factory.hpp"
#include "logger.hpp"

using namespace ilrd;

/* ===================== IKeyArgs Stub ===================== */
class KeyArgsStub : public IKeyArgs
{
public:
    explicit KeyArgsStub(int key) : m_key(key) {}

    int GetKey() override
    {
        LOG_DEBUG("KeyArgsStub::GetKey entered");
        LOG_DEBUG("KeyArgsStub::GetKey exit");
        return m_key;
    }

private:
    int m_key;
};

/* ===================== ICommand Stub ===================== */
class CommandStub : public ICommand
{
public:
    async_args Execute(std::shared_ptr<IKeyArgs> args) override
    {
        LOG_DEBUG("CommandStub::Execute entered");
        std::cout << "CommandStub Execute, key = " << args->GetKey() << std::endl;

        LOG_DEBUG("CommandStub::Execute exit");
        return {[]() { std::cout << "AsyncAction running\n"; return true;},std::chrono::milliseconds(100)};
    }
};

/* ===================== IListener Stub ===================== */
class ListenerStub : public Reactor::IListener
{
public:
    std::vector<Reactor::fd_pair>
    Listen(const std::vector<Reactor::fd_pair>& fds) override
    {
        LOG_DEBUG("ListenerStub::Listen entered");
        std::vector<Reactor::fd_pair> ready_fds;

        for (const auto& fd_pair : fds)
        {
            int fd = fd_pair.first;
            char buf;
            ssize_t n = read(fd, &buf, 1);
            if (n > 0)
            {
                std::cout << "ListenerStub: fd " << fd << " is ready\n";
                ready_fds.push_back(fd_pair);
            }
        }

        LOG_DEBUG("ListenerStub::Listen exit");
        return ready_fds;
    }
};

/* ===================== IInputProxy Stub ===================== */
class NBDProxyStub : public IInputProxy
{
public:
    std::shared_ptr<IKeyArgs>
    GetKeyArgs(int fd, Reactor::Mode mode) override
    {
        LOG_DEBUG("NBDProxyStub::GetKeyArgs entered");
        std::cout << "NBDProxyStub fd=" << fd << " mode=" << static_cast<int>(mode) << std::endl;

        LOG_DEBUG("NBDProxyStub::GetKeyArgs exit");
        return std::make_shared<KeyArgsStub>(fd);
    }
};

/* ============================= MAIN ============================= */

int main()
{
    std::cout << "=== InputMediator integration test ===\n";

    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    int flags = fcntl(fds[0], F_GETFL, 0);
    fcntl(fds[0], F_SETFL, flags | O_NONBLOCK);

    std::shared_ptr<Reactor::IListener> listener = std::make_shared<ListenerStub>();

    using command_factory_t = Factory<ICommand, int>;
    auto& factory = Handleton<command_factory_t>::GetInstance();

    factory.Add(3, []() { std::cout << "[Factory] ctor called\n"; return std::make_shared<CommandStub>();});

    auto proxy = std::make_shared<NBDProxyStub>();

    std::vector<std::tuple<int, Reactor::Mode, InputMediator::input_proxy_t>> registrations =
    {
        {fds[0], Reactor::Mode::READ, proxy} 
    };

    InputMediator mediator(registrations, listener);

    std::thread mediator_thread([&]() { mediator.Run(); });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    write(fds[1], "x", 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    mediator_thread.join();

    std::cout << "=== Test finished successfully ===\n";
    return 0;
}