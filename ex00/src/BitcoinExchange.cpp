#include "../include/BitcoinExchange.hpp"
#include <iomanip>
#include <ctime>
#include <iostream>
#include <exception>
#include <limits>
#include <sstream>
#include <fstream>

BitcoinExchange::BitcoinExchange() {
	//std::cout << "BitcoinExchange default constructed\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
	std::cout << "BitcoinExchange copy constructed\n";
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		this->_csvData = other._csvData;
	}
	std::cout << "BitcoinExchange assigned.\n";
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
	std::cout << "BitcoinExchange destructed.\n";
}

std::pair<std::string, double> BitcoinExchange::parseLine(const std::string& line) const {
	std::stringstream ss(line);
	std::string date, priceStr;

	if (!std::getline(ss, date, ',') || date.empty())
		throw std::invalid_argument("Missing or empty date field.");

	if (!isValidDate(date))
		throw std::invalid_argument("Invalid date: " + date);

	if (!std::getline(ss, priceStr) || priceStr.empty())
		throw std::invalid_argument("Missing or empty price field.");

	double price;

	try {
		price = std::stod(priceStr);
	} catch (...) {
		throw std::invalid_argument("Invalid price: " + priceStr);
	}
	return {date, price};
}

void BitcoinExchange::loadCsvData(const std::string& file) {
	std::ifstream	csvData(file);
	if (!csvData.is_open()) {
		throw std::runtime_error("Cannot open CSV file: " + file);
	}

	std::string line;
	if (!std::getline(csvData, line)) {
		throw std::runtime_error("CSV file is empty: " + file);
	}

	std::size_t lineNumber = 1;
	while (std::getline(csvData, line)) {
		lineNumber++;
		if (line.empty())
			continue;
		try {
			auto [date, price] = parseLine(line);
			_csvData.emplace(date, price);
		} catch (const std::exception& e) {
			std::cerr
				<< "data.csv Error in line: "
				<< lineNumber
				<< e.what()
				<< "\n";
		}
	}
	if (_csvData.empty())
		throw std::runtime_error("No valid data loaded from data.csv");
}

double BitcoinExchange::getPrice(const std::string& date) const {
	auto it = _csvData.lower_bound(date);
	if (it == _csvData.end() || it->first > date) {
		if (it == _csvData.begin())
			throw std::out_of_range("Bitcoin didn't exist at that Date");
		--it;
	}
	return it->second;
}


bool BitcoinExchange::isValidDate(const std::string& s) const {
	std::tm time = {};
	std::stringstream ss(s);
	ss >> std::get_time(&time, "%Y-%m-%d");
	if (ss.fail())
		return false;
	
	time.tm_isdst = -1;
	std::time_t t = std::mktime(&time);
	if ( t == -1)
		return false;
	
	std::stringstream check;
	check << std::put_time(&time, "%Y-%m-%d");
	return check.str() == s;
}

void BitcoinExchange::readData(const std::string& dataCSV, const std::string& inputTXT) {
	loadCsvData(dataCSV);
	std::ifstream inputFile(inputTXT);
	if (!inputFile)
		throw std::runtime_error("Cannot open input file: " + inputTXT);
	
	std::string line;
	std::getline(inputFile, line);
	if (line != "date | value") 
		throw std::runtime_error("Invalid header line in " + inputTXT);

	size_t lineNum = 1;
	while(std::getline(inputFile, line)) {
		++lineNum;
		if (line.empty())
			continue;

		std::stringstream ss(line);
		std::string	date;
		double amount;
		char sep;

		if (!(ss >> date >> sep >> amount) || sep != '|') {
			std::cerr	<< "Error: bad format in input.txt on line: "
						<< lineNum << "\n";
			continue;
		}
		if (!isValidDate(date)) {
			std::cerr << "Error: date does not exist on line: " << lineNum << "\n";
			continue;
		}
		if (amount < 0) {
			std::cerr	<< "Error: negative number on line: " << lineNum << "\n";
			continue;
		}
		if (amount > 1000) {
			std::cerr	<< "Error: amount too large on line: " << lineNum << "\n";
			continue;
		}

		try {
			double result = getPrice(date) * amount;
			if (result > __DBL_MAX__) {
				std::cerr << "Error: result too large.\n";
				continue;
			}
			std::cout	<< std::fixed << std::setprecision(2)
						<< date << " => "
						<< amount << " = "
						<< result << "\n";
		} catch (const std::exception& e) {
			std::cerr	<< "Error on line " << lineNum
						<< ": " << e.what() << "\n";
		}
	}
}