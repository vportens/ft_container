#ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include <cstddef>
#include <iostream>

namespace ft
{

template<typename T>
struct node{
	typedef T	value_type;
	value_type	value;
	bool		red;
	node*		back;
	node*		left;
	node*		right;	

//	node() : value(), red(0), back(0), left(0), right(0) {}

	node(node* back = 0, node* left = 0,node* right = 0 ) : red(0), back(back), left(left), right(right), value() {}

	
	node(const value_type& val, node* back = 0, node* left = 0,node* right = 0) :red(0), back(back), left(left), right(right), value(val) {}

	node(const node& cpy) : red(cpy.red), value(cpy.value), back(cpy.back), right(cpy.right), left(cpy.left) {}

	virtual ~node() {}

	node&	operator=(const node& cpy) {
		if (*this == cpy)
			return (*this);
		value = cpy.value;
		red = cpy.red;
		back = cpy.back;
		right = cpy.right;
		left = cpy.left;
		return (*this);
	}

	bool	operator==(const node& cmp) {
		if (value == cmp.value)
			return (true);
		return (false);
	}

	std::ostream&	operator<<(std::ostream& out) {
		std::cout << "bite" << std::endl;
		out << &value;

	}
	
	void	left_rotation()
	{
//		ft::node<int> *tmp_p = new ft::node<int>(*(back));
	//	ft::node<int> *tmp_gp = new ft::node<int>(*(tmp_p));
		ft::node<int> *tmp_p = back;
		ft::node<int> *tmp_gp = (back->back);
		tmp_p->left = tmp_gp;
		tmp_p->back = 0;
		tmp_gp->back = tmp_p;
		tmp_gp->right = this;
		this->back = tmp_gp;


	}

	void	right_rotation()
	{
//		ft::node<int> *tmp_p = new ft::node<int>(*(back));
	//	ft::node<int> *tmp_gp = new ft::node<int>(*(tmp_p));
		ft::node<int> *tmp_p = back;
		ft::node<int> *tmp_gp = (back->back);
		tmp_p->right= tmp_gp;
		tmp_p->back = 0;
		tmp_gp->back = tmp_p;
		tmp_gp->left= this;
		this->back = tmp_gp;


	}

	void	insert(node* t)
	{
		if (this->back == 0)
		{
			if (!this->value)
				*this = *t;
			else
			{
				if (!right && this->value < t->value)
				{
					right = t;
					t->back = this;
				}
				else if (!left && value > t->value)
				{
					left = t;
					t->back = this;
				}
				else if (right && value < t->value)
					return (right->insert(t));
				else if (left && value > t->value)
					return (left->insert(t));
			}
			return ;
		}
		if (back)
		{
			std::cout <<"back exist" <<std::endl;
			if (value < back->value)
			{
				std::cout << "left" << std::endl;
				if (t->value < value)
				{
					if (!left)
					{
						left = t;
						t->back = this;
					}
					else
						return (left->insert(t));
					return ;
				}
				else if (t->value > value && back->value > t->value)
				{
					if (!right)
					{
						right = t;
						t->back = this;
					}
					else
						return (right->insert(t));
					return ;
				}
				else
				{
					std::cout << "plop" << std::endl;
					return (back->insert(t));
				}
				return ;
			}
			else
			{
				std::cout << "right" << std::endl;
				if (t->value > value)
				{
					if (!right)
					{
						right = t;
						t->back = this;
					}
					else
						return (right->insert(t));
					return ;
				}
				else if (t->value < value && back->value < t->value)
				{
					std::cout << "oscar" << std::endl;
					if (!left)
					{
						left = t;
						t->back = this;
					}
					else
					{
						std::cout << "1" << std::endl;
						return (left->insert(t));
					}
					return ;
				}
				else
				{
					return (back->insert(t));
				}
				return ;
			}
		}
		return ;
	}
	
	void	print_tree(){
		if (this->back != 0)
			return (this->back->print_tree());
		
		for (int i = 0; i < 60; i++)
			std::cout << " ";
		std::cout << this;
		std::cout << std::endl;

//fichelle echelle 1
		for (int i = 0; i < 60; i++)
			std::cout << " ";
		std::cout << "|" << std::endl;
		for (int i = 0; i < 30; i++)	
			std::cout<< " ";
		for (int i = 0; i < 60; i++)	
			std::cout<< "-";
		std::cout << std::endl;
		for (int i = 0; i < 30; i++)	
			std::cout<< " ";
		std::cout << "|";	
		for (int i = 0; i < 59; i++)	
			std::cout<< " ";
		std::cout << "|"<< std::endl;	
//

		for (int i = 0; i < 30; i++)
			std::cout<< " ";
		std::cout << left;	   ////////////left
		for (int i = 0; i < 59; i++)
			std::cout<< " ";
		std::cout << this->right << std::endl;	 ////////////////right

//fichelle echelle 2
		for (int i = 0; i < 15; i++)
			std::cout << " ";
		for (int i = 0; i < 30; i++)
			std::cout << "-";
		for (int i = 0; i < 30; i++)
			std::cout << " ";
		for (int i = 0; i < 30; i++)
			std::cout << "-";
		std::cout << std::endl;
		for (int i = 0; i < 15; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 28; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 30; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 30; i++)
			std::cout << " ";
		std::cout << "|" << std::endl;
//	
		if (this->left)
			ft::node<int> *left = new ft::node<int>(this->left);
		else
			ft::node<int> *left = new ft::node<int>();	
		if (this->right)
			ft::node<int> *right= new ft::node<int>(this->right);
		else
			ft::node<int> *right= new ft::node<int>();
		
		for (int i = 0; i < 15; i++)
			std::cout << " ";
		std::cout << left->left;
		for	(int i = 0; i < 30; i++) 
		{
			if (i == 0 && !left->left)
				i = 5;
			std::cout << " ";
		}
		std::cout << left->right;

		for (int i = 0; i < 30; i++)
		{
			if (i == 0 && !left->right)
				i = 3;
			std::cout << " ";
		}
		std::cout << right->left;
		for (int i = 0; i < 30; i++)
		{
			if (i == 0 && !right->right)
				i = 3;
			std::cout << " ";
		}
		std::cout << right->right<< std::endl;

//end of step 3



		for (int i = 0; i < 8; i++)
			std::cout << " ";
		for (int i = 0; i < 14; i++)
			std::cout << "-";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		for (int i = 0; i < 14; i++)
			std::cout << "-";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		for (int i = 0; i < 14; i++)
			std::cout << "-";
		for (int i = 0; i < 18; i++)
			std::cout << " ";
		for (int i = 0; i < 14; i++)
			std::cout << "-";
		std::cout  << std::endl;

		
		ft::node<int> *srr = new ft::node<int>();
		if (right->right)
			*srr = *(right->right);

		ft::node<int> *srl = new ft::node<int>();
		if (right->left)
			*srl = *(right->left);
		
		ft::node<int> *slr = new ft::node<int>();
		if ((left->right))
			 *slr = *(left->right);

		ft::node<int> *sll = new ft::node<int>();
		if ((left->left))
			*sll = *(left->left);

		for (int i = 0; i < 8; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 18; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		std::cout << "|";
		std::cout  << std::endl;
	
		for (int i = 0; i < 8; i++)
			std::cout << " ";
		if (sll->left)
		std::cout << sll->left->value; 
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (sll->right)
		std::cout << sll->right->value; 
		else 
			std::cout << " ";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		if (slr->left)
		std::cout << slr->left->value; 
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (slr->right)
		std::cout << slr->right->value; 
		else 
			std::cout << "r";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		if (srl->left)
		std::cout << srl->left->value; 
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (srl->right)
		std::cout << srl->right->value; 
		else 
			std::cout << " ";
			for (int i = 0; i < 16; i++)
			std::cout << " ";
		if (srr->left)
		std::cout << srr->left->value; 
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (srr->right)
		std::cout << srr->right->value; 
		else 
			std::cout << " ";
		std::cout << std::endl;
	
	}
};


template<typename T>
std::ostream&	operator<<(std::ostream& out, const ft::node<T>* t){
	if (t == NULL)
		return (out << "nill");
	return (out << t->value);
}







}

#endif
