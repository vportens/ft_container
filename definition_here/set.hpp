#ifndef SET_HPP 
# define SET_HPP 

#include "mapIterator_noob.hpp"
#include "reverse_iterator_map.hpp"
#include "utils_map.hpp"
#include "rb_tree_nood.hpp"


namespace ft {

template < class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T> >
class set {
	public:

	typedef const T			key_type;
	typedef const T			value_type;
	typedef Compare		key_compare;

 	class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class set<T, Compare, Alloc>;

		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}

		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x, y);
			}
		};

	typedef Alloc							allocator_type;
	typedef	typename allocator_type::reference		reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer	const_pointer;

	typedef	ft::Node<value_type>						node_type;	
	typedef	node_type*									node_ptr;	
	typedef	std::allocator<node_type>							alloc_node;

	typedef	ft::mapIterator<value_type, node_type>				iterator;	
	typedef	ft::mapIterator<const value_type, node_type>		const_iterator;
	typedef	ft::reverse_iterator<iterator>				reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	typedef	ptrdiff_t		difference_type;
	typedef	difference_type								size_type;


/* ----------- Menber fonctions ------------------ */

	private :
	node_ptr	_data;
	node_ptr	TNULL;
	key_compare	_key_cmp;
	allocator_type	_alloc;
	alloc_node	_alloc_node;
	size_type	_size;

	public:

	void	printTree() 
	{
		if (_data != TNULL)
			_data->printTree();
	}


	explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _data(), TNULL(), _key_cmp(comp), _alloc(alloc), _size(0) {

		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		_alloc_node.construct(node_to_insert, value_type());

		TNULL = node_to_insert;
		_data = TNULL;
		return ;
	}

	template <class InputIterator>
	set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :  _data(), TNULL(), _key_cmp(comp), _alloc(alloc), _size(0){

//		std::cout << "here" << std::endl;
		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		_alloc_node.construct(node_to_insert, value_type());
		TNULL = node_to_insert;

		while (first != last)
		{
//			std::cout << "bite" << std::endl;
			insert(*first);
			first++;
		}
		TNULL->root = _data->getRoot();
	}

	set (const set& src) {
		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		_alloc_node.construct(node_to_insert, value_type());
		this->TNULL = node_to_insert;
		_data = NULL;
		*this = src;
	}

	virtual ~set(void) {
		clear();
		delete TNULL;
	}	
	
	set &operator=(set const &rhs) {
		if (this == &rhs)
			return (*this);
		clear();
		insert(rhs.begin(), rhs.end());
		return (*this);
	}

/* ---------------------------------------Iterators------------------------------------ */

	iterator				begin(void) {
		if (!_data || _data == TNULL)
			return (iterator(TNULL));
		return iterator(farLeft(_data->getRoot()));
	}

	const_iterator			begin(void) const {
		if (!_data || _data == TNULL)
			return (iterator(TNULL));
		return const_iterator(farLeft(_data->getRoot()));
		}


	iterator				end(void) {
		if (!_data || _data == TNULL)
			return (iterator(TNULL));
		return (iterator(TNULL));

		return iterator(farRight(_data->getRoot())->right);
	}

	const_iterator			end(void) const {
		
		if (!_data || _data == TNULL)
			return (iterator(TNULL));
		return (iterator(TNULL));
		return const_iterator(farRight(_data->getRoot())->right);
	
	}

	reverse_iterator		rbegin(void) {return reverse_iterator(end());}
	const_reverse_iterator	rbegin(void) const {return reverse_iterator(end());}

	reverse_iterator		rend(void) {return reverse_iterator(begin());}
	const_reverse_iterator	rend(void) const {return reverse_iterator(begin());}

/* ------------------------------Capacity-------------------------------- */

	size_type	size(void) const {
		return (_size);
	}
	size_type	max_size(void) const {return (alloc_node().max_size());}
	bool		empty(void) const {return (_size == 0? true : false);}

// ******************************** Modifiers ******************************* //

	ft::pair<iterator, bool>	insert(const value_type &val) {
		ft::pair<iterator, bool> res;
		iterator	first = begin();
		iterator	last = end();
		node_ptr 	here = _data;

//		std::cout << "data :" << _data->value << std::endl;
		while (_data != TNULL && first != last)
		{
//			std::cout << "test" << std::endl;
			if (!_data)
				break;
			if (!_key_cmp(*first, val) && !_key_cmp(val, *first))
			{
//				std::cout << "end test" << std::endl;
				res.second = false;
				res.first = first;
				return (res);
			}
			first++;
		}
		res.second = true;
		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		_alloc_node.construct(node_to_insert, val);

		node_to_insert->TNULL = TNULL;
		node_to_insert->left = TNULL;
		node_to_insert->right = TNULL;
		node_to_insert->parent = nullptr;
		_size++;
		if (_data == NULL || _data == TNULL)
			_data = node_to_insert;
		else
		{
//			std::cout  << "go here" << std::endl;
			ft::Node<value_type> *tmp = here->getRoot();
			node_to_insert->parent = nullptr;
			node_to_insert->left = TNULL;
			node_to_insert->right = TNULL;
			node_to_insert->color = 1;
		
			ft::Node<value_type> *y = nullptr; 
			ft::Node<value_type> *x = tmp; 

		//	std::cout << "x: " << x->value << std::endl;
			while (x != TNULL) {
				y = x;
				if (_key_cmp(x->value, node_to_insert->value))
	 		       x = x->right;
				else 
	 				x = x->left;
	 		}
		//	std::cout  << "go here y: " << y->value << std::endl;
			node_to_insert->parent = y;
			if (y == nullptr)
				tmp = node_to_insert;
			else if (_key_cmp(y->value ,node_to_insert->value))
				y->right = node_to_insert;
			else
				y->left = node_to_insert;
			if (node_to_insert->parent == nullptr) {
				node_to_insert->color = 0;    
				res.first = find(val);
				return (res);
			}
			if (node_to_insert->parent->parent == nullptr) {
				res.first = find(val);
				return (res);
			}
//			std::cout << "tets" << std::endl;
			here->insertFix(node_to_insert);	
//			std::cout << "end tets" << std::endl;
		}
		res.first = find(val);
		TNULL->parent = _data->getRoot();
		TNULL->root = _data->getRoot();
		return (res);
	}

	iterator					insert(iterator position, const value_type &val) {
		static_cast<void>(position);
		return (insert(val).first);
	}

	template <class Ite> void	insert(Ite first, Ite last) {
		while (first != last)
		{
			insert(*first);
			first++;
		}
	}


	void		erase(iterator position) {
		erase(position._node->value);
	}

	size_type	erase(const key_type &k){
		iterator element = this->find(k);
	
		
		if (element._node == _data->getRoot() && element._node->left == TNULL && element._node->right == TNULL)
		{
			delete element._node;
			//make ite right
			_size--;
			_data = NULL;
			return 1;
		}
		if (element == this->end())
			return (0);

		node_ptr tmp;

		if (_data->value == k)
		{
			if (_data->parent && _data->parent != TNULL)
				tmp = _data->parent;
			else if (_data->left && _data->left != TNULL)
				tmp = _data->left;
			else if (_data->right&& _data->right!= TNULL)
				tmp = _data->right;
			else 
				tmp = NULL;
		}
//		std::cout << "value to delete: " << element._node->value << std::endl;
		element._node->deleteNode(element._node);
		if (_data->value == k)
		{
			if (tmp == NULL)
				_data = NULL;
			else 
				_data = tmp->getRoot();
		} 
		_size--;
		if ((TNULL->getRoot())->value != k)
			_data = TNULL->getRoot();
//		std::cout << "data after erase:" << _data->value << std::endl;
		TNULL->root = _data->getRoot();
		return (1);
	}

	void		erase(iterator first, iterator last) {
		while (first != last)
		{
//			std::cout << "value to erase:" << first._node->value << std::endl;
			erase(first++);
		}
	}

// to do swap
void swap(set &x) {
	key_compare _compTmp;
	alloc_node _node_allocTmp;
	node_ptr _rootTmp;
	node_ptr TNULLTmp;
	allocator_type _allocTmp;
	size_type _sizeTmp;

	_compTmp = _key_cmp;
	_node_allocTmp = _alloc_node;
	_rootTmp = _data;
	TNULLTmp = TNULL;
	_allocTmp = _alloc;
	_sizeTmp = _size;
	
	_key_cmp = x._key_cmp;
	_alloc_node = x._alloc_node;
	_data = x._data;
	TNULL = x.TNULL;
	_alloc = x._alloc;
	_size = x._size;

	x._key_cmp = _compTmp;
	x._alloc_node = _node_allocTmp;
	x._data = _rootTmp;
	x.TNULL = TNULLTmp;
	x._alloc = _allocTmp;
	x._size = _sizeTmp;
}


	void		clear(void) {
		if (_data == NULL || _data == TNULL)
			return ;
		erase(begin(), end());
		_data = NULL;
	}

/* ----------------------------Observers-------------------------------- */

	key_compare		key_comp(void) const {return key_compare();}
	value_compare	value_comp(void) const {return value_compare(key_compare());}

/* -----------------------Operations----------------------------- */

	iterator		find(const key_type &key) {
		iterator first = begin();
		iterator last = end();

		while (first != last)
		{
			if (!(_key_cmp(*first, key)) && !(_key_cmp(key, *first)))
				break;
			first++;
		}
		return (first);
	}

	const_iterator	find(const key_type &key) const {
		const_iterator first = begin();
		const_iterator last = end();

		while (first != last)
		{
			if (!(_key_cmp(*first, key)) && !(_key_cmp(key, *first)))
				break;
			first++;
		}
		return (first);
	}

	size_type		count(const key_type &key) const {
		const_iterator last = end();
		if (find(key) == end())
			return (false);
		return (true);
	}

	iterator		lower_bound(const key_type &key) {
		iterator first = begin();
		iterator last = end();

		while (first != last)
		{
			if (!_key_cmp(*first, key))
				break;
			first++;
		}
		return first;
	}

	const_iterator	lower_bound(const key_type &key) const {
		const_iterator first = begin();
		const_iterator last = end();

		while (first != last)
		{
			if (!_key_cmp(*first, key))
				break;
			first++;
		}
		return first;
	}


	iterator		upper_bound(const key_type &key) {
		iterator first = begin();
		iterator last = end();

		while (first != last)
		{
			if (_key_cmp(key, *first))
				break;
			first++;
		}
		return first;
	}

	const_iterator	upper_bound(const key_type &key) const {
		const_iterator first = begin();
		const_iterator last = end();

		while (first != last)
		{
			if (_key_cmp(key, *first))
				break;
			first++;
		}
		return first;
	}


	pair<const_iterator,const_iterator>	equal_range(const key_type &key) const {
		pair<const_iterator, const_iterator> res;

		res.first = lower_bound(key);
		res.second = upper_bound(key);
		return (res);
	}

	pair<iterator,iterator>				equal_range(const key_type &key) {
		pair<iterator, iterator> res;

		res.first = lower_bound(key);
		res.second = upper_bound(key);
		return (res);
	}


};


template <class T, class Compare, class Alloc>
bool	operator==(const set<T, Compare, Alloc> &lhs,
					const set<T, Compare, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Compare, class Alloc>
bool	operator!=(const set<T, Compare, Alloc> &lhs,
					const set<T, Compare, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool	operator< (const set<T, Compare, Alloc> &lhs,
					const set<T, Compare, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Compare, class Alloc>
bool	operator<=(const set<T, Compare, Alloc> &lhs,
					const set<T, Compare, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class T, class Compare, class Alloc>
bool	operator> (const set<T, Compare, Alloc> &lhs,
					const set<T, Compare, Alloc> &rhs) {
	return (rhs < lhs);
}

template <class T, class Compare, class Alloc>
bool	operator>=(const set<T, Compare, Alloc> &lhs,
					const set<T, Compare, Alloc> &rhs) {
	return !(lhs < rhs);
}


}

#endif
