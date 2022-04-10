#ifndef MAP_DECL_CLASS_HPP
# define MAP_DECL_CLASS_HPP

# include "base_noob.hpp"
# include "mapIte_noob.hpp"
# include "rev_ite_map_noob.hpp"
# include "rb_tree_nood.hpp"

namespace ft {

template < class Key,                                     // map::key_type
		 class T,                                         // map::mapped_type
		 class Compare = std::less<Key>,                  // map::key_compare
		 class Alloc = std::allocator<pair<const Key,T> > // map::allocator_type
		 >
class map {
	public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef pair<const key_type, mapped_type>			value_type;
	typedef Compare										key_compare;
	class												value_compare;

	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::Node<value_type>						node_type;
	typedef node_type*									node_ptr;

	typedef	std::allocator<node_type>							alloc_node;
	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;

	typedef ft::mapIte<value_type, node_type>			iterator;
	typedef ft::mapIte<const value_type, node_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

/* ----------------------------- Member functions ------------------------------------ */
	private:
	node_ptr				_data;
	node_ptr				TNULL;
	key_compare				_key_cmp;
	allocator_type			_alloc;
	alloc_node				_alloc_node;
	size_type				_size;

	public:


	explicit map(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _data(), TNULL(), _key_cmp(comp), _alloc(alloc), _size(0){
		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		this->TNULL = node_to_insert;
		_data = TNULL;
		return ;
		}

	template <class Ite >
	map(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
			Ite last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _data(), TNULL(), _key_cmp(comp), _alloc(alloc), _size(0) {
	//			std::cout << "ready to go" << std::endl;
					ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
			this->TNULL = node_to_insert;
			while (first != last)
			{
			this->insert(*first);
			first++;
			}
			TNULL->root = _data->getRoot();
//				std::cout << "ready to end" << std::endl;

			}

	map(const map &src) : _data(), TNULL(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0) {
		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		this->TNULL = node_to_insert;
		_data = NULL;
		*this = src;
	}

	virtual ~map(void) {
		clear();
	//	delete TNULL;
	}

	map	&operator=(map const &rhs) {
		if (this == &rhs)
			return (*this);
		
		clear();
		insert(rhs.begin(), rhs.end());
		return (*this);
	}

	/*make it private */
	void	printTree() 
	{
		if (_data != TNULL)
			_data->printTree();
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

/* -----------------------------Ele Access---------------------------------- */

	mapped_type	&operator[](const key_type &key) {
		iterator tmp;
		insert(ft::make_pair(key, mapped_type()));
		tmp = find(key);
		return ((*tmp).second);
	}

// ******************************** Modifiers ******************************* //

	ft::pair<iterator, bool>	insert(const value_type &val) {
//	std::cout << "je rentre dans insert" << std::endl;
		ft::pair<iterator, bool> res;
		iterator	first = begin();
		iterator	last = end();
		node_ptr 	here = _data;


//		std::cout << "j'ai init mes ite" << std::endl;
//		if (last._node == TNULL)
//			std::cout << "end marche bien" << std::endl;
//		std::cout << "je rentre dans la recherche de l'element avant d'insert" << std::endl;
//		std::cout << "what are we looking for: " << val << std::endl;
//		std::cout << "bjr" << std::endl;
		while (_data != TNULL && first != last)
		{
//			std::cout << "go find if element to insert exist" << std::endl;
			if (!_data)
				break;
			if (!_key_cmp(first->first, val.first) && !_key_cmp(val.first, first->first))
			{
				res.second = false;
				res.first = first;
				return (res);
			}
			first++;
		}
	//	std::cout << "elements pas trouve" << std::endl;
		res.second = true;
	//	std::cout << "creation d'une nouvelle node" << std::endl;
		ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);
		_alloc_node.construct(node_to_insert, val);
		node_to_insert->TNULL = TNULL;
		node_to_insert->left = TNULL;
		node_to_insert->right = TNULL;
		_size++;
//		std::cout << "fin de l'init de la nouvel node " << std::endl;
		if (_data == NULL || _data == TNULL)
		{
//			std::cout << "first insert " << std::endl;
			_data = node_to_insert;
		}
		else
		{
	//		std::cout << "je rentre dans l'insert de node" << std::endl;
	//		std::cout << here->value << std::endl;
			here->insert(node_to_insert);
		}
//		std::cout << "end :)" << std::endl;
		res.first = find(val.first);
		TNULL->parent = _data->getRoot();
		TNULL->root = _data->getRoot();
//		std::cout << "go find l'element pour le ret de la fin:)" << std::endl;
		return (res);
	}

	iterator					insert(iterator position, const value_type &val) {
		static_cast<void>(position);
		return (insert(val).first);
	}

	template <class Ite> void	insert(Ite first, Ite last) {
		while (first != last)
		{
//			std::cout << "yes" << std::endl;
//			std::cout << "what am i insert with ite: " << *first << std::endl;
			insert(*first);
//			std::cout << "next" << std::endl;
			first++;
		}
	}


	void		erase(iterator position);
	size_type	erase(const key_type &k);
	void		erase(iterator first, iterator last);

	void		swap(map &x);
	


	void		clear(void) {
//		std::cout << "ca marche pas" << std::endl;
		if (_data == NULL)
			return ;
		erase(begin(), end());
		_data = NULL;

//		std::cout << "ca marche " << std::endl;
		
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
			if (!(_key_cmp(first->first, key)) && !(_key_cmp(key, first->first)))
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
			if (!(_key_cmp(first->first, key)) && !(_key_cmp(key, first->first)))
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
			if (!_key_cmp(first->first, key))
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
			if (!_key_cmp(first->first, key))
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
			if (_key_cmp(key, first->first))
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
			if (_key_cmp(key, first->first))
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

// ******************************* Non-public ******************************* //

	private:

	void				_cpy_content(map &src);

	void				_btree_clear(node_ptr node);
	void				_btree_add(node_ptr node);
	void				_btree_rm(node_ptr node);

//	bool				_key_eq(const key_type &k1, const key_type &k2) const;

}; // ***************************************************** class ft::map end //

template <class Key, class T, class Compare, class Alloc>
class	map<Key, T, Compare, Alloc>::value_compare {
	public:
	Compare comp;
	value_compare(Compare c) : comp(c) { };

	typedef bool		result_type;
	typedef value_type	first_argument_type;
	typedef value_type	second_argument_type;
	bool	operator()(const value_type &x, const value_type &y) const {
		return comp(x.first, y.first);
	}
};


template <class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator< (const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator> (const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
	x.swap(y);
}


} // ******************************************************* ft namespace end //

#endif // ******************************************** MAP_DECL_CLASS_HPP end //