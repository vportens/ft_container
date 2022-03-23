#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include "reverse_iterator.hpp"

namespace ft
{
	template <typename pair, class node>
	class btree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, pair>
	{
		public :
			typedef pair value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		node * _node;
		node * _back;
	//	compare _comp;

	//	btree_iterator(T *lala, compare const &lsl) : _node(lala), _comp(lsl) {}


//		btree_iterator(const btree_iterator& btree_it) : _node(btree_it._node), _comp() {}
//		btree_iterator(const ft::btree_const_iterator<T,  compare>& it) : _node(it._node), _comp() {}
		btree_iterator() : _node(NULL), _back(NULL) {}

	//	btree_iterator (const btree_iterator &cpy)  : _node(cpy._node){}

		btree_iterator(node *x, node* y) : _node(x), _back(y) {}
		
		btree_iterator<pair, node> (const btree_iterator<pair, node> &cpy)  : _node(cpy._node), _back(cpy._back) {}
		
	//	btree_iterator<pair, node> (const btree_iterator<pair, node> &cpy)  : _node(cpy._node){}

		btree_iterator (node *cpy) : _node(cpy), _back(cpy->back) {}

		virtual ~btree_iterator() {}

		btree_iterator &operator=(const btree_iterator &cpy) {
			_node = cpy._node;
			_back = cpy._back;
			return (*this);
		}

		operator btree_iterator<const pair, node>() const {
			return btree_iterator<const pair, node>(_node, _back);
		}


	value_type getter(){ return _node;}
/*		btree_iterator& operator=(const btree_const_iterator& cpy) {
			if (*this == cpy)
				return (*this);
			_node = cpy._node;
			_comp = cpy._comp;
			return (*this);
		}
	*/

		bool operator==(const btree_iterator& it) {
			return (_node == it._node);
		}

		
		bool operator!=(const btree_iterator& it) {
			return (_node != it._node);
		}
		

	
		btree_iterator& operator++(void) {

			node *start = _node;

			if (_node == NULL)
				return (*this);
			if (_node->right)
			{
				_back = _node;
				start = _node->right;
				while (start->left)
				{
					_back = start;
					start = start->left;
				}
				_node = start;
				return (*this);
			}
			else {
				node *prec = _node;
				start = _node->back;
				while (start && start->value < prec->value)
					start = start->back;
				if (start == NULL)
				{
					_back = prec;
					_node = NULL;
					return (*this);
				}
				else
				{
					_node = start;
					_back = _node->back;
					return (*this);
				}
			}
			return (*this);
			/*
			node * start = _node;

			if (_node->right)
			{
				start = _node->right;
				while (start->left)
					start = start->left;
				_node = start;
				if (_node->back)
					_back = _node->back;
				return (*this);
			}
			else
			{
				node *prec = _node;
				if (_node->back)
				{
					start = _node->back;
					while (start->back && prec == start->right)
					{
						prec = start;
						start = start->back;
						
						if (_node->back)
							_back = _node->back;
					}
					if (!start->back && prec == start->right)
					{
						while(start->right)
						{
							start = start->right;
						}
						_back = start;
						start = start->right;
						_node = start;
						return (*this);
					}
					else {
						_node = start;
						if (_node->back)
							_back = _node->back;
						return (*this);
					}
				}
				else
					return (*this);
			}
			return (*this); */
		}

		btree_iterator	operator++(int){
			btree_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		btree_iterator& operator--(void) {
			node * start = _node;

			if (_node == NULL && _back)
			{
				_node = _back;
				_back = _back->back;
				return (*this);
			}
			if (_node->left)
			{
				start = _node->left;
				while (start->right)
					start = start->right;
				_node = start;
				if (_node->back)
					_back = _node->back;
				return (*this);
			}
			else
			{
				node *prec = _node;
				if (start->back == NULL)
				{
					return (*this);
				}
				start = start->back;
				while (start->back && start->left == prec)
				{
					prec = start;
					start = start->back;
				}
				_node = start;
				_back = start->back;
				return (*this);
			/*
				if (start->back == NULL)
					return (*this);
				start = start->back;
				node *prec = _node;
				while (start->back && prec == start->right)
				{
					prec = start;
					start = start->back;
					if (_node->back)
						_back = _node->back;
				}
				if (!start->back && prec == start->right)
					return (*this);
				else {
					_node = start;
					if (_node->back)
						_back = _node->back;
					return (*this);
				}
				*/
			}
			return (*this);
		}

		btree_iterator operator--(int)
		{
			btree_iterator tmp(*this);
			operator--();
			return tmp;
		}

		reference operator*() const {
			return _node->value;
		}


		pointer operator->() const {
			return ((&this->operator*()));
		}

		void	operator<<(reference &test){
		if (test == NULL)
		{
			(std::cout << "nill");
			return ;
		}
		(std::cout << test._node);
			return ;
		}



		template <class, class>
		friend class btree_iterator;
	};

/*
template <typename T, typename node_type>
btree_iterator<T, node_type>::btree_iterator(node_type *src) { this->_node = src; }


template <typename T, typename node_type>
btree_iterator<T, node_type>::btree_iterator(const node_type &src) { this->_node = src; }
*/
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, ft::btree_iterator<T1, T2>& to_print){
	out << "node value :" << to_print._node;
	return out;
}


			template<typename T, typename compare>
			typename ft::btree_iterator<T, compare>::difference_type
 			operator==(const ft::btree_iterator<T, compare> ite1, const ft::btree_iterator<T, compare> ite2) {return (ite1._node == ite2._node);}

			template<typename T, typename compare, typename T1>
			typename ft::btree_iterator<T, compare>::difference_type
 			operator==(const ft::btree_iterator<T, compare> ite1, const ft::btree_iterator<T1, compare> ite2) {return ite1._node == ite2._node;} 


			template<typename T, typename compare>
			typename ft::btree_iterator<T, compare>::difference_type
 			operator!=(const ft::btree_iterator<T, compare> ite1, const ft::btree_iterator<T, compare> ite2) {return (ite1._node != ite2._node);}

			template<typename T,typename compare,  typename T1>
			typename ft::btree_iterator<T, compare>::difference_type
 			operator!=(const ft::btree_iterator<T, compare> ite1, const ft::btree_iterator<T1, compare> ite2) {return ite1._node != ite2._node;} 


/*
	template <typename T, class compare >
	class btree_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
			typedef typename T::value_type value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		T * _node;
		compare _comp;

		btree_const_iterator(const compare& comp = compare()) : _node(), _comp(comp) {}

		btree_const_iterator(const btree_const_iterator& btree_it) : _node(btree_it._node), _comp() {}

		btree_const_iterator(T *node_cpy, const compare& comp = compare()) : _node(node_cpy), _comp(comp) {}

//		btree_const_iterator(const btree_iterator& it) : _node(it._node), _comp() {}

		virtual ~btree_const_iterator() {}

		btree_const_iterator& operator=(const btree_const_iterator& cpy) {
			if (*this == cpy)
				return (*this);
			_node = cpy._node;
			_comp = cpy._comp;
			return (*this);
		}

		T * getter() {
			return (_node);
		}

		bool operator==(const btree_const_iterator& it) {
			return (_node == it._node);
		}

		
		bool operator!=(const btree_const_iterator& it) {
			return (_node != it._node);
		}
		
		btree_const_iterator& operator++(void) {
			T * start = _node;

			if (_node->right)
			{
				start = _node->right;
				while (start->left)
					start = start->left;
				_node = start;
				return (*this);
			}
			else
			{
				if (_node->back)
				{
					start = _node->back;
					while (start->back && (_comp(start->value.first, _node->value.first)))
					{
						start = start->back;
					}
					if (!start->back && (_comp(start->value.first, _node->value.first)))
						return (*this);
					else {
						_node = start;
						return (*this);
					}
				}
				else
					return (*this);
			}
			return (*this);
		}

		btree_const_iterator	operator++(int){
			btree_const_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		btree_const_iterator& operator--(void) {
			T * start = _node;

			if (_node->left)
			{
				start = _node->left;
				while (start->right)
					start = start->right;
				_node = start;
				return (*this);
			}
			else
			{
				while (start->back && (!_comp(start->value.first, _node->value.first)))
				{
					start = start->back;
				}
				if (!start->back && (!_comp(start->value.first, _node->value.first)))
					return (*this);
				else {
					_node = start;
					return (*this);
				}
			}
			return (*this);
		}

		btree_const_iterator operator--(int)
		{
			btree_const_iterator tmp(*this);
			operator--();
			return tmp;
		}

		pointer operator->() const {
			return (&this->_node->value);
		}

		reference operator*(){
			return _node->value;	
		}

		void	operator<<(reference &test){
		if (test == NULL)
		{
			(std::cout << "nill");
			return ;
		}
		(std::cout << test._node);
			return ;
		}
	};

	*/

}

#endif