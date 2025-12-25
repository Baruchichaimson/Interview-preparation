/**************************************
Exercise: 	final project - input mediator
Date:		23/12/2025
Developer:	baruch haimson
Reviewer: 	
Status:		
**************************************/
#ifndef __ILRD_INPUTMEDIATOR__
#define __ILRD_INPUTMEDIATOR__

#include <memory> // std::shared_ptr
#include <tuple> // std::tuple
#include <vector> // std::vector

#include "pool_thread.hpp"
#include "iinputproxy.hpp"
#include "reactor.hpp"

namespace ilrd
{
class InputMediator 
{
public:
    using input_proxy_t = std::shared_ptr<IInputProxy>; 
    
    InputMediator(const std::vector<std::tuple<int, Reactor::Mode, input_proxy_t>>& registrations, std::shared_ptr<Reactor::IListener> listener);
    ~InputMediator() = default;

    void Run(); 
    void Stop();
    
private:

    class TPTask : public ThreadPool::ITPTask
    {
    public:
        TPTask(std::shared_ptr<IKeyArgs> args);
        ~TPTask() override;
        void Execute() override;  
    private:
        std::shared_ptr<IKeyArgs> m_args;
    };
    
    class ReactorCallback // Reactors std::function callback
    {
    public:
        ReactorCallback(std::shared_ptr<IInputProxy> inputProxy);
        void operator()(int fd, Reactor::Mode mode);
    
    private:
        const std::shared_ptr<IInputProxy> m_input_proxy;
    };

    Reactor m_reactor;

}; // class InputMediator
} // ilrd

#endif  // __ILRD_INPUTMEDIATOR__