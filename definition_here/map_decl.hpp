#ifndef MAP_DECL_CLASS_HPP
# define MAP_DECL_CLASS_HPP

# include "base.hpp"
# include "mapIte.hpp"
# include "rev_ite_map.hpp"

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
	typedef ft::mapNode<value_type>						node_type;
	typedef node_type*									node_ptr;

	typedef	std::allocator<node_type>							alloc_node;
	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;

	typedef ft::mapIte<value_type, node_type>			iterator;
	typedef ft::mapIte<const value_type, node_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

/* ----------------------------- Member functions ------------------------------------ */

	explicit map(const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _data(), _key_cmp(comp), _alloc(alloc), _size(0){
		ft::mapNode<value_type> * node_to_insert = _alloc_node.allocate(1);
		this->_data = node_to_insert;
		return ;
		}

	template <class Ite>
	map(typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
			Ite last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
					ft::mapNode<value_type> * node_to_insert = _alloc_node.allocate(1);
			this->_data = node_to_insert;
			this->insert(first, last);
			}

	map(const map &src) : _data(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0) {
		ft::mapNode<value_type> * node_to_insert = _alloc_node.allocate(1);
		this->_data = node_to_insert;
		*this = src;
	}

	virtual ~map(void) {
		clear();
		delete _data;
	}

	map	&operator=(map const &rhs) {
		if (this == &rhs)
			return (*this);
		clear();
		insert(rhs.begin(), rhs.end());
		return (*this);
	}

/* ---------------------------------------Iterators------------------------------------ */

	iterator				begin(void) {return iterator(farLeft(_data));}
	const_iterator			begin(void) const {return const_iterator(farLeft(_data));}

	iterator				end(void) {return iterator(farRight(_data));}
	const_iterator			end(void) const {return const_iterator(farRight(_data));}

	reverse_iterator		rbegin(void) {return reverse_iterator(end());}
	const_reverse_iterator	rbegin(void) const {return reverse_iterator(end());}

	reverse_iterator		rend(void) {return reverse_iterator(begin());}
	const_reverse_iterator	rend(void) const {return reverse_iterator(begin());}

/* ------------------------------Capacity-------------------------------- */

	size_type	size(void) const {return (_size);}
	size_type	max_size(void) const {return (alloc_node().max_size());}
	bool		empty(void) const {return (_size == 0? true : false);}

/* -----------------------------Ele Access---------------------------------- */

	mapped_type	&operator[](const key_type &key) {
		return (insert(value_type(key, mapped_type())).first->second);
	}

// ******************************** Modifiers ******************************* //

	ft::pair<iterator, bool>	insert(const value_type &val) {
		ft::pair<iterator, bool> res;
		iterator	first = begin();
		iterator	last = end();

		while (first != last)
		{
			if (!_key_cmp(first->first, val.first) && !_key_cmp(val.first, first->first))
			{
				res.second = false;
				res.first = first;
				return (res);
			}
			first++;
		}
		res.second = true;
		ft::mapNode<value_type> * node_to_insert = _alloc_node.allocate(1);
		_alloc_node.construct(node_to_insert, val);
		_btree_add(node_to_insert);
		res.first = find(val.first);
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

	void		erase(iterator position);
	size_type	erase(const key_type &k);
	void		erase(iterator first, iterator last);

	void		swap(map &x);


	void		clear(void) {
		node_ptr void_node_ptr = end()._node;
		if (_size == 0)
			return ;
		void_node_ptr->parent->right = NULL;
		_btree_clear(_data);
		_data = void_node_ptr;
		_size = 0;
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
	node_ptr				_data;
	key_compare				_key_cmp;
	allocator_type			_alloc;
	alloc_node				_alloc_node;
	size_type				_size;

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