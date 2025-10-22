#include <iostream>

#include "simple_string.hpp"

using namespace std;
using namespace ilrd;

void TestCtor();
void TestCopyCtor();
void TestAssignment();
void TestComparison();
void TestLength();
void TestIO();

int main()
{
    TestCtor();
    TestCopyCtor();
    TestAssignment();
    TestComparison();
    TestLength();
    TestIO();

    cout << "\n All tests completed successfully!" << endl;

    return 0;
}

void TestCtor()
{
    cout << "\n[TEST] Constructors" << endl;

    String s1;
    String s2("Hello");

    cout << "s1: " << s1 << " (should be empty)" << endl;
    cout << "s2: " << s2 << " (should be Hello)" << endl;
}

void TestCopyCtor()
{
    cout << "\n[TEST] Copy Constructor" << endl;

    String original("World");
    String copy(original);

    cout << "original: " << original << "" << endl;
    cout << "copy: " << copy << "" << endl;
    cout << "Equal? " << (original == copy) << " (should be 1)" << endl;
}

void TestAssignment()
{
    cout << "\n[TEST] Assignment Operator" << endl;

    String a("Hi");
    String b("Bye");

    cout << "Before assignment: a = " << a << ", b = " << b << "" << endl;

    b = a;

    cout << "After assignment:  a = " << a << ", b = " << b << "" << endl;
    cout << "Equal? " << (a == b) << " (should be 1)" << endl;
}

void TestComparison()
{
    cout << "\n[TEST] Comparison Operators" << endl;

    String a("apple");
    String b("banana");
    String c("apple");

    cout << "a = " << a << ", b = " << b << ", c = " << c << "" << endl;

    cout << "(a == b): " << (a == b) << " (should be 0)" << endl;
    cout << "(a == c): " << (a == c) << " (should be 1)" << endl;
    cout << "(a < b):  " << (a < b)  << " (should be 1)" << endl;
    cout << "(b > a):  " << (b > a)  << " (should be 1)" << endl;
}

void TestLength()
{
    cout << "\n[TEST] Length()" << endl;

    String s1("");
    String s2("abcd");

    cout << "Length of " << s1 << ": " << s1.Length() << " (should be 0)" << endl;
    cout << "Length of " << s2 << ": " << s2.Length() << " (should be 4)" << endl;
}

void TestIO()
{
    cout << "\n[TEST] Stream Operators" << endl;

    String inputString;
    cout << "Enter a word: ";
    cin >> inputString;

    cout << "You entered: " << inputString << "" << endl;
}
