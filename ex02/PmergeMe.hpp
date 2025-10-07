#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>

class PmergeMe
{
private:
    std::vector<int> _vector;
    std::deque<int> _deque;
    
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    
    // Ford-Johnson algorithm for vector
    void fordJohnsonSort(std::vector<int>& arr);
    void createPairsVector(std::vector<int>& arr);
    void insertionSortVector(std::vector<int>& arr, int left, int right);
    void mergeInsertVector(std::vector<int>& arr);
    
    // Ford-Johnson algorithm for deque
    void fordJohnsonSort(std::deque<int>& arr);
    void createPairsDeque(std::deque<int>& arr);
    void insertionSortDeque(std::deque<int>& arr, int left, int right);
    void mergeInsertDeque(std::deque<int>& arr);
    
    bool isValidInput(const std::vector<std::string>& args) const;
    void printSequence(const std::vector<int>& seq, const std::string& prefix) const;
    
public:
    PmergeMe(const std::vector<std::string>& args);
    ~PmergeMe();
    
    void sortAndDisplay();
};

#endif

