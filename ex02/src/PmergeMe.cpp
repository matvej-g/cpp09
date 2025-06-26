#include "../include/PmergeMe.hpp"
#include <iostream>

PmergeMe::PmergeMe() {
	//std::cout << "PmergeMe constructed\n";
}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
	//std::cout << "PmergeMe copy constructed.\n";
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	//std::cout << Pmgerme assigned.\n";
	return *this;
}

PmergeMe::~PmergeMe() {
	//std::cout << "PmergeMe destructed.\n";
}