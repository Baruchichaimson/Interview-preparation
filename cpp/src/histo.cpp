#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() 
{
    std::map<std::string, int> counts;
    std::vector<std::string> order;
    std::string line;

    while (std::getline(std::cin, line)) 
    {
        if (line == ".") 
        {
            break;
        }

        if (++counts[line] == 1) 
        {
            order.push_back(line);
        }
    }

    for (std::vector<std::string>::const_iterator it = order.begin(); it != order.end(); ++it) 
    {
        const std::string &s = *it;

        if (counts[s] > 1) 
        {
            std::cout << counts[s] << " x " << s << std::endl;
        } 
        else 
        {
            std::cout << s << std::endl;
        }
    }

    return 0;
}
