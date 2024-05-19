#include "RPN.hpp"
#include <stdexcept>
#include <iostream>


int main(int ac, char **av){
	try{
		if (ac != 2)
			throw std::runtime_error ("Not Valid Argument");
		RPN rpn;
		rpn.exec(av[1]);
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
	}
}
