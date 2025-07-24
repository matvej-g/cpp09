#include "../include/PmergeMe.hpp"
#include <iostream>
#include <ctime>

int main(int argc, char**argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: need at least one integer\n";
		return 1;
	}

	//Parse Input in vector container
	std::vector<size_t> vec;
	for (int i = 1; i < argc; ++i)
	{
		int x = std::atoi(argv[i]);
		if (x <= 0) {
			std::cerr << "Error\n";
			return 1;
		}
		vec.push_back(static_cast<size_t>(x));
	}
	//Parse Input in deque container
	std::deque<size_t> deq;
	for (int i = 1; i < argc; ++i)
	{
		int x = std::atoi(argv[i]);
		if (x <= 0) {
			std::cerr << "Error\n";
			return 1;
		}
		deq.push_back(static_cast<size_t>(x));
	}

	std::cout << "Before: ";
	for (size_t num : vec)
		std::cout << num << ' ';
	std::cout << "\n";

	auto sorted = PmergeMe::mergeInsertSort_vec(vec);

	std::cout << "After: ";
	for (size_t num : sorted)
		std::cout << num << ' ';
	std::cout << "\n";


	return 0;
}