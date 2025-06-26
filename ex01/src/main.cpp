#include "../include/RPN.hpp"
#include <iostream>

int main(int argc, char** argv) {
	if (argc == 2)
	{
		RPN rpn;
		try {
			int result = rpn.process(argv[1]);
			std::cout << result << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	else
		std::cout << "Usage: ./RPN <expression>\n";
	return (0);
}