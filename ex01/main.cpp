#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: wrong number of arguments" << std::endl;
        return 1;
    }
    
    try
    {
        RPN rpn(argv[1]);
        int result = rpn.calculate();
        std::cout << result << std::endl;
    }
    catch (const std::exception& e)
    {
        return 1;
    }
    
    return 0;
}

