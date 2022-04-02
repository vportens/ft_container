#ifndef MAP_CLASS_HPP
# define MAP_CLASS_HPP

# include "base.hpp"
# include "map_decl.hpp"

namespace ft {





// ******************************** Modifiers ******************************* //

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::erase(iterator position) {
	this->erase(position++, position);
}

template<class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::size_type
map<Key, T, Compare, Alloc>::erase(const key_type &k) {
	iterator element = this->find(k);

	if (element == this->end())
		return (0);
	this->_btree_rm(element._node);
	return (1);
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last) {
	while (first != last)
		this->_btree_rm((first++)._node);
}


template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::swap(map &x) {
	map tmp;

	tmp._cpy_content(x);
	x._cpy_content(*this);
	this->_cpy_content(tmp);
}





// ################################ Private ####################################



template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_cpy_content(map &src) {
	this->clear();
	node_ptr tmp = this->_data;

	this->_data = src._data;
	this->_key_cmp = src._key_cmp;
	this->_alloc = src._alloc;
	this->_size = src._size;
	src._data = tmp;
	src._size = 0;
	tmp = NULL;
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_btree_clear(node_ptr node) {
	if (node == NULL)
		return ;
	this->_btree_clear(node->left);
	this->_btree_clear(node->right);
	delete node;
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_btree_add(node_ptr newNode) {
	node_ptr	*parent = &this->_data;
	node_ptr	*node = &this->_data;
	node_ptr	ghost = farRight(this->_data);
	bool		side_left = -1;

	++this->_size;
	while (*node && *node != ghost)
	{
		parent = node;
		side_left = this->_key_cmp(newNode->data.first, (*node)->data.first);
		node = (side_left ? &(*node)->left : &(*node)->right);
	}
	if (*node == NULL)
	{
		newNode->parent = (*parent);
		*node = newNode;
	}
	else // if (*node == ghost)
	{
		*node = newNode;
		newNode->parent = ghost->parent;
		ghost->parent = farRight(newNode); // Using farRight(newNode)
		farRight(newNode)->right = ghost; // in case newNode isnt alone
	}
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_btree_rm(node_ptr rmNode) {
	node_ptr	replaceNode = NULL;
	node_ptr	*rmPlace = &this->_data;

	--this->_size;
	if (rmNode->parent)
		rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
	if (rmNode->left == NULL && rmNode->right == NULL)
		;
	else if (rmNode->left == NULL) // left == NULL && right != NULL
		replaceNode = rmNode->right;
	else // left != NULL && right ?= NULL
	{
		replaceNode = farRight(rmNode->left);
		if (replaceNode != rmNode->left)
			if ((replaceNode->parent->right = replaceNode->left))
				replaceNode->left->parent = replaceNode->parent;
	}
	if (replaceNode)
	{
		replaceNode->parent = rmNode->parent;
		if (rmNode->left && rmNode->left != replaceNode)
		{
			replaceNode->left = rmNode->left;
			replaceNode->left->parent = replaceNode;
		}
		if (rmNode->right && rmNode->right != replaceNode)
		{
			replaceNode->right = rmNode->right;
			replaceNode->right->parent = replaceNode;
		}
	}
	*rmPlace = replaceNode;
	delete rmNode;
}



} // ******************************************************* ft namespace end //

#endif // ************************************************* MAP_CLASS_HPP end //