#include "noob/rb_tree_nood.hpp"
#include <iostream>
#include "noob/utils_noob.hpp"
#include "noob/map.hpp"

typedef ft::map<float, char *>::value_type T3;

int main()
{
ft::map<float, char *> map;


	std::cout << "know we here" << std::endl;
	map.insert(T3(3, "lol"));
	map.printTree();
	std::cout << std::endl;
	map.insert(T3(4, "lol"));
	map.printTree();
	std::cout << std::endl;
	map.insert(T3(5, "lol"));
	map.printTree();
	
	std::cout << "creation d'un ite" << std::endl;
ft::map<float, char *>::iterator start = map.begin();
ft::map<float, char *>::iterator last = map.end();
	std::cout << "creation de l'ite done" << std::endl;
	std::cout << "num to print :" << *start << std::endl;
	//std::cout << "num end() : " << *last << std::endl;
while (start != map.end())
{
	std::cout << "in ite " << std::endl;
	std::cout << "num to print :" << *start << std::endl;
	start++;
}
while (start != map.begin())
{
	start--;
	std::cout << "in ite " << std::endl;
	std::cout << "num to print :" << *start << std::endl;

}

std::cout << "end of ite++" << std::endl;
	/*
	std::cout << std::endl;
	map.insert(T3(999, "lol"));
	map.printTree();
	std::cout << std::endl;
	map.insert(T3(38238, "lol"));
	map.printTree();
	std::cout << std::endl;
	map.insert(T3(5.2, "lol"));

	map.printTree();
	std::cout << std::endl;
	*/
}
