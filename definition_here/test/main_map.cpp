#include "../red_black.hpp"
#include "../map.hpp"
#include <iostream>
#include "../utils.hpp"

int main()
{
	std::cout << "bonjour main" << std::endl;
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


	std::cout << "all pair made" << std::endl;

	m.insert(test);
	std::cout << "first insert done" << std::endl;

	std::cout << "test end" << std::endl;
	ft::map<char *, int>::iterator last(m.end());
	std::cout << "copy constructor done" << std::endl;
	std::cout << "end :" << last << std::endl;

	m.insert(test1);


	std::cout << "second insert done" << std::endl;
	m.insert(test2);
	std::cout << "last insert done" << std::endl;
	std::cout << "all insert done" << std::endl;

	m.printmap();
	std::cout << m << std::endl;

	std::map<char *, int> real;

	std::cout << "test des iterator" << std::endl;
	real.insert(std::pair<char *,int>(str, 3) );
	real.insert(std::pair<char *,int>(str1, 7) );
	real.insert(std::pair<char *,int>(str2, 9) );


	std::cout << "test des iterator" << std::endl;
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
	std::cout << "test operator = iterator, after: " << std::endl;//*test_egal << std::endl;

	ft::map<char *,int>::iterator debut = m.begin();
	//	std::cout << "test_egal decrementation, test_egal: " << *test_egal << std::endl;
		--test_egal;
		std::cout << "test_egal decrementation, test_egal: " << *test_egal << std::endl;
	while (test_egal != m.begin())
	{
		--test_egal;
		std::cout << "test_egal decrementation, test_egal: " << *test_egal << std::endl;
	//	std::cout << "m.begin resemble a: " << *debut << std::endl;
	}

	// reverse iterator


}

