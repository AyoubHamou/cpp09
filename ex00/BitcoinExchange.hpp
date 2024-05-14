#pragma once

#include <fstream>
#include <map>
#include <iostream>


class BitcoinExchange{
private:
	std::map<std::string, float> map;

public:
	BitcoinExchange();
  BitcoinExchange(const BitcoinExchange& other);
  BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void exec(const char* infile);
	float getprice(std::string);
};

int check_date(std::string &date);
std::pair<std::string,float> pairs(std::string &input, std::string del);
float stringTofloat(const std::string &str);
