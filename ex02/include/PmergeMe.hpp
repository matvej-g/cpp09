#pragma once
#include <vector>
#include <deque>

class PmergeMe {
private:
	std::vector<size_t> _vector;
	std::deque<size_t> _deque;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe &operator=(const PmergeMe& other);
	~PmergeMe();

	static std::vector<size_t> computeJacobsthal_vec(size_t n);
	static std::vector<size_t> mergeInsertSort_vec(std::vector<size_t> vec);

	static std::deque<size_t> computeJacobsthal_deque(size_t n);
	static std::deque<size_t> mergeInsertSort_deque(std::deque<size_t> vec);
};