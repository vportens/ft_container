#include "../vector.hpp"
#include <iostream>
#include <vector>

int main()
{
	ft::vector<int> test;
	std::vector<int> vrai;	

	if (vrai.empty() != test.empty())
		std::cout << "empty fail" << std::endl;	
	std::cout << "capacity of true vector: " << vrai.capacity() << std::endl;
	std::cout << "capacity of false vector: " << test.capacity() << std::endl;
	vrai.reserve(120);
	test.reserve(120);
	std::cout << "reserve done n = 120" << std::endl;
	std::cout << "capacity of true vector: " << vrai.capacity() << std::endl;
	std::cout << "capacity of false vector: " << test.capacity() << std::endl;
	if (vrai.empty() != test.empty())
		std::cout << "empty fail" << std::endl;	
	else
		std::cout << "empty pass" << std::endl;
	std::cout << "max size true vector: " << vrai.max_size() << std::endl;
	std::cout << "max size false vector: " << test.max_size() << std::endl;
	return (0);
}
