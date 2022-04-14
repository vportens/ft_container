#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include "reverse_iterator.hpp"
//#include "rb_tree.hpp"

namespace ft
{
	template <typename pair, class Node>
	class btree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, pair>
	{
		public :
			typedef pair value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		Node * _node;
		Node * _back;
		ft::RedBlackTree<pair>	base;
	//	compare _comp;

	//	btree_iterator(T *lala, compare const &lsl) : _node(lala), _comp(lsl) {}

//		new version

		btree_iterator() : _node(NULL), _back(NULL), base() {}
		btree_iterator(Node * node, ft::RedBlackTree<pair> j) : _node(node), _back(node->parent), base(j) {}

//		operator btree_iterator<const pair, Node>() const {
//			return btree_iterator<const pair, Node>(_node, base);
//		}
//		btree_iterator(Node * node, Node * null_node) : _node(node), _back(node->parent), TNULL(null_node) {}

		
//		btree_iterator(const btree_iterator& btree_it) : _node(btree_it._node), _comp() {}
//		btree_iterator(const ft::btree_const_iterator<T,  compare>& it) : _node(it._node), _comp() {}
/*
		btree_iterator() : _node(NULL), _back(NULL) {}

	//	btree_iterator (const btree_iterator &cpy)  : _node(cpy._node){}

		btree_iterator(Node *x, Node* y) : _node(x), _back(y) {}
		
		btree_iterator<pair, Node> (const btree_iterator<pair, Node> &cpy)  : _node(cpy._node), _back(cpy._back) {}
		
	//	btree_iterator<pair, node> (const btree_iterator<pair, node> &cpy)  : _node(cpy._node){}

		btree_iterator (Node *cpy) : _node(cpy), _back(cpy->parent) {}

		virtual ~btree_iterator() {}

		btree_iterator &operator=(const btree_iterator &cpy) {
			_node = cpy._node;
			_back = cpy._back;
			return (*this);
		}

		operator btree_iterator<const pair, Node>() const {
			return btree_iterator<const pair, Node>(_node, _back);
		}

*/
//	value_type getter(){ return _node;}
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



			Node *start = _node;

			if (_node == NULL)
			{
	//			std::cout << "node vide dans ++" << std::endl;
				return (*this);
			} 
			if (_node->right && _node->right != base.TNULL)
			{
	//			std::cout << "il y a un element a droit dans ++" << std::endl;
				_back = _node;
				start = _node->right;
				while (start->left && start->left != nullptr && start->left != base.TNULL)
				{
	//				std::cout << "passe par la gauche" << std::endl;
					_back = start;
					start = start->left;
				}
				_node = start;
				return (*this);
			}
			else {
	//			std::cout << "il n'y a pas d'element a droit dans ++" << std::endl;
				Node *prec = _node;
				start = _node->parent;
				while (start && start->value < prec->value)
					start = start->parent;
				if (start == NULL)
				{
					_node = _node->right;
					return (*this);
				}
				else
				{
					_node = start;
					_back = _node->parent;
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
			Node * start = _node;

			if (_node == NULL && _back)
			{
				_node = _back;
				_back = _back->parent;
				return (*this);
			}
			if (_node->left)
			{
				start = _node->left;
				while (start->right && start->right != base.TNULL)
					start = start->right;
				_node = start;
				if (_node->parent)
					_back = _node->parent;
				return (*this);
			}
			else
			{
				Node *prec = _node;
				if (start->parent == NULL)
				{
					return (*this);
				}
				start = start->parent;
				while (start->parent && start->left == prec)
				{
					prec = start;
					start = start->parent;
				}
				_node = start;
				_back = start->parent;
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

template <typename pair, class Node>
class const_btree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, pair>
{
		public :
			typedef pair value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		Node * _node;
		Node * _back;
		ft::RedBlackTree<pair>	base;

		const_btree_iterator() : _node(NULL), _back(NULL), base() {}
		const_btree_iterator(Node * node, const ft::RedBlackTree<pair> j) : _node(node), _back(node->parent), base(j) {}

		const_btree_iterator &operator=(const const_btree_iterator &cpy) {
			_node = cpy._node;
			_back = cpy._back;
			base = cpy.base;
			return (*this);
		}

		const_btree_iterator& operator=(const ft::btree_iterator<pair, Node>& cpy)const {

			_node = cpy._node;
			_back= cpy._back;
			base = cpy.base;
			return (*this);

		}
		

//		operator btree_iterator<const pair, Node>() const {
//			return btree_iterator<const pair, Node>(_node, base);
//		}
//		btree_iterator(Node * node, Node * null_node) : _node(node), _back(node->parent), TNULL(null_node) {}

		
//		btree_iterator(const btree_iterator& btree_it) : _node(btree_it._node), _comp() {}
//		btree_iterator(const ft::btree_const_iterator<T,  compare>& it) : _node(it._node), _comp() {}
/*
		btree_iterator() : _node(NULL), _back(NULL) {}

	//	btree_iterator (const btree_iterator &cpy)  : _node(cpy._node){}

		btree_iterator(Node *x, Node* y) : _node(x), _back(y) {}
		
		btree_iterator<pair, Node> (const btree_iterator<pair, Node> &cpy)  : _node(cpy._node), _back(cpy._back) {}
		
	//	btree_iterator<pair, node> (const btree_iterator<pair, node> &cpy)  : _node(cpy._node){}

		btree_iterator (Node *cpy) : _node(cpy), _back(cpy->parent) {}

		virtual ~btree_iterator() {}

		btree_iterator &operator=(const btree_iterator &cpy) {
			_node = cpy._node;
			_back = cpy._back;
			return (*this);
		}

		operator btree_iterator<const pair, Node>() const {
			return btree_iterator<const pair, Node>(_node, _back);
		}

*/
//	value_type getter(){ return _node;}
/*		btree_iterator& operator=(const btree_const_iterator& cpy) {
			if (*this == cpy)
				return (*this);
			_node = cpy._node;
			_comp = cpy._comp;
			return (*this);
		}
	*/

		bool operator==(const const_btree_iterator& it) {
			return (_node == it._node);
		}

		
		bool operator!=(const const_btree_iterator& it) {
			return (_node != it._node);
		}
		

	
		const_btree_iterator& operator++(void) {



			Node *start = _node;

			if (_node == NULL)
			{
	//			std::cout << "node vide dans ++" << std::endl;
				return (*this);
			} 
			if (_node->right && _node->right != base.TNULL)
			{
	//			std::cout << "il y a un element a droit dans ++" << std::endl;
				_back = _node;
				start = _node->right;
				while (start->left && start->left != nullptr && start->left != base.TNULL)
				{
	//				std::cout << "passe par la gauche" << std::endl;
					_back = start;
					start = start->left;
				}
				_node = start;
				return (*this);
			}
			else {
	//			std::cout << "il n'y a pas d'element a droit dans ++" << std::endl;
				Node *prec = _node;
				start = _node->parent;
				while (start && start->value < prec->value)
					start = start->parent;
				if (start == NULL)
				{
					_node = _node->right;
					return (*this);
				}
				else
				{
					_node = start;
					_back = _node->parent;
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

		const_btree_iterator	operator++(int){
			const_btree_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		const_btree_iterator& operator--(void) {
			Node * start = _node;

			if (_node == NULL && _back)
			{
				_node = _back;
				_back = _back->parent;
				return (*this);
			}
			if (_node->left)
			{
				start = _node->left;
				while (start->right && start->right != base.TNULL)
					start = start->right;
				_node = start;
				if (_node->parent)
					_back = _node->parent;
				return (*this);
			}
			else
			{
				Node *prec = _node;
				if (start->parent == NULL)
				{
					return (*this);
				}
				start = start->parent;
				while (start->parent && start->left == prec)
				{
					prec = start;
					start = start->parent;
				}
				_node = start;
				_back = start->parent;
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

		const_btree_iterator operator--(int)
		{
			const_btree_iterator tmp(*this);
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



template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, ft::const_btree_iterator<T1, T2>& to_print){
	out << "node value :" << to_print._node;
	return out;
}


			template<typename T, typename compare>
			typename ft::const_btree_iterator<T, compare>::difference_type
 			operator==(const ft::const_btree_iterator<T, compare> ite1, const ft::const_btree_iterator<T, compare> ite2) {return (ite1._node == ite2._node);}

			template<typename T, typename compare, typename T1>
			typename ft::const_btree_iterator<T, compare>::difference_type
 			operator==(const ft::const_btree_iterator<T, compare> ite1, const ft::const_btree_iterator<T1, compare> ite2) {return ite1._node == ite2._node;} 


			template<typename T, typename compare>
			typename ft::const_btree_iterator<T, compare>::difference_type
 			operator!=(const ft::const_btree_iterator<T, compare> ite1, const ft::const_btree_iterator<T, compare> ite2) {return (ite1._node != ite2._node);}

			template<typename T,typename compare,  typename T1>
			typename ft::const_btree_iterator<T, compare>::difference_type
 			operator!=(const ft::const_btree_iterator<T, compare> ite1, const ft::const_btree_iterator<T1, compare> ite2) {return ite1._node != ite2._node;} 



}

#endif