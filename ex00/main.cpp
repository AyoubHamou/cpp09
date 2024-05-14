#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>


int main(int ac, char **av){
	try
  {
    if (ac != 2)
      throw std::runtime_error("Error: could not open file.");
		BitcoinExchange bitcoin;
    bitcoin.exec(av[1]);
  }
  catch ( std::exception &e)
  {
    std::cout << e.what() << "\n";
  }
}
