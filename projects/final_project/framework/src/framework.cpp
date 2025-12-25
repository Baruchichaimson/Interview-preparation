/**************************************
Exercise: 	final project - framework
Date:		24/12/2025
Developer:	baruch haimson
Reviewer: 	
Status:		
**************************************/

#include "framework.hpp"
#include "handleton.hpp"
#include "factory.hpp"

namespace ilrd
{

FrameWork::FrameWork(const std::vector<CallBacks>& call_backs, std::shared_ptr<Reactor::IListener> listener, const std::vector<Commands>& commands, const std::string& plugin_dir)
    : m_mediator(call_backs, listener), m_dir_monitor(plugin_dir)
{
    for (const auto& cmd : commands)
    {
        Handleton<Factory<ICommand, int>>::GetInstance().Add(cmd.first, cmd.second);
    }
}

void FrameWork::Run()
{
    m_mediator.Run();
}

void FrameWork::Stop() 
{
    m_mediator.Stop();
}

} // namespace ilrd
