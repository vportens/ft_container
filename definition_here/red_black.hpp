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
	bool		not_set;
	node*		back;
	node*		left;
	node*		right;

//	node() : value(), red(0), back(0), left(0), right(0) {}

	node() : not_set(0), red(0), back(NULL), left(NULL), right(NULL), value() {}

	node(const value_type& val) : value(val), red(0), not_set(1), back(0), left(0), right(0) {}
	
	node(const value_type& val, node* back, node* left,node* right ) :red(0), not_set(1), back(back), left(left), right(right) {
		value = val;
	}

	node(const node* cpy) {
		red = cpy->red;
		not_set = cpy->not_set;
		value = cpy->value;
		back = cpy->back;
		right = cpy->right;
		left = cpy->left;
	
	}

	node(const node& cpy) {
		red = cpy.red;
		not_set = cpy.not_set;
		value = cpy.value;
		back = cpy.back;
		right = cpy.right;
		left = cpy.left;
	}

	virtual ~node() {}

	operator node<const T> const() {
		return (node<const T>(value,back, left, right));
	}


	node&	operator=(node& cpy) {
		if (*this == cpy)
			return (*this);
		value = cpy.value;
		red = cpy.red;
		back = cpy.back;
		not_set = cpy.not_set;
		right = cpy.right;
		left = cpy.left;
		return (*this);
	}

	node*	operator=(node* cpy) {
		if (this == cpy)
			return (this);
		this->value = cpy->value;
		this->red = cpy->red;
		this->not_set = cpy->not_set;
		this->back = cpy->back;
		this->right = cpy->right;
		this->left = cpy->left;
		return (this);
	}

	node*	operator=(const node* cpy) {
		if (this == cpy)
			return (this);
		value = cpy->value;
		red = cpy->red;
		not_set = cpy->not_set;
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
		out << &value;

	}
	


	void	left_rotation()
	{
		ft::node<value_type>	*tmp_son = right;
		ft::node<value_type>	*tmp_gson = right->left;

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
		ft::node<value_type>	*tmp_son = left;
		ft::node<value_type>	*tmp_gson = NULL;
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
			if (!not_set)
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
					if (!left)
					{
						left = t;
						t->back = this;
					}
					else
					{
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

		ft::node<value_type> *first;

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
			ft::node<value_type> *parent = t->back;
			if (parent->back)
			{
				ft::node<value_type> *gp = parent->back;
				ft::node<value_type> *oncle;
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
		this->insert_to_good_place(t);
		while (rule(t))
		{
	//		t->print_tree();
			fix_color(t);
		}
	}
		
	node *mini(node *x)
	{
		while (x->left != NULL)
			x = x->left;
		return (x);
	}

	void	swap_some(node *a, node *b)
	{
		if (a->back== NULL)
			return;
		else if (a == a->back->left)
			a->back->left = b;
		else
			a->back->right = b;

		if (b != NULL)
			b->back= a->back;
	}

	void fix_delete_two(node *x)
	{
		node *s;
	
	std::cout << "step1" << std::endl;
	std::cout << x << std::endl;
		s->back = x;
	std::cout << "step1" << std::endl;
		s->red = 0;
	std::cout << "step1" << std::endl;
		s->left = NULL;
	std::cout << "step1" << std::endl;
		s->right= NULL;
	std::cout << "step2" << std::endl;
		if (x->left == NULL)
		{
			std::cout << "test 1" << std::endl;
			x->left = s;
			fix_delete(s);	
		}
		else
		{
			std::cout << "test 2" << std::endl;
			x->right= s;
			fix_delete(s);	
		}
	}

	void fix_delete(node *x)
	{
		node *s;
		
		while (x->back != NULL && x->red == 0)
		{
			if (x == x->back->left)
			{
				s = x->back->right;
				if (s->red == 1)
				{
					s->red = 0;
					x->back->red = 1;
					x->back->left_rotation();
					s = x->back->right;
				}
				if (s->left->red == 0 && s->right->red == 0)
				{
					s->red = 1;
					x = x->back;
				}
				else 
				{
					if (s->right->red == 0)
					{
						s->left->red = 0;
						s->red = 1;
						s->right_rotation();
						s = x->back->right;
					}
					s->red = x->back->red;
					x->back->red = 0;
					s->right->red = 0;
					x->back->left_rotation();
					x->back = NULL;
				}
			}
			else
			{
				s = x->back->left;
				if (s->red == 1)
				{
					s->red = 0;
					x->back->red= 1;
					x->back->right_rotation();
					s = x->back->left;
				}
				if (s->right->red == 0 && s->right->red == 0)
				{
					s->red = 1;
					x = x->back;
				}
				else
				{
					if (s->left->red == 0)
					{
						s->right->red = 0;
						s->red= 1;
						s->left_rotation();
						s = x->back->left;
					}
					s->red = x->back->red;
					x->back->red = 0;
					s->left->red = 0;
					x->back->right_rotation();
					x->back = NULL;
				}
			}
			
		}
		x->red = 0;
	}

	void erase(node *to_erase)
	{
		node *z;
		node *x;
		node *y;
		node *pres;

		pres = to_erase->back;


		int ogColor_y;

		z = to_erase;
		y = z;
		ogColor_y = y->red;
		// first if (z have on son)
		std::cout << "plop" << std::endl;
		if (z->left == NULL)
		{
			std::cout << "plop1" << std::endl;
			x = z->right;
			std::cout << "plop1 bis" << std::endl;
			swap_some(z, z->right);
			std::cout << "plop1 end" << std::endl;
		}
		else if (z->right == NULL)
		{
			std::cout << "plop2" << std::endl;
			x = z->left;
			swap_some(z, z->left);
			std::cout << "plop2 end" << std::endl;
		} // if two son, let do the big tour
		else {
			std::cout << "plop3" << std::endl;
			y = mini(z->right);
			ogColor_y = y->red;
			x = y->right;
			if (y->back == z)
				x->back = y;
			else
			{
				swap_some(y, y->right);
				y->right = z->right;
				y->right->back= y;
			}
			swap_some(z, y);
			y->left = z->left;
			y->left->back= y;
			y->red= z->red;
			std::cout << "plop3 end" << std::endl;
		}
		std::cout << "__________________________________________" << std::endl;
		std::cout << z << std::endl;
		std::cout << y << std::endl;
	//	y->print_tree();	
	
		if (ogColor_y == 0)
		{
			std::cout << "probleme a fixdelete" << std::endl;
			if (x == NULL)
			{
				std::cout << "test solution" << std::endl;
				fix_delete_two(pres);
			}
			else
			{
			std::cout << "---" << std::endl;
			std::cout << x << std::endl;
			std::cout << "plop4" << std::endl;
			fix_delete(x);
			std::cout << "plop4" << std::endl;
			x->print_tree();	
			}
		}			
		delete z;


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
			ft::node<value_type> *left = new ft::node<value_type>(this->left);
		else
			ft::node<value_type> *left = new ft::node<value_type>();	
		if (this->right)
			ft::node<value_type> *right= new ft::node<value_type>(this->right);
		else
			ft::node<value_type> *right= new ft::node<value_type>();
		
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

		
		ft::node<value_type> *srr = new ft::node<value_type>();
		if (right->right)
			*srr = *(right->right);

		ft::node<value_type> *srl = new ft::node<value_type>();
		if (right->left)
			*srl = *(right->left);
		
		ft::node<value_type> *slr = new ft::node<value_type>();
		if ((left->right))
			 *slr = *(left->right);

		ft::node<value_type> *sll = new ft::node<value_type>();
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
			typename ft::node<T>::difference_type
 			operator==(const ft::node<T> ite1, const ft::node<T> ite2) {return (ite1.value == ite2.value);}

			template<typename T, typename T1>
			typename ft::node<T>::difference_type
 			operator==(const ft::node<T> ite1, const ft::node<T1> ite2) {return ite1.value == ite2.value;} 


			template<typename T>
			typename ft::node<T>::difference_type
 			operator!=(const ft::node<T> ite1, const ft::node<T> ite2) {return (ite1.value != ite2.value);}

			template<typename T, typename T1>
			typename ft::node<T>::difference_type
 			operator!=(const ft::node<T> ite1, const ft::node<T1> ite2) {return ite1.value != ite2.value;} 





template<typename T>
std::ostream&	operator<<(std::ostream& out, const ft::node<T>* t){
	if (t == NULL)
		return (out << "nill");
	return (out << t->value);
}










}

#endif
