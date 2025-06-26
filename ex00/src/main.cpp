#include "../include/BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./btc input.txt\n";
		return 1;
	}
	BitcoinExchange btc;
	try {
		btc.readData("data.csv", argv[1]);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}