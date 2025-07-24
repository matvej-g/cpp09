#include "../include/PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <chrono>


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
		if (x < 0) {
			std::cerr << "Error: Use only positive integers\n";
			return 1;
		}
		vec.push_back(static_cast<size_t>(x));
	}
	//Parse Input in deque container
	std::deque<size_t> deq;
	for (int i = 1; i < argc; ++i)
	{
		int x = std::atoi(argv[i]);
		if (x < 0) {
			std::cerr << "Error: Use only positive integers\n";
			return 1;
		}
		deq.push_back(static_cast<size_t>(x));
	}

	std::cout << "Before: ";
	for (size_t num : vec)
		std::cout << num << ' ';
	std::cout << "\n";

	std::chrono::steady_clock::time_point start_vec = std::chrono::steady_clock::now();
	auto vec_sorted = PmergeMe::mergeInsertSort_vec(vec);
	std::chrono::steady_clock::time_point end_vec = std::chrono::steady_clock::now();

	std::chrono::steady_clock::time_point start_deq = std::chrono::steady_clock::now();
	auto deq_sorted = PmergeMe::mergeInsertSort_deque(deq);
	std::chrono::steady_clock::time_point end_deq = std::chrono::steady_clock::now();

	std::cout << "After: ";
	for (size_t num : vec_sorted)
		std::cout << num << ' ';
	std::cout << "\n";

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << std::chrono::duration_cast<std::chrono::microseconds>(end_vec - start_vec).count() << "[µs]" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: " << std::chrono::duration_cast<std::chrono::microseconds>(end_deq - start_deq).count() << "[µs]" << std::endl;

	return 0;
}
