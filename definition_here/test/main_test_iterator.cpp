#include <iterator>
#include <iostream>
#include <vector>

#include "../randomIterator.hpp"

int main()
{
	

	std::vector<int> ar;
	std::vector<int>::iterator ptr;

	int test = 10;
	int test2[5] = {10,20,30,40,50};
	ft::VectorIterator<int> myptr(&test);
	ft::VectorIterator<int> myptr2(test2);

	for (int i = 0; i < 10; i++)
	{
		ar.push_back(i + 10);
	}

	ptr = ar.begin();
	std::cout << "test iterator true vector" << std::endl;
	std::cout << *ptr++ << std::endl;
	ptr++;
	std::cout << *ptr << std::endl;

	std::cout << std::endl;
	for (std::vector<int>::iterator it = ar.begin(); it != ar.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "end test" << std::endl;

	std::cout << "test print val in vector" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "vector[" << i << "]: " << ar[i] << std::endl;
	}

	std::cout << "end test" << std::endl;
	std::cout << "myiterator: " << *myptr << std::endl;
	std::cout << "test2 iterator" << std::endl;
	while (*myptr2 != 50)
	{
		std::cout << "inside: " << *myptr2 <<std::endl;
		++myptr2;
	}
	while (*myptr2 != 10)
	{
		std::cout << "inside: " << *myptr2 <<std::endl;
		--myptr2;
	}
	while (*myptr2 != 50)
	{
		std::cout << "inside: " << *myptr2 <<std::endl;
		myptr2++;
	}
	while (*myptr2 != 10)
	{
		std::cout << "inside: " << *myptr2 <<std::endl;
		myptr2--;
	}




/*--------------------------------------------------------------------*/


}
