#pragma once

#include <vector>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>


typedef std::vector<unsigned int>::iterator it;
typedef 	std::vector< std::pair<unsigned int, unsigned int> > pair_vec;

class PmergeMe{
private:
	std::vector<int> _vector;
public:
	PmergeMe();
	~PmergeMe();
	void sort_vector(int ac, char **av);
};
