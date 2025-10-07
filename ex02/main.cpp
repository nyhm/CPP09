#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    try
    {
        std::vector<std::string> args;
        for (int i = 1; i < argc; ++i)
        {
            args.push_back(argv[i]);
        }
        
        PmergeMe pmerge(args);
        pmerge.sortAndDisplay();
    }
    catch (const std::exception& e)
    {
        return 1;
    }
    
    return 0;
}

