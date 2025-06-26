#include "../include/RPN.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

RPN::RPN() {
	//std::cout "RPN constructor called.\n";
}

RPN::RPN(const RPN& other) {
	*this = other;
	//std::cout << "RPN copy constructed.\n";
}

RPN & RPN::operator=(const RPN& other) {
	if (this != &other) {
		this->_num_stack = other._num_stack;
	}
	//std::cout << "RPN assigned.\n";
	return *this;
}

RPN::~RPN() {
	//std::cout << "RPN destructed.\n";
}

int RPN::process(char* string_expression)
{
	if (!string_expression)
		return (0);
	while (!_num_stack.empty())
		_num_stack.pop();

	std::string expression = string_expression;
	std::istringstream iss(expression);
	std::string token;
	int result = 0;
	while(iss >> token)
	{
		if (token.size() == 1 && (token == "+" || token == "-" || token == "*" || token == "/"))
		{
			if (_num_stack.size() < 2)
				throw std::runtime_error("Error");
			int b = _num_stack.top(); _num_stack.pop();
			int a = _num_stack.top(); _num_stack.pop();
			if (token == "+")
				result = a + b;
			else if (token == "-")
				result = a - b;
			else if (token == "*")
				result = a * b;
			else
			{
				if (b == 0)
					throw std::runtime_error("Error: 0 division");
				result = a / b;
			}
			_num_stack.push(result);
		}
		else if (token.size() == 1 && std::isdigit(token[0]))
		{
			int value = token[0] - '0';
			_num_stack.push(value);
		}
		else
			throw std::runtime_error("Error");
	}
	if (_num_stack.size() != 1)
		throw std::runtime_error("Error");
	return (_num_stack.top());
}