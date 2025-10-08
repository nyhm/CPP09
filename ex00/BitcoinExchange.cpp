#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange(const std::string& databaseFile)
{
    loadExchangeRates(databaseFile);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadExchangeRates(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date, rateStr;
        
        if (std::getline(iss, date, ',') && std::getline(iss, rateStr))
        {
            std::istringstream rateStream(rateStr);
            double rate;
            rateStream >> rate;
            _exchangeRates[date] = rate;
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    // Check if all characters except dashes are digits
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    
    // Efficient date parsing
    int year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + 
               (date[2] - '0') * 10 + (date[3] - '0');
    int month = (date[5] - '0') * 10 + (date[6] - '0');
    int day = (date[8] - '0') * 10 + (date[9] - '0');
    
    if (year < 2009 || year > 2022 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    
    // Detailed date validation
    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        int maxDays = isLeapYear ? 29 : 28;
        if (day > maxDays)
            return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }
    
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& value, double& result) const
{
    std::istringstream iss(value);
    iss >> result;
    
    if (iss.fail() || !iss.eof())
        return false;
    
    if (result < 0)
        return false;
    
    if (result > 1000)
        return false;
    
    return true;
}

std::string BitcoinExchange::findClosestDate(const std::string& targetDate) const
{
    std::map<std::string, double>::const_iterator it = _exchangeRates.lower_bound(targetDate);
    
    // If exact match found
    if (it != _exchangeRates.end() && it->first == targetDate)
        return targetDate;
    
    // If no exact match, find the closest previous date
    if (it != _exchangeRates.begin())
    {
        --it;
        return it->first;
    }
    
    // If target date is before all dates in database, return the first available date
    if (!_exchangeRates.empty())
        return _exchangeRates.begin()->first;
    
    // This should never happen if database is loaded correctly
    return targetDate;
}

void BitcoinExchange::processInputFile(const std::string& inputFile)
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date, valueStr;
        
        if (std::getline(iss, date, '|') && std::getline(iss, valueStr))
        {
            // Remove leading/trailing whitespace efficiently
            size_t start = date.find_first_not_of(" \t");
            size_t end = date.find_last_not_of(" \t");
            if (start != std::string::npos && end != std::string::npos)
                date = date.substr(start, end - start + 1);
            else
                date.clear();
            
            start = valueStr.find_first_not_of(" \t");
            end = valueStr.find_last_not_of(" \t");
            if (start != std::string::npos && end != std::string::npos)
                valueStr = valueStr.substr(start, end - start + 1);
            else
                valueStr.clear();
            
            if (!isValidDate(date))
            {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            
            double value;
            if (!isValidValue(valueStr, value))
            {
                if (value < 0)
                    std::cerr << "Error: not a positive number." << std::endl;
                else if (value > 1000)
                    std::cerr << "Error: too large a number." << std::endl;
                else
                    std::cerr << "Error: bad input => " << valueStr << std::endl;
                continue;
            }
            
            std::string closestDate = findClosestDate(date);
            double exchangeRate = _exchangeRates.find(closestDate)->second;
            double result = value * exchangeRate;
            
            std::cout << date << " => " << value << " = " << result << std::endl;
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
    
    file.close();
}

