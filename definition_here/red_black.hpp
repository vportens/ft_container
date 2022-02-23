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

	node*	operator=(const node* cpy) {
		if (this == cpy)
			return (this);
		value = cpy->value;
		red = cpy->red;
		back = cpy->back;
		right = cpy->right;
		left = cpy->left;
		return (this);
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
		ft::node<int>	*tmp_son = right;
		ft::node<int>	*tmp_gson = right->left;

		tmp_son->back = back;
		if (back)
		{
			if (back->value > value)
				back->left = tmp_son;
			else
				back->right = tmp_son;
		}
		tmp_son->left = this;
		back = tmp_son;
		right = tmp_gson;
		if (tmp_gson)
			tmp_gson->back = this;

	}

	void	right_rotation()
	{
		ft::node<int>	*tmp_son = left;
		ft::node<int>	*tmp_gson;
		if (left)
			tmp_gson = left->right;

		tmp_son->back = back;
		if (back)
		{
			if (back->value > value)
				back->left = tmp_son;
			else
				back->right= tmp_son;
		}
		tmp_son->right= this;
		back = tmp_son;
		left = tmp_gson;
		if (tmp_gson)
			tmp_gson->back = this;

	}

	void	insert_to_good_place(node *t)
	{
		if (this->back == 0)
		{
			if (!this->value)
			{
				*this = *t;
			}
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
			if (value < back->value)
			{
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

	int rule(node *t)
	{
		if (t->back && t->back->red)
			return 1;

		ft::node<int> *first;

		first = t;
		while (first->back)
		{
			if (first->back->red && first->red)
			{
				fix_color(first);
				return (0);
			}
			first = first->back;
		}
		if (first->red)
		{
			fix_color(first);
			return (0);
		}
		return (0);

	}

	void	fix_color(node* t)
	{
		if (!t->back)
		{
			t->red = 0;
			return ;	
		}
		else if (t->back)
		{
			ft::node<int> *parent = t->back;
			if (parent->back)
			{
				ft::node<int> *gp = parent->back;
				ft::node<int> *oncle;
				if (parent->value < gp->value)
					oncle = gp->right;
				else
					oncle = gp->left;
				if (oncle && oncle->red) //case 1
				{
					if (gp->red)
						gp->red = 0;
					else
						gp->red = 1;
					if (parent->red)
						parent->red = 0;
					else
						parent->red = 1;
					oncle->red = 0;
				}
				else if (!oncle || oncle->red == 0)
				{
					if ((gp->value < parent->value && parent->value > t->value)) //|| (gp->value > parent->value && parent->value < t->value)) // case 2
					{
						parent->right_rotation();	
					}
					else if (gp->value > parent->value && parent->value < t->value)
						parent->left_rotation();
					else if (gp->value < parent->value && parent->value < t->value) // casse 3
					{
						gp->left_rotation();
						if (gp->red)
							gp->red = 0;
						else
							gp->red = 1;
						if (parent->red)
							parent->red = 0;
						else
							parent->red = 1;
					}
					else if (gp->value > parent->value && parent->value > t->value)
					{
						gp->right_rotation();
						if (gp->red)
							gp->red = 0;
						else
							gp->red = 1;
						if (parent->red)
							parent->red = 0;
						else
							parent->red = 1;

					}
					rule(parent);
				}
			}
	
		}
	}

	void	insert(node* t)
	{
		t->red = 1;
		insert_to_good_place(t);
		while (rule(t))
		{
			std::cout << "go to fix" << std::endl;
			t->print_tree();
			fix_color(t);
		}
	}
		

	
	void	print_tree(){
		if (this->back != 0)
			return (this->back->print_tree());
		
		for (int i = 0; i < 60; i++)
			std::cout << " ";
		std::cout << this;
		if (this->red)
			std::cout << "red";
		else 
			std::cout << "black";
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
		if (left)
		{
		if (left->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		for (int i = 0; i < 59; i++)
			std::cout<< " ";
		std::cout << this->right ;	 ////////////////right
		if (right)
		{
		 if (right->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		std::cout << std::endl;


		if (!left && !right)
			return ;
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
		
		if (left)
		{
		if (left->left)
		{
		std::cout << left->left;
		 if (left->left->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		for	(int i = 0; i < 30; i++) 
		{
			if (i == 0 && !left->left)
				i = 5;
			std::cout << " ";
		}
		if (left->right)
		{
		std::cout << left->right;
		 if (left->right->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		}
		for (int i = 0; i < 30; i++)
		{
			if (i == 0 && !left->right)
				i = 3;
			std::cout << " ";
		}
		if (right)
		{
		 if (right->left)
		 {
		std::cout << right->left;
		 if (right->left->red)
			std::cout << "red";
		else
			std::cout << "black";
		 }
		for (int i = 0; i < 30; i++)
		{
			if (i == 0 && !right->right)
				i = 3;
			std::cout << " ";
		}
		if (right->right)
		{
		std::cout << right->right;
		 if (right->right->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		}
		std::cout << std::endl;

		if (!left || !right)
		{
			if (!left)
			{
				if (!right->left && !right->right)
					return;
			}
			if (!right) 
			{
					if (!left->left && !left->right)
						return ;

			}
		}
		if (!left->left && !left->right && !right->left && !right->right)
			return ;

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
		{
		std::cout << sll->left->value; 
		if (sll->left->red)
			std::cout << "red";
		else
			std::cout << "black";
		}

		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (sll->right)
		{
		std::cout << sll->right->value; 
		if (sll->right->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		else 
			std::cout << " ";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		if (slr->left)
		{
		std::cout << slr->left->value; 
		if (slr->left->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (slr->right)
		{
		std::cout << slr->right->value; 
		if (slr->right->red)
			std::cout << "red";
		else 
			std::cout << "black";
		}
		else 
			std::cout << "r";
		for (int i = 0; i < 16; i++)
			std::cout << " ";
		if (srl->left)
		{
		std::cout << srl->left->value; 
		if (srl->left->red)
			std::cout << "red";
		else 
			std::cout << "black";
	
		}
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (srl->right)
		{
		std::cout << srl->right->value; 
		if (srl->right->red)
			std::cout << "red";
		else
			std::cout << "black";

		}
		else 
			std::cout << " ";
			for (int i = 0; i < 16; i++)
			std::cout << " ";
		if (srr->left)
		{
		std::cout << srr->left->value; 
		if (srr->left->red)
			std::cout << "red";
		else	
			std::cout << "black";
		}
		else 
			std::cout << " ";
		for (int i = 0; i < 12; i++)
			std::cout << " ";
		if (srr->right)
		{
		std::cout << srr->right->value; 
		if (srr->right->red)
			std::cout << "red";
		else
			std::cout << "black";
		}
	
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
