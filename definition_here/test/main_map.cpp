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
	char   str[] = "bonjour";
	char   str1[] = "aurevoir";
	char   str2[] = "baise";

	test = ft::make_pair(str, 3);
	test1 = ft::make_pair(str1, 7);
	test2 = ft::make_pair(str2, 9);
	m.insert(test);
	m.insert(test1);
	m.insert(test2);
	m.printmap();
	std::cout << m << std::endl;

	std::map<char *, int> real;

	real.insert(std::pair<char *,int>(str, 3) );
	real.insert(std::pair<char *,int>(str1, 7) );
	real.insert(std::pair<char *,int>(str2, 9) );


	for (std::map<char *, int>::iterator it = real.begin(); it != real.end(); it++)
		std::cout << it->first << ", " << it->second << std::endl;

	ft::map<char *, int>::iterator it = m.begin();
	std::cout << "test iterator begin: " << (*it) << std::endl;


	++it;
	std::cout << "test iterator begin++: " << (*it) << std::endl;

	it++;
	std::cout << "test iterator begin++: " << (*it) <<  std::endl;


	ft::map<char *, int>::iterator test_egal = m.begin();

	std::cout << "test operator = iterator, befor: " << *test_egal << std::endl;
	test_egal = m.end();
	std::cout << "test operator = iterator, after: " << *test_egal << std::endl;
}

