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
		T * _prec_node;
		compare _comp;

		btree_iterator(const compare& comp = compare()) : _node(), _prec_node(), _comp(comp) {}

		btree_iterator(const btree_iterator& btree_it) : _node(btree_it._node), _prec_node(btree_it.node), _comp() {}

		btree_iterator(T *node_cpy, T * prec_node_cpy, const compare& comp = compare()) : _node(node_cpy), _prec_node(prec_node_cpy), _comp(comp) {}

		virtual ~btree_iterator() {}

	};	
}

#endif