#include "../red_black.hpp"
#include "../map.hpp"
#include <iostream>
#include "../utils.hpp"

int main()
{
	ft::map<char *, int> m;

	
	ft::pair<char *, int> test;
	ft::pair<char *, int> test1;
	ft::pair<char *, int> test2;
	char *  str = "bonjour";
	char *  str1 = "aurevoir";
	char *  str2 = "baise";

	test = ft::make_pair(str, 3);
	test1 = ft::make_pair(str1, 7);
	test2 = ft::make_pair(str2, 9);
	m.insert(test);
	m.insert(test1);
	m.insert(test2);
	m.printmap();


	std::map<char *, int> real;

	std::cout << m << std::endl;
}

