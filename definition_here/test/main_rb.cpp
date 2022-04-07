#include "../rb_tree_nood.hpp"
#include <iostream>
#include "../utils.hpp"

int main()
{
	std::cout << "first insertion" << std::endl;
/*	ft::Node<float>*	gp = new ft::Node<float>(2);	
	ft::Node<float>*	pere = new ft::Node<float>(1);	
	ft::Node<float>*	mere = new ft::Node<float>(9.48);	
	ft::Node<float>*	oncle_bob = new ft::Node<float>(44);	
	ft::Node<float>*	mec_chiant= new ft::Node<float>(5);	
	ft::Node<float>*	oscart = new ft::Node<float>(6);	
	ft::Node<float>*	max= new ft::Node<float>(99999);	
	ft::Node<float>*	maxmax= new ft::Node<float>(9999999);	
	ft::Node<float>*	pmax= new ft::Node<float>(33);	
	ft::Node<float>*	tran = new ft::Node<float>(8);	
*/

	gp->printTree();
	std::cout << "first insertion" << std::endl;
	gp->insert(pere);
	std::cout << "yes" << std::endl;
	gp->printTree();
	gp->insert(mere);
	gp->printTree();

/*
	pere->back = gp;
	mere->back = gp;
	gp->left = pere;
	gp->right = mere;

	std::cout << "test init Node start, value in: " << gp<< std::endl;
	std::cout << "test init Node left, value in: " << gp->left<< std::endl;
	std::cout << "test init Node right, value in: " << gp->right<< std::endl;

	std::cout << "test init Node start, value in: " << pere->back<< std::endl;



	std::cout << std::endl;
	*/




//	gp->print_tree();
	//pere->print_tree();

	mere->insert(oncle_bob);
	gp->printTree();
	pere->insert(mec_chiant);
	gp->printTree();
	//std::cout << "insertion d'oscart" << std::endl;
	pere->insert(oscart);

	
	gp->printTree();
	pere->insert(max);
	gp->printTree();
	pere->insert(maxmax);
	gp->printTree();
	pere->insert(tran);
	gp->printTree();
	pere->insert(pmax);
	gp->printTree();

	//std::cout << mec_chiant->right << std::endl;
//	mec_chiant->left_rotation();

//	pere->print_tree();
//	mec_chiant->right_rotation();


	pere->printTree();
	
	ft::pair<char, int> test;
	test = ft::make_pair<char, int>('c', 10);
	std::cout << "pair test: " << test.first << ", " << test.second << std::endl;

	ft::Node<ft::pair<char, int> > test2(test);
	(&test2)->printTree();
}
