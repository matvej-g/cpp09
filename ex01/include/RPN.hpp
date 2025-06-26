#pragma once
#include <stack>

class RPN {
private:
	std::stack<int> _num_stack;

public:
	RPN();
	RPN(const RPN& other);
	RPN &operator=(const RPN& other);
	~RPN();

	int process(char* expression);
};