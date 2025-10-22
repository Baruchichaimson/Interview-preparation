#include <iostream>

#include "complex.hpp"

int main()
{
    ilrd::Complex c;
    ilrd::Complex a(3, 4);
    ilrd::Complex b(1, 2);

    std::cout << "c = " << c << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;

    //std::cout << std::boolalpha;
    std::cout << "a == b? " << (a == b) << std::endl;
    std::cout << "a != b? " << (a != b) << std::endl;

    return 0;
}
