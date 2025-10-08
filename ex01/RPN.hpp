#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <climits>

class RPN
{
private:
    std::string _expression;
    std::stack<int> _stack;
    
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    
    bool isOperator(char c) const;
    bool isValidToken(char c) const;
    long long performOperation(long long  a, long long  b, char op) const;
    void parseExpression();
    
public:
    RPN(const std::string& expression);
    ~RPN();
    
    int calculate();
};

#endif

