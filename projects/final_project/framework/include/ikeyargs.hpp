#ifndef __ILRD_IKEYARGS__
#define __ILRD_IKEYARGS__


namespace ilrd
{
class IKeyArgs
{
public:
    virtual ~IKeyArgs() = default;
    virtual int GetKey() = 0;
}; // class IKeyArgs
} // ilrd

#endif  // __ILRD_IKEYARGS__