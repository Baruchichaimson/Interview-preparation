#ifndef __ILRD_IINPUT_PROXY_
#define __ILRD_IINPUT_PROXY_

#include "reactor.hpp" //Reactor::MODE mode
#include <memory>

#include "ikeyargs.hpp"

namespace ilrd
{
class IInputProxy
{
public:

   IInputProxy() = default;
   virtual ~IInputProxy() = default;
   virtual std::shared_ptr<IKeyArgs> GetKeyArgs(int fd, Reactor::Mode mode) = 0;
   
}; // class IInputProxy


} // ilrd
#endif  // __ILRD_IINPUT_PROXY_ 