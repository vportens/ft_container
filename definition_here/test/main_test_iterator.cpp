#include <iterator>
#include <iostream>
#include <vector>

#include "../randomIterator.hpp"
#include "../vector.hpp"

void	test_random() {
	std::vector<double> vec;
	std::vector<double>::iterator ite;
	std::vector<double>::iterator ite2;

	int test[5] = {2,4,6,8,10};
	ft::VectorIterator<int> myptr(test);
	ft::VectorIterator<int> sec;

	std::cout << "my vector operator +=" << std::endl;
	myptr += 2;
	std::cout << *myptr << std::endl; 
	myptr -=2;
	std::cout << *myptr << std::endl; 
	if (myptr > sec)
		std::cout << "operator > valide" << std::endl;

	if (sec< myptr )
		std::cout << "operator > valide" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "my ite [" << i << "]: " << myptr[i] << std::endl;
	}
	
//	sec =  2 + myptr;
	
	for (int i = 1; i < 6; i++)
	{
		vec.push_back(i * 2);
	}
	ite = vec.begin();
	ite2 = 2 + ite;	
	if (ite > ite2)
		std::cout << "test operator >" << std::endl;	
	std::cout << *ite << " " << *ite2 << std::endl;
}

void	test_output_ite() {
	std::vector<int> vec;
	std::vector<int>::iterator  ite;
	int test[5] = {2,4,6,8,10};
	ft::VectorIterator<int> myptr(test);

	for (int i = 1; i < 6; i++)
	{
		vec.push_back(i * 2);
	}
	ite = vec.begin();
	std::cout << "before: " << *ite << std::endl;
	*ite++ = 15;
	std::cout << "after: " << *ite<<std::endl;
	std::cout << "before: " << *myptr << std::endl;	
	*myptr++ = 15;
	std::cout << "after: " << *myptr << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << *(myptr + i) << " ";
		std::cout << *(ite + i) << std::endl;	
	}
	
	
}

int	test_forward()
{
	std::vector<int> vec;
	std::vector<int>::iterator  ite;
	std::vector<int>::iterator	ite2;

	int test[5] = {2,4,6,8,10};
	ft::VectorIterator<int> myptr(test);
	ft::VectorIterator<int> myptr2;

	for (int i = 1; i < 6; i++)
	{
		vec.push_back(i * 2);
	}
	ite = vec.begin();
	ite2 = ite;
	*ite++;
	std::cout << "ite: "<< *ite << std::endl;
	std::cout << "ite2: " << *ite2<< std::endl;
	
	myptr2 = myptr;
	*myptr++;
	std::cout << "myptr: "<< *myptr<< std::endl;
	std::cout << "myptr2: " << *myptr2<< std::endl;
	return (0);

}

template<class T>
int	test_issameiterator(ft::VectorIterator<T> good,ft::VectorIterator<T> copy)
{
	for (int i = 0; i < 5; i++)
	{
		if (*good != *copy)
		{
			std::cout << "not the same iterator" << std::endl;
			return (1);
		}
		good++;
		copy++;
	}
	return (0);
}

template<class T>
int	test_preincrementation(ft::VectorIterator<T> myite, typename std::vector<T>::iterator ite)
{
	for (int i = 0; i < 5; i++)
	{
		if (*myite != *ite)
		{
			std::cout << "preincrementation error" << std::endl;
			return (1);
		}
		++myite;
		++ite;
	}	
	std::cout << "preincrementation good !!" << std::endl;
	return (0);

}

template<class T>
int	test_predecrementation(ft::VectorIterator<T> myite, typename std::vector<T>::iterator ite)
{
	for (int i = 0; i < 5; i++)
	{
		if (*myite != *ite)
		{
			std::cout << "predecrementation error" << std::endl;
			return (1);
		}
		--myite;
		--ite;
	}	
	std::cout << "predecrementation good !!" << std::endl;
	return (0);

}

template<class T>
int	test_postincrementation(ft::VectorIterator<T> myite, typename std::vector<T>::iterator ite)
{
	for (int i = 0; i < 5; i++)
	{
		if (*myite != *ite)
		{
			std::cout << "postincrementation error" << std::endl;
			std::cout << "test value: " << *myite<< std::endl;
			std::cout << "true value: " << *ite<< std::endl;
			return (1);
		}
		myite++;
		ite++;
	}	
	std::cout << "preincrementation good !!" << std::endl;
	return (0);

}

template<class T>
int	test_postdecrementation(ft::VectorIterator<T> myite, typename std::vector<T>::iterator ite)
{
	for (int i = 0; i < 5; i++)
	{
		if (*myite != *ite)
		{
			std::cout << "postdecrementation error" << std::endl;
			return (1);
		}
		myite--;
		ite--;
	}	
	std::cout << "predecrementation good !!" << std::endl;
	return (0);

}


void	test_distance(){
	std::vector<double> test;


	for (int i = 0; i< 10 ; i++)	test.push_back(i * 10);
	std::vector<double>::iterator first = test.begin();
	std::vector<double>::iterator last = test.end();


	std::cout << "the distance is: " << std::distance(first, last) << std::endl;

	ft::vector<double> test2;
	for (int i = 0; i< 10 ; i++)	test2.push_back(i * 10);
	ft::VectorIterator<double> first2 = test2.begin();
	ft::VectorIterator<double> last2 = test2.end();
	std::cout << "the distance is: " << ft::distance(first2, last2) << std::endl;

}

int main()
{
	

	std::vector<int> ar;
	std::vector<int>::iterator ptr;

	int test = 10;
	int test2[5] = {10,20,30,40,50};
	ft::VectorIterator<int> myptr(&test);
	ft::VectorIterator<int> myptr2(test2);

	std::vector<int>::iterator it(test2);

	for (int i = 0; i < 10; i++)
	{
		ar.push_back(i + 10);
	}

	ptr = ar.begin();
	std::cout << "test iterator true vector" << std::endl;
	std::cout << *ptr++ << std::endl;
//	ptr++;
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
// ++a, a++, --a, a--, a + integer
	std::cout << "test2 iterator incrementation decrementation" << std::endl;
	test_preincrementation(myptr2, it);
	test_predecrementation(myptr2 + 4, it + 4);
	test_postincrementation(myptr2, it);
	test_postdecrementation(myptr2 + 4, it + 4);
// operator =
	std::cout << "test operator =" <<std::endl;
	ft::VectorIterator<int> egal;
	egal = myptr2;
	if (test_issameiterator(myptr2, egal) == 0)
		std::cout << "test operator = valide" << std::endl;
// constructor by cpy
	std::cout << "test constructor by cpy" << std::endl;
	ft::VectorIterator<int> cpy(myptr2);
	if (test_issameiterator(myptr2, cpy) == 0)
		std::cout << "test constructor by cpy valide" << std::endl;
// ==, !=	
	std::cout << "test == & !=" << std::endl;
	if (myptr2 == cpy)
		std::cout << "== true valide " << std::endl;
	if (myptr2 == myptr) 
		std::cout << "== false invalide" << std::endl;
	else
		std::cout <<"== false valide" << std::endl;
	if (myptr2  != cpy)
		std::cout << "!= false invalide" << std::endl;
	else
		std::cout << "!= false  valide" << std::endl;
	if (myptr2 != myptr)
		std::cout << "!= true valide" << std::endl;
	else
		std::cout << "!= false invalide"<< std::endl;

//*a = t
	test_output_ite();
	test_forward();
	test_random();

	test_distance();
/*--------------------------------------------------------------------*/


}
