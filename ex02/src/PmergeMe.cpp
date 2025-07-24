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
	if (this != &other) {
		this->_vector = other._vector;
		this->_deque = other._deque;
	}
	//std::cout << Pmgerme assigned.\n";
	return *this;
}

PmergeMe::~PmergeMe() {
	//std::cout << "PmergeMe destructed.\n";
}

//Vector container sort
std::vector<size_t> PmergeMe::computeJacobsthal_vec(size_t n) {
	std::vector<size_t> Jacob = {0, 1};
	while (Jacob.back() < n)
	{
		size_t k = Jacob.size();
		size_t num = Jacob[k - 1] + 2 * Jacob[k - 2];
		if (num <= n)
			Jacob.push_back(num);
		else
			break;
	}
	size_t i = 0;
	std::vector<size_t> order;
	std::vector<bool> seen(n, false);
	i = 0;
	for (size_t x : Jacob)
	{
		if (!seen[x])
		{
			order.push_back(x);
			seen[x] = true;
		}
		while (i < x)
		{
			if (!seen[i])
			{
				order.push_back(i);
				seen[i] = true;
			}
			i++;
		}
	}
	while(i < n)
	{
		if (!seen[i])
		{
			order.push_back(i);
			seen[i] = true;
		}
		i++;
	}
	return order;
}

std::vector<size_t> PmergeMe::mergeInsertSort_vec(std::vector<size_t> vec) {
	if (vec.size() <= 1)
		return vec;
	
	std::vector<size_t> smaller, larger;
	for (size_t i = 0; i + 1 < vec.size(); i += 2)
	{
		size_t a = vec[i], b = vec[i + 1];
		if (a < b)
		{
			smaller.push_back(a);
			larger.push_back(b);
		}
		else
		{
			smaller.push_back(b);
			larger.push_back(a);	
		}
	}
	if (vec.size() % 2) {
		larger.push_back(vec.back());
	}
	larger = mergeInsertSort_vec(std::move(larger));
	auto order = computeJacobsthal_vec(smaller.size());
	for (size_t test : order)
		std::cout << "Order: " << test << ' ' << "\n";
	for (size_t idx : order)
	{
		int x = smaller[idx];
		std::cout << "\nX: " << x << "\n\n";
		auto it = std::lower_bound(larger.begin(), larger.end(), x);
		larger.insert(it ,x);
	}
	return larger;
}

//Deque container sort
std::deque<size_t> computeJacobsthal_deque(size_t n) {
	std::deque<size_t> Jacob = {0, 1};
	while (Jacob.back() < n)
	{
		size_t k = Jacob.size();
		size_t num = Jacob[k - 1] + 2 * Jacob[k - 2];
		if (num <= n)
			Jacob.push_back(num);
		else
			break;
	}
	size_t i = 0;
	std::deque<size_t> order;
	std::deque<bool> seen(n, false);
	i = 0;
	for (size_t x : Jacob)
	{
		if (!seen[x])
		{
			order.push_back(x);
			seen[x] = true;
		}
		while (i < x)
		{
			if (!seen[i])
			{
				order.push_back(i);
				seen[i] = true;
			}
			i++;
		}
	}
	while(i < n)
	{
		if (!seen[i])
		{
			order.push_back(i);
			seen[i] = true;
		}
		i++;
	}
	return order;
}

std::deque<size_t> mergeInsertSort_deque(std::deque<size_t> vec) {
	if (vec.size() <= 1)
		return vec;
	
	std::deque<size_t> smaller, larger;
	for (size_t i = 0; i + 1 < vec.size(); i += 2)
	{
		size_t a = vec[i], b = vec[i + 1];
		if (a < b)
		{
			smaller.push_back(a);
			larger.push_back(b);
		}
		else
		{
			smaller.push_back(b);
			larger.push_back(a);	
		}
	}
	if (vec.size() % 2) {
		larger.push_back(vec.back());
	}
	larger = mergeInsertSort_deque(std::move(larger));
	auto order = computeJacobsthal_deque(smaller.size());
	for (size_t idx : order)
	{
		int x = smaller[idx];
		auto it = std::lower_bound(larger.begin(), larger.end(), x);
		larger.insert(it ,x);
	}
	return larger;
}