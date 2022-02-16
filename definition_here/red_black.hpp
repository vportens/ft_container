#ifndef RED_BLACK_HPP
# define RED_BLACK_HPP

#include <cstddef>


namespace ft
{

template<typename T>
struct node{
	typedef T	value;
	node*		back;
	node*		left;
	node*		right;	

	node() : value(), back(nullptr), left(nullptr), right(nullptr) {}

	node(node* back = nullptr, node* left = nullptr,node* right = nullptr ) : back(back), left(left), right(right), value() {}

	
	node(const value& val, node* back = nullptr, node* left = nullptr,node* right = nullptr) :back(back), left(left), right(right), value(val) {}

	node(const node& cpy) : value(cpy.value), back(cpy.back), right(cpy.right), left(cpy.left) {}

	virtual ~node() {}

	node&	operator=(const node& cpy) {
		if (*this == cpy)
			return (*this);
		value = cpy.value;
		back = cpy.back;
		right = cpy.right;
		left = cpy.left;
	}

	bool	operator==(const node& cmp) {
		if (value == cmp.value)
			return (true);
		return (false);
	}
};


template<typename T>
class	rbtree : public node<T>{
	private :

	public :
		typedef typename node<T>*	pointer;
		
		





};

}

#endif
