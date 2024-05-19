#include "BitcoinExchange.hpp"
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>
#include <sstream>


float stringTofloat(const std::string &str){
	float f;
	std::string tmp;

	std::istringstream iss(str);
	if (!(iss >> f))
		throw std::runtime_error("Error Converting string to float");
	if (iss >> tmp)
		throw std::runtime_error("Error Converting string to float");
	return f;
}

int stringToint(const std::string &str) {
    int result = 0;

    for (size_t i = 0; i < str.length(); ++i) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

std::pair<std::string,float> pairs(std::string &input, std::string del){
	std::pair<std::string,float> p;

	size_t pos = input.find(del);
	if (pos == std::string::npos)
		throw std::runtime_error("Error: bad input ");
	p.first = input.substr(0, pos);
	p.second = stringTofloat(input.substr(pos + del.length()));
	return p;
}

BitcoinExchange::BitcoinExchange(){
	std::ifstream database;
	std::string buffer;

	database.open("data.csv");
	if (!database.is_open()){
		throw std::runtime_error("failed to open the file");
	}
	std::getline(database, buffer);
	if (buffer.compare("date,exchange_rate") || database.eof()){
		throw std::runtime_error("invalid database");
	}
	while(std::getline(database,buffer)){
		this->map.insert(pairs(buffer,","));
	}
	database.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other){
	if (this != &other)
		this->map = other.map;
	return *this;
}

BitcoinExchange::~BitcoinExchange(){}

int check_date(std::string &date){
	if (date.length() != 10)
    return 1;
	size_t pos1 = date.find("-");
  if (pos1 == std::string::npos || pos1 != 4)
    return 1;
  size_t pos2 = date.find("-", pos1 + 1);
  if (pos2 == std::string::npos || pos2 != 7)
    return 1;
	std::string year_str = date.substr(0, pos1);
  std::string month_str = date.substr(pos1 + 1, pos2 - pos1 - 1);
  std::string day_str = date.substr(pos2 + 1);

	for (size_t i = 0; i < year_str.size(); ++i) {
    if (!std::isdigit(year_str[i]))
			return 1;
  }
  for (size_t i = 0; i < month_str.size(); ++i) {
      if (!std::isdigit(month_str[i]))
				return 1;
  }
  for (size_t i = 0; i < day_str.size(); ++i) {
    if (!std::isdigit(day_str[i]))
			return 1;
  }
  int year = stringToint(year_str);
  int month = stringToint(month_str);
  int day = stringToint(day_str);
  if (year < 2009)
      return 1;
  if (month < 1 || month > 12)
    return 1;
  if (day < 1 || day > 31)
    return 1;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
    return 1;
  }
  if (month == 2) {
  bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (day > 29 || (day == 29 && !isLeap)) {
        return 1;
    }
  }
	return 0;
}

float BitcoinExchange::getprice(std::string date){
	std::map<std::string, float>::iterator it;
	for (it = map.begin();it != map.end(); it++){
		if (!it->first.compare(date))
			return it->second;
		if (it->first.compare(date) > 0){
			it--;
			return it->second;
		}
	}
	return 47115.93;
}


void BitcoinExchange::exec(const char* file){
	std::ifstream infile(file);
	std::string buffer;
	std::pair<std::string,float> p;
	float price;

	if (!infile.is_open())
		throw std::runtime_error("Can't open the file");
	std::getline(infile, buffer);
	if (buffer.compare("date | value") || infile.eof())
		throw std::runtime_error("First line is not valid");
	while(std::getline(infile,buffer)){
		try{
			p = pairs(buffer, " | ");
			if (check_date(p.first)){
				std::cout << "Error: bad input => " << p.first << std::endl;
				continue;
			}
		}
		catch (std::exception &e)
		{
			std::cout << "Error: bad input => " << buffer << std::endl;
			continue;
		}
		if (p.second < 0){
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (p.second > 1000){
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		price = getprice(p.first);
		std::cout << std::setprecision(2) << p.first << " => " << p.second << " = " << p.second * price << std::endl;
	}
	infile.close();
}
