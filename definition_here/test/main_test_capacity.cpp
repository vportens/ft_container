#include "../vector.hpp"
#include <iostream>
#include <vector>

template<class T>
int	print_elem(ft::vector<T> lst)
{
	std::cout << "size: " << lst.size() << std::endl;
	std::cout << "capacity: " << lst.capacity() << std::endl;
	size_t n = lst.size();
	for (size_t i = 0; i < n; i++)
	{
		std::cout << "index: " << i << ", nbr: " << lst[i]<< std::endl;
	}
	return (1);
}

template<class T>
int	compare_elements(ft::vector<T> test, std::vector<T> vrai)
{
	size_t n_true =  vrai.size();
	size_t n_false = test.size();

	if (n_true != n_false)
	{
		std::cout << "not the same size" << std::endl;
		return (1);
	}
	for (size_t i = 0; i < n_true; i++)
	{
		if (vrai[i] != test[i])
		{
			std::cout << "vector non identique; a l'indexe :" << i << std::endl;
			std::cout << "vrai[i] = " << vrai[i] << std::endl;
			std::cout << "test[i] = " << test[i] << std::endl;
			return (1);
		}
	}
	std::cout << "vector identique de size: " << n_true << std::endl;
	return (0);
}

void	test_assign(){
	std::vector<int> assi;
	ft::vector<int> test;

	assi.reserve(3);	
	test.reserve(3);
	for (int i = 0; i < 3; i++)
	{
		assi.push_back(i*2 + 10);
		test.push_back(i*2 + 10);
	}
		std::cout << "print new vector for assign" << std::endl;
	std::cout << "size befor assigne " << assi.size()<< std::endl;
	std::cout << "capacity befor assigne " << assi.capacity() << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << " " << assi[i];
	}
	std::cout << std::endl;
	std::cout << "size befor assigne test " << test.size()<< std::endl;
	std::cout << "capacity befor assigne test " << test.capacity() << std::endl;
	for (int i = 0; i < 15; i++)
	{
		std::cout << " " << test[i];
	}
	std::cout << std::endl;

	assi.assign(7, 15);
	test.assign(7, 15);
	for (int i = 0; i < 15; i++)
	{
		std::cout << " " << assi[i];
	}
	std::cout << std::endl;
	std::cout << "size after assigne " << assi.size() << std::endl;
	std::cout << "capacity after assigne " << assi.capacity() << std::endl;
	for (int i = 0; i < 15; i++)
	{
		std::cout << " " << test[i];
	}
	std::cout << std::endl;
	std::cout << "size after assigne " << test.size() << std::endl;
	std::cout << "capacity after assigne " << test.capacity() << std::endl;


	


}

void	test_insert() {
	std::vector<int> vec(3, 100);
	std::vector<int>::iterator ite;

	std::vector<int> vec26(3, 100);
	std::vector<int>::iterator ite26;

	ite = vec.end();
	ite = vec.insert(ite, 60);


	ite26 = vec26.end();
	ite26 = vec26.insert(ite26, 60);

	std::cout << "tests : " << (ite26 < ite) << "houlalalalallallalaal:" << std::endl;
	for (int i = 0; i < vec.size(); i++)
		std::cout << " " << vec[i];
	std::cout << std::endl;
	std::cout << "after insert, capacity: " << vec.capacity() << std::endl;
	std::cout << "after insert, size: " << vec.size() << std::endl;
	std::cout << "ou poite ite: " << *ite<< std::endl;

	ft::vector<int> myvec(3, 100);
	ft::vector<int>::iterator myite;

	myite = myvec.end();
	myite = myvec.insert(myite, 60);
	for (int i = 0; i < myvec.size(); i++)
		std::cout << " " << myvec[i];
	std::cout << std::endl;
	std::cout << "after insert, capacity: " << myvec.capacity() << std::endl;
	std::cout << "after insert, size: " << myvec.size() << std::endl;
	std::cout << "ou poite ite: " << *myite<< std::endl;


	std::vector<int> vec2(3, 100);	
	std::vector<int>::iterator ite2;

	ite2 = vec2.begin();
	vec2.insert(ite2, 10, 300);	

	for (int i = 0; i < vec2.size(); i++)
		std::cout << " " << vec2[i];
	std::cout << std::endl;
	std::cout << "after insert, capacity: " << vec2.capacity() << std::endl;
	std::cout << "after insert, size: " << vec2.size() << std::endl;


	ft::vector<int> myvec2(3, 100);
	ft::vector<int>::iterator myite2;

	myite2 = myvec2.begin();
	myvec2.insert(myite2,10 ,  300);
	for (int i = 0; i < myvec2.size(); i++)
		std::cout << " " << myvec2[i];
	std::cout << std::endl;
	std::cout << "after insert, capacity: " << myvec2.capacity() << std::endl;
	std::cout << "after insert, size: " << myvec2.size() << std::endl;

	std::vector<int> myvec3;

	std::vector<int>::iterator ite3;
	ite3 = myvec3.end();
	std::cout << *ite3 << std::endl;


	
	
}


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
	test.push_back(10);
	vrai.push_back(10);
	std::cout << test[0] << std::endl;
	std::cout << vrai[0] << std::endl;
	std::cout << "is test empty? " << test.empty() << std::endl;
	std::cout << "is vrai empty? " << vrai.empty() << std::endl;
	std::cout << "capacity of true vector: " << vrai.capacity() << std::endl;
	std::cout << "capacity of false vector: " << test.capacity() << std::endl;
	std::cout << "size of true vector: " << vrai.size() << std::endl;
	std::cout << "size of false vector: " << test.size() << std::endl;
	std::cout << test[-1] << std::endl;
	std::cout << vrai[-1] << std::endl;
	std::cout << test[10] << std::endl;
	std::cout << vrai[10] << std::endl;
	std::cout << test[130] << std::endl;
	std::cout << vrai[130] << std::endl;
	std::cout << "-------------------------------" << std::endl;
	
	ft::vector<int> test2;
	std::vector<int> vrai2;

	vrai2.reserve(10);
	test2.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		
	test2.push_back(i * 2 + 29);
	vrai2.push_back(i * 2 + 29);
	}
	std::cout << "size and capacity true vector: " << vrai2.size() << "; " << vrai2.capacity()<< std::endl;
	std::cout << "size and capacity false vector: " << test2.size() << "; " << test2.capacity()<< std::endl;
	
	test2.push_back(10);
	vrai2.push_back(10);
	std::cout << "size and capacity true vector: " << vrai2.size() << "; " << vrai2.capacity()<< std::endl;
	std::cout << "size and capacity false vector: " << test2.size() << "; " << test2.capacity()<< std::endl;
	compare_elements(test2, vrai2);
	test2.pop_back();
	vrai2.pop_back();
	compare_elements(test2, vrai2);

// pop_back vector null
	ft::vector<int> pop;
	std::vector<int> back;
	pop.pop_back();
	back.pop_back();

	test2.swap(test);
	std::cout << "print test" << std::endl;
	print_elem(test);
	std::cout << "print test2" << std::endl;
	print_elem(test2);

	std::vector<double> t;
	ft::vector<double> tt;
	std::vector<int> r;

	test_insert();
	std::cout << "difference entre test[0] et test.front()" << std::endl;
	std::cout << test[0] << std::endl;
	std::cout << test.front() << std::endl;
	
	std::cout << "difference entre test[test.size() -1] et test.back()" << std::endl;
	std::cout << test[test.size() - 1] << std::endl;
	std::cout << test.back() << std::endl;
	//std::cout << "test de back dun vector vide: " << t.back() << std::endl; le vrai vector segfault
	//std::cout << "test de back dun faux vector vide: " << tt.back() << std::endl;


	test_assign();

	return (0);
}
