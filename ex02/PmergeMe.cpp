#include "PmergeMe.hpp"
#include <utility>


PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

void is_number(char *str){
	for (size_t i = 0; str[i] ;i++){
		if (i == 0 && str[i] == '+' && str[i+1])
			continue;
		if (!std::isdigit(str[i]))
			throw std::runtime_error("Error1");
	}
}

unsigned int stringToInt(char *av)
{
	unsigned int res;
	std::istringstream iss(av);
	if (!(iss >> res))
		throw std::runtime_error ("Error2");
	return res;
}


void check_args(int ac,char **av){
	for (int i = 0; i < ac ;i++){
		is_number(av[i]);
	};
}

pair_vec make_pairs(it begin, it end){
	pair_vec res;
	unsigned int i1;
	unsigned int i2;

	for (it it = begin ; it + 1 < end ;	it += 2){
		i1 = *it;
		i2 = *(it + 1);
		if (i1 > i2)
			res.push_back(std::make_pair(i1, i2));
		else
			res.push_back(std::make_pair(i2, i1));
	}
	return res;
}



void PmergeMe::sort_vector(int ac, char **av){
	check_args(ac, av);
	std::vector<unsigned int> before;
	for (int i = 0; i < ac;i++){
		before.push_back(stringToInt(av[i]));
	}
	bool odd = false;
	int last_element;
	if (ac % 2){
		odd = true;
		last_element = before.at(ac - 1);
	}
	pair_vec pairs = make_pairs(before.begin(), before.end());
	for (pair_vec::iterator it = pairs.begin(); it < pairs.end() ; it++){
		std::cout << "{" << it->first << "," << it->second << "}" << std::endl;
	}
	if (odd)
		std::cout << last_element << std::endl;
}
