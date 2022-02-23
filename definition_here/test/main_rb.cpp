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
	ft::node<int>*	maxmax= new ft::node<int>(9999999);	
	ft::node<int>*	pmax= new ft::node<int>(33);	


	gp->print_tree();
	std::cout << "first insertion" << std::endl;
	gp->insert(pere);
	std::cout << "yes" << std::endl;
	gp->print_tree();
	gp->insert(mere);
	gp->print_tree();

/*
	pere->back = gp;
	mere->back = gp;
	gp->left = pere;
	gp->right = mere;

	std::cout << "test init node start, value in: " << gp<< std::endl;
	std::cout << "test init node left, value in: " << gp->left<< std::endl;
	std::cout << "test init node right, value in: " << gp->right<< std::endl;

	std::cout << "test init node start, value in: " << pere->back<< std::endl;



	std::cout << std::endl;
	*/




//	gp->print_tree();
	//pere->print_tree();

	mere->insert(oncle_bob);
	gp->print_tree();
	pere->insert(mec_chiant);
	gp->print_tree();
	//std::cout << "insertion d'oscart" << std::endl;
	pere->insert(oscart);

	
	gp->print_tree();
	pere->insert(max);
	gp->print_tree();
	pere->insert(maxmax);
	gp->print_tree();
	//pere->insert(pmax);
	//std::cout << mec_chiant->right << std::endl;
//	mec_chiant->left_rotation();

//	pere->print_tree();
//	mec_chiant->right_rotation();
	pere->print_tree();

	std::cout << "test" << std::endl;
	//mere->right_rotation();

	std::cout << "test" << std::endl;

	pere->print_tree();
	
}
