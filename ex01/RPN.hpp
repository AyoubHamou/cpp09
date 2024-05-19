#pragma once

#include <stack>
#include <string>
class RPN{
private:
	std::stack<double> stack;
public:
	RPN();
	~RPN();
	void exec(std::string str);
};
