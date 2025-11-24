/**************************************
Exercise: 	cpp_intro - rc_string
Date:		24/11/2025
Developer:	Baruch Haimson
Reviewer: 	
Status:		
**************************************/

#include <iostream>
#include <mutex>
#include <fstream>

namespace ilrd
{
    template<typename Resource>
    class RAII 
    {
    private:
        Resource& res;
    public:
        RAII(Resource& r) : res(r) 
        {
            res.acquire(); 
            std::cout << "Resource acquired\n";
        }

        ~RAII() 
        {
            res.release(); 
            std::cout << "Resource released\n";
        }

        RAII(const RAII&) = delete;
        RAII& operator=(const RAII&) = delete;
    };

    class MutexWrapper 
    {
    private:
        std::mutex mtx;
    public:
        void acquire() { mtx.lock(); }
        void release() { mtx.unlock(); }
    };
}
int main() 
{
    ilrd::MutexWrapper myMutex;

    ilrd::RAII<ilrd::MutexWrapper> lock(myMutex);
    std::cout << "Inside critical section\n";
    
    return 0;
}
