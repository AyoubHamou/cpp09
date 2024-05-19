#include "PmergeMe.hpp"
#include <exception>
#include <stdexcept>


int main(int ac, char **av){
	try{
		if (ac < 2)
			throw std::runtime_error ("Bad arguments");
		ac--;
		av++;
		PmergeMe m;
		m.sort_vector(ac, av);
	}
	catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
}
