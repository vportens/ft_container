#include "noob/rb_tree_nood.hpp"
#include <iostream>
#include "noob/utils_noob.hpp"
#include "noob/map_noob.hpp"

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
