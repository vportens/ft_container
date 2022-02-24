#include "../red_black.hpp"
#include <iostream>

int main()
{
	ft::node<float>*	gp = new ft::node<float>(2);	
	ft::node<float>*	pere = new ft::node<float>(1);	
	ft::node<float>*	mere = new ft::node<float>(9.48);	
	ft::node<float>*	oncle_bob = new ft::node<float>(44);	
	ft::node<float>*	mec_chiant= new ft::node<float>(5);	
	ft::node<float>*	oscart = new ft::node<float>(6);	
	ft::node<float>*	max= new ft::node<float>(99999);	
	ft::node<float>*	maxmax= new ft::node<float>(9999999);	
	ft::node<float>*	pmax= new ft::node<float>(33);	
	ft::node<float>*	tran = new ft::node<float>(8);	


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
	pere->insert(tran);
	gp->print_tree();
	pere->insert(pmax);
	gp->print_tree();

	//std::cout << mec_chiant->right << std::endl;
//	mec_chiant->left_rotation();

//	pere->print_tree();
//	mec_chiant->right_rotation();


	pere->print_tree();
	
}
