#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
//using namespace std;


int main()
{
	std::string filter_name;
	std::cout << "Enter filter filepath: " << std::endl;
	std::getline(std::cin, filter_name);
	std::string input_file_name;
	std::cout << "Enter input filepath: " << std::endl;
	std::getline(std::cin, input_file_name);
	std::unordered_set<std::string> filter;
	std::ifstream file;
	file.open(filter_name);
	if (!file.is_open())
	{
		std::cerr << "Cant open the filter file" << std::endl;
	}

	std::string word;
	while (file >> word)
	{
		filter.insert(word);
	}
	file.close();
	std::ifstream input;
	input.open(input_file_name);
	if (!input.is_open())
	{
		std::cerr << "Cant open input file" << std::endl;
	}
	std::unordered_multimap<std::string, int> input_words;
	int line_counter = 1;
	while (!input.eof())
	{
		std::string line;
		std::getline(input, line);
		std::istringstream iss(line);
		std::string word2;
		while (iss >> word2)
		{
			std::unordered_set<std::string>::const_iterator contains = filter.find(word2);
			if (contains == filter.end())
			{
				input_words.insert(std::pair<std::string, int>(word2, line_counter));
			}
		}
		line_counter++;
	}
	input.close();
	while (1)
	{
		std::string searched;
		std::getline(std::cin, searched);
		std::unordered_multimap<std::string, int>::const_iterator contains = input_words.find(searched);
		if (contains == input_words.end())
		{
			std::cout << "no occurrences found" << std::endl;
		}
		else
		{
			auto range = input_words.equal_range(searched);
			int counter = 0;
			for (auto i = range.first; i != range.second; i++)
			{
				if (counter >= 1)
				{
					std::cout << ", " << i->second;
				}
				else
				{
					std::cout << i->second;
				}
				counter++;
			}
			std::cout << std::endl;
		}
	}
	return 0;
}

