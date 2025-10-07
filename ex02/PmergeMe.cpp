#include "PmergeMe.hpp"
#include <sstream>
#include <stdexcept>

PmergeMe::PmergeMe(const std::vector<std::string>& args)
{
    if (!isValidInput(args))
    {
        std::cerr << "Error" << std::endl;
        throw std::runtime_error("Invalid input");
    }
    
    for (size_t i = 0; i < args.size(); ++i)
    {
        std::istringstream iss(args[i]);
        int value;
        iss >> value;
        _vector.push_back(value);
        _deque.push_back(value);
    }
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::isValidInput(const std::vector<std::string>& args) const
{
    if (args.empty())
        return false;
    
    for (size_t i = 0; i < args.size(); ++i)
    {
        const std::string& arg = args[i];
        
        // Check if string is empty
        if (arg.empty())
            return false;
        
        // Check if all characters are digits
        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                return false;
        }
        
        // Check if number is positive
        std::istringstream iss(arg);
        int value;
        iss >> value;
        if (value <= 0)
            return false;
    }
    
    return true;
}

void PmergeMe::printSequence(const std::vector<int>& seq, const std::string& prefix) const
{
    std::cout << prefix << ": ";
    for (size_t i = 0; i < seq.size(); ++i)
    {
        std::cout << seq[i];
        if (i < seq.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::fordJohnsonSort(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    // For small arrays, use insertion sort
    if (arr.size() <= 10)
    {
        insertionSortVector(arr, 0, arr.size() - 1);
        return;
    }
    
    // Ford-Johnson algorithm: create pairs and sort them
    createPairsVector(arr);
    
    // Recursively sort the pairs (only the first elements of each pair)
    std::vector<int> firstElements;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        firstElements.push_back(arr[i]);
    }
    
    fordJohnsonSort(firstElements);
    
    // Reconstruct the array with sorted first elements
    for (size_t i = 0; i < firstElements.size(); ++i)
    {
        arr[i * 2] = firstElements[i];
    }
    
    // Merge-insert phase
    mergeInsertVector(arr);
}

void PmergeMe::createPairsVector(std::vector<int>& arr)
{
    // In-place pair creation and sorting for better memory efficiency
    for (size_t i = 0; i < arr.size() - 1; i += 2)
    {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }
}

void PmergeMe::insertionSortVector(std::vector<int>& arr, int left, int right)
{
    for (int i = left + 1; i <= right; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeInsertVector(std::vector<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    // Extract first element of each pair (already sorted)
    std::vector<int> mainChain;
    std::vector<int> pend;
    
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        mainChain.push_back(arr[i]);
        if (i + 1 < arr.size())
            pend.push_back(arr[i + 1]);
    }
    
    // Insert pend elements using binary search
    for (size_t i = 0; i < pend.size(); ++i)
    {
        int element = pend[i];
        
        // Binary search for insertion point
        int left = 0, right = mainChain.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (mainChain[mid] < element)
                left = mid + 1;
            else
                right = mid;
        }
        
        mainChain.insert(mainChain.begin() + left, element);
    }
    
    arr = mainChain;
}

void PmergeMe::fordJohnsonSort(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    // For small arrays, use insertion sort
    if (arr.size() <= 10)
    {
        insertionSortDeque(arr, 0, arr.size() - 1);
        return;
    }
    
    // Ford-Johnson algorithm: create pairs and sort them
    createPairsDeque(arr);
    
    // Recursively sort the pairs (only the first elements of each pair)
    std::deque<int> firstElements;
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        firstElements.push_back(arr[i]);
    }
    
    fordJohnsonSort(firstElements);
    
    // Reconstruct the array with sorted first elements
    for (size_t i = 0; i < firstElements.size(); ++i)
    {
        arr[i * 2] = firstElements[i];
    }
    
    // Merge-insert phase
    mergeInsertDeque(arr);
}

void PmergeMe::createPairsDeque(std::deque<int>& arr)
{
    // In-place pair creation and sorting for better memory efficiency
    for (size_t i = 0; i < arr.size() - 1; i += 2)
    {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }
}

void PmergeMe::insertionSortDeque(std::deque<int>& arr, int left, int right)
{
    for (int i = left + 1; i <= right; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeInsertDeque(std::deque<int>& arr)
{
    if (arr.size() <= 1)
        return;
    
    // Extract first element of each pair (already sorted)
    std::deque<int> mainChain;
    std::deque<int> pend;
    
    for (size_t i = 0; i < arr.size(); i += 2)
    {
        mainChain.push_back(arr[i]);
        if (i + 1 < arr.size())
            pend.push_back(arr[i + 1]);
    }
    
    // Insert pend elements using binary search
    for (size_t i = 0; i < pend.size(); ++i)
    {
        int element = pend[i];
        
        // Binary search for insertion point
        int left = 0, right = mainChain.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (mainChain[mid] < element)
                left = mid + 1;
            else
                right = mid;
        }
        
        mainChain.insert(mainChain.begin() + left, element);
    }
    
    arr = mainChain;
}


void PmergeMe::sortAndDisplay()
{
    // Print original sequence
    printSequence(_vector, "Before");
    
    // Sort with vector and measure time
    std::vector<int> vectorCopy = _vector;
    clock_t start = clock();
    fordJohnsonSort(vectorCopy);
    clock_t end = clock();
    double vectorTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000; // Convert to microseconds
    
    // Sort with deque and measure time
    std::deque<int> dequeCopy = _deque;
    start = clock();
    fordJohnsonSort(dequeCopy);
    end = clock();
    double dequeTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000; // Convert to microseconds
    
    // Print sorted sequence
    printSequence(vectorCopy, "After");
    
    // Print timing information
    std::cout << "Time to process a range of " << _vector.size() 
              << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _deque.size() 
              << " elements with std::deque : " << dequeTime << " us" << std::endl;
}

