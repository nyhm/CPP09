#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

RPN::RPN(const std::string& expression) : _expression(expression)
{
    if (expression.empty())
    {
        std::cerr << "Error" << std::endl;
        throw std::runtime_error("Empty expression");
    }
}

RPN::~RPN()
{
}

bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isValidToken(char c) const
{
    return (std::isdigit(c) || isOperator(c) || c == ' ');
}

int RPN::performOperation(int a, int b, char op) const
{
    switch (op)
    {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
            {
                std::cerr << "Error" << std::endl;
                throw std::runtime_error("Division by zero");
            }
            return a / b;
        default:
            std::cerr << "Error" << std::endl;
            throw std::runtime_error("Invalid operator");
    }
}

void RPN::parseExpression()
{
    for (size_t i = 0; i < _expression.length(); ++i)
    {
        char c = _expression[i];
        
        // Skip spaces
        if (c == ' ')
            continue;
        
        if (!isValidToken(c))
        {
            std::cerr << "Error" << std::endl;
            throw std::runtime_error("Invalid token");
        }
        
        if (std::isdigit(c))
        {
            // Check if number is between 0-9 (single digit only)
            int digit = c - '0';
            _stack.push(digit);
        }
        else if (isOperator(c))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                throw std::runtime_error("Not enough operands");
            }
            
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            
            int result = performOperation(a, b, c);
            _stack.push(result);
        }
    }
}

int RPN::calculate()
{
    // Clear stack and parse expression
    while (!_stack.empty())
        _stack.pop();
    
    try {
        parseExpression();
    } catch (const std::exception& e) {
        std::cerr << "Error" << std::endl;
        throw;
    }
    
    if (_stack.empty())
    {
        std::cerr << "Error" << std::endl;
        throw std::runtime_error("Empty stack");
    }
    
    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        throw std::runtime_error("Invalid expression");
    }
    
    return _stack.top();
}

