#ifndef MAP_CLASS_HPP
# define MAP_CLASS_HPP

# include "base_noob.hpp"
# include "map_decl_noob.hpp"

namespace ft {





// ******************************** Modifiers ******************************* //

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::erase(iterator position) {
//	std::cout << "coucou" << std::endl;
	this->erase(position._node->value.first);
//	std::cout << "aurevoir" << std::endl;

}

template<class Key, class T, class Compare, class Alloc>
typename map<Key, T, Compare, Alloc>::size_type
map<Key, T, Compare, Alloc>::erase(const key_type &k) {
//	std::cout << "plop" << std::endl;
	iterator element = this->find(k);
		
	if (element._node == element._node->getRoot() && element._node->left == TNULL && element._node->right == TNULL)
	{
//		std::cout << "last element" << std::endl;
		delete element._node;
		_size--;
		_data = TNULL;
		return 1;
	}

	if (element == this->end())
	{
		std::cout << "element not found" << std::endl;
		return (0);
	}
	
//	std::cout << "go to delete node: " << element._node->value << std::endl;
	node_ptr bite;
	if (_data->value.first == k)
	{
//		std::cout << "key to delete is root" << std::endl;
		if (_data->parent && _data->parent != TNULL)
		{
			bite = _data->parent;
//			std::cout << "new _data: " << bite->value << std::endl;
//			std::cout << "we chose that" << std::endl;
		}
		else if (_data->left && _data->left != TNULL)
			bite = _data->left;
		else if (_data->right&& _data->right!= TNULL)
			bite = _data->right;
		else 
			bite = NULL;
	}
//	std::cout << "we pass that" << std::endl;
	element._node->deleteNode(element._node);
//	std::cout << "we go out of delete" << std::endl;
	if (_data->value.first == k)
	{
	if (bite == NULL)
		_data = NULL;
	else 
		_data = bite->getRoot();
	}
	_size--;
//	std::cout << "delete done ouaiiii" << std::endl;
	TNULL->root = _data->getRoot();
	return (1);
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last) {
	while (first != last)
	{
	//	std::cout << "nique ta mere" << std::endl;
	//	std::cout << *first << std::endl;
	//	first._node->printTree();
		erase((first++));
	//	std::cout << "chouette, erase fini" << std::endl;

	}
//	std::cout << "fin de la session de baise" << std::endl;
			TNULL->root = _data->getRoot();
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
	if (_data != NULL)
	this->clear();
	node_ptr tmp = this->_data;

	this->_data = src._data;
	this->TNULL = src.TNULL;
	this->_key_cmp = src._key_cmp;
	this->_alloc = src._alloc;
	this->_size = src._size;
	src._data = tmp;
	src._size = 0;
	tmp = NULL;
}




} // ******************************************************* ft namespace end //

#endif // ************************************************* MAP_CLASS_HPP end //