#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

namespace ft
{
	template <typename T, class compare >
	class btree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :
			typedef T value_type;
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

		void operator*(){
			std::cout << _node->value.first;
			return ;	
			}

		void	operator<<(btree_iterator &test){
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