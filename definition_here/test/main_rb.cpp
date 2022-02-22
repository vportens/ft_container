#include "../red_black.hpp"
#include <iostream>

int main()
{
	ft::node<int>*	gp = new ft::node<int>(2);	
	ft::node<int>*	pere = new ft::node<int>(1);	
	ft::node<int>*	mere = new ft::node<int>(9);	
	ft::node<int>*	oncle_bob = new ft::node<int>(44);	
	ft::node<int>*	mec_chiant= new ft::node<int>(5);	
	ft::node<int>*	oscart = new ft::node<int>(6);	
	ft::node<int>*	max= new ft::node<int>(99999);	


	pere->back = gp;
	mere->back = gp;
	gp->left = pere;
	gp->right = mere;

	std::cout << "test init node start, value in: " << gp<< std::endl;
	std::cout << "test init node left, value in: " << gp->left<< std::endl;
	std::cout << "test init node right, value in: " << gp->right<< std::endl;

	std::cout << "test init node start, value in: " << pere->back<< std::endl;



	std::cout << std::endl;




//	gp->print_tree();
	//pere->print_tree();

	mere->insert(oncle_bob);
	pere->insert(mec_chiant);
	std::cout << "insertion d'oscart" << std::endl;
	pere->insert(oscart);
	pere->insert(max);
	std::cout << mec_chiant->right << std::endl;
	mec_chiant->left_rotation();

	pere->print_tree();
	mec_chiant->right_rotation();
	pere->print_tree();
}
