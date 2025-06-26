#pragma once 
#include <string>
#include <map>

class BitcoinExchange {
private:
	std::map<std::string, double> _csvData;
	std::pair<std::string, double> parseLine(const std::string& line) const;
	void	loadCsvData(const std::string& file);
	double	getPrice(const std::string& date) const;
	bool	isValidDate(const std::string& s) const;

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange &operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	readData(const std::string& dataCSV, const std::string& inputTXT);
};
