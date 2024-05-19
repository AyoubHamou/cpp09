#include "RPN.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>

RPN::RPN(){}

RPN::~RPN(){}

int is_operator(char c){
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 1;
	return 0;
}

int do_operation(char c, double d1, double d2){
	if (c == '+')
		return d1 + d2;
	if (c == '-')
		return d1 - d2;
	if (c == '*')
		return d1 * d2;
	if (c == '/')
		return d1 / d2;
	return 0;
}

void RPN::exec(std::string str){
	if (str.empty())
		throw std::runtime_error ("Error : empty argument");
	for (size_t i = 0; i < str.length();i++){
		if (std::isdigit(str[i])){
			if (i + 1 > str.length())
				throw std::runtime_error("Error");
			if (std::isdigit(str[i+1]))
				throw std::runtime_error("Error");
			stack.push(str[i] - 48);
		}
		else if (is_operator(str[i])){
			if (stack.size() < 2)
				throw std::runtime_error ("Error : stack size is under 2");
			double d1 = stack.top();
			stack.pop();
			double d2 = stack.top();
			stack.pop();
			stack.push(do_operation(str[i], d2, d1));
		}
		else if (str[i] != ' ' && str[i] != '\t')
			throw std::runtime_error ("Error : Invalid character");
	}
	if (stack.size() > 1)
		throw std::runtime_error ("Error");
	std::cout << stack.top() << std::endl;
}
