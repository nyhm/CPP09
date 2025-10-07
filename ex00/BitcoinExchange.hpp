#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> _exchangeRates;
    
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value, double& result) const;
    std::string findClosestDate(const std::string& targetDate) const;
    void loadExchangeRates(const std::string& filename);
    
public:
    BitcoinExchange(const std::string& databaseFile);
    ~BitcoinExchange();
    
    void processInputFile(const std::string& inputFile);
};

#endif

