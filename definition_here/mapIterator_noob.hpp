#ifndef MAP_ITE_CLASS_HPP
# define MAP_ITE_CLASS_HPP

# include "utils_map.hpp"

namespace ft {

template <typename T, typename node_type>
class mapIterator {
	protected:

	public:
		typedef T						value_type;
		typedef ptrdiff_t				difference_type;
		typedef value_type&				reference;
		typedef value_type*				pointer;

		node_type						*_node;

		mapIterator(void);
		mapIterator(const mapIterator &src);
		mapIterator(node_type *src);

		virtual ~mapIterator(void);
		mapIterator	&operator=(mapIterator const &rhs);

		template <class U> bool	operator==(const mapIterator<U, node_type> &rhs) const;
		template <class U> bool	operator!=(const mapIterator<U, node_type> &rhs) const;

		mapIterator		&operator++(void);
		mapIterator		operator++(int);
		mapIterator		&operator--(void);
		mapIterator		operator--(int);

		reference	operator*(void) const;
		pointer		operator->(void) const;

		operator mapIterator<const T, node_type>(void) const {
			return mapIterator<const T, node_type>(this->_node);
		}

		template <class, class, class, class>
		friend class map;

		template <class, class>
		friend class mapIterator;

};

template <typename T, typename node_type>
mapIterator<T, node_type>::mapIterator(void) : _node(NULL)  { return ; }

template <typename T, typename node_type>
mapIterator<T, node_type>::mapIterator(node_type *src) {this->_node = src;}

template <typename T, typename node_type>
mapIterator<T, node_type>::mapIterator(const mapIterator &src) {*this = src;}

template <typename T, typename node_type>
mapIterator<T, node_type>::~mapIterator(void) {return ;}

template <typename T, typename node_type>
mapIterator<T, node_type> &mapIterator<T, node_type>::operator=(const mapIterator &rhs) {
	if (this == &rhs)
		return (*this);
	_node = rhs._node;
	return (*this);
}

template <typename T, typename node_type> template <class U>
bool	mapIterator<T, node_type>::operator==(const mapIterator<U, node_type> &rhs) const {
	return (_node == rhs._node);
}

template <typename T, typename node_type> template <class U>
bool	mapIterator<T, node_type>::operator!=(const mapIterator<U, node_type> &rhs) const {
	return (_node != rhs._node);
}

template <typename T, typename node_type>
mapIterator<T, node_type> &mapIterator<T, node_type>::operator++(void) {
	if (_node == farRight(_node->getRoot()))
	{
		_node = _node->TNULL;
		return (*this);
	}
	if (_node->right != _node->TNULL)
		_node = farLeft(_node->right);
	else
	{
		node_type	*child = _node;

		_node = _node->parent;
		while (_node && child == _node->right)
		{
			child = _node;
			_node = _node->parent;
		}
	}
	return (*this);
}

template <typename T, typename node_type>
mapIterator<T, node_type> mapIterator<T, node_type>::operator++(int) {
	mapIterator	tmp(*this);
	
	++(*this);
	return (tmp);
}

template <typename T, typename node_type>
mapIterator<T, node_type>& mapIterator<T, node_type>::operator--(void) {
	if (_node->left == NULL && _node->right == NULL)
	{
		_node = farRight(_node->root->getRoot());
		return (*this);
	}
	if (_node->left != _node->TNULL)
	 {
		_node = farRight(_node->left);
		return (*this);
	 }
	else
	{
		node_type	*child = _node;

		_node = _node->parent;
		while (_node && child == _node->left)
		{
			child = _node;
			_node = _node->parent;
		}
	}
	return (*this);
}

template <typename T, typename node_type>
mapIterator<T, node_type> mapIterator<T, node_type>::operator--(int) {
	mapIterator	tmp(*this);

	--(*this);
	return (tmp);
}

template <typename T, typename node_type>
typename mapIterator<T, node_type>::reference mapIterator<T, node_type>::operator*(void) const {
	return (this->_node->value);
}

template <typename T, typename node_type>
typename mapIterator<T, node_type>::pointer mapIterator<T, node_type>::operator->(void) const {
	return &this->operator*();
}

}
#endif