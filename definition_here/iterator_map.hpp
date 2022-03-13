#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

namespace ft
{
	template <typename T, class compare >
	class btree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
			typedef typename T::value_type value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

		T * _node;
		compare _comp;

		btree_iterator(const compare& comp = compare()) : _node(), _comp(comp) {}

		btree_iterator(const btree_iterator& btree_it) : _node(btree_it._node), _comp() {}

		btree_iterator(T *node_cpy, const compare& comp = compare()) : _node(node_cpy), _comp(comp) {}

		virtual ~btree_iterator() {}

		btree_iterator& operator=(const btree_iterator& cpy) {
			if (*this == cpy)
				return (*this);
			_node = cpy._node;
			_comp = cpy._comp;
			return (*this);
		}

		bool operator==(const btree_iterator& it) {
			return (_node == it._node);
		}

		
		bool operator!=(const btree_iterator& it) {
			return (_node != it._node);
		}
		
		btree_iterator& operator++(void) {
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

		btree_iterator	operator++(int){
			btree_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		btree_iterator& operator--(void) {
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

		btree_iterator operator--(int)
		{
			btree_iterator tmp(*this);
			operator--();
			return tmp;
		}

		reference operator*(){
			return _node->value;
		}


		pointer operator->() const {
			return (&this->_node->value);
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

		btree_const_iterator(const btree_iterator<T,  compare>& it) : _node(it._node), _comp() {}

		virtual ~btree_const_iterator() {}

		btree_const_iterator& operator=(const btree_const_iterator& cpy) {
			if (*this == cpy)
				return (*this);
			_node = cpy._node;
			_comp = cpy._comp;
			return (*this);
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

}

#endif