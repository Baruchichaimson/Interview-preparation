/**************************************
Exercise: waitable queue
Date: 01/12/2025
Developer: Baruch Haimson
Reviewer: 
Status:	waiting
**************************************/

#include <iostream>
#include <thread>
#include <chrono>

#include "waitable_queue.hpp"   

using namespace ilrd;

static void PrintResult(const char* test_name, bool condition)
{
    std::cout << test_name << ": " << (condition ? "PASS" : "FAIL") << "\n";
}

void TestPushAndPopCopy()
{
    WaitableQueue<int> q;
    int out = 0;

    q.push(42);          
    q.pop(&out);         
    PrintResult("TestPushAndPopCopy", out == 42);
}

void TestPushMove()
{
    WaitableQueue<std::string> q;
    std::string s = "hello";
    std::string out;

    q.push(std::move(s));   
    q.pop(&out);

    PrintResult("TestPushMove", out == "hello" && s.empty());
}

void TestEmpty()
{
    WaitableQueue<int> q;

    PrintResult("TestEmptyInitially", q.empty());

    q.push(5);

    PrintResult("TestEmptyAfterPush", !q.empty());
}

void TestPopTimeoutFail()
{
    WaitableQueue<int> q;
    int out = 123;

    bool result = q.pop(&out, std::chrono::milliseconds(200));

    PrintResult("TestPopTimeoutFail", result == false && out == 123); 
}

void TestPopTimeoutSuccess()
{
    WaitableQueue<int> q;
    int out = 0;

    std::thread t([&q]() 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        q.push(999);
    });

    bool result = q.pop(&out, std::chrono::milliseconds(300));

    t.join();

    PrintResult("TestPopTimeoutSuccess", result && out == 999);
}

void TestMultipleProducersConsumers()
{
    WaitableQueue<int> q;

    std::thread producer1([&q]() 
    {
        for (int i = 1; i <= 5; ++i) 
        {
            q.push(i);
        }
    });

    std::thread producer2([&q]() 
    {
        for (int i = 6; i <= 10; ++i) 
        {
            q.push(i);
        }
    });

    int sum = 0;
    std::thread consumer([&]() 
    {
        int val;
        for (int i = 0; i < 10; ++i) 
        {
            q.pop(&val);
            sum += val;
        }
    });

    producer1.join();
    producer2.join();
    consumer.join();

    PrintResult("TestMultipleProducersConsumers", sum == 55);
}

int main()
{
    std::cout << "===== WaitableQueue Tests =====\n";

    TestPushAndPopCopy();
    TestPushMove();
    TestEmpty();
    TestPopTimeoutFail();
    TestPopTimeoutSuccess();
    TestMultipleProducersConsumers();

    std::cout << "===== Tests Finished =====\n";
    return 0;
}
