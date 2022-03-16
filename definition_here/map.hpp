#ifndef MAP_H
# define MAP_H

#include <map>
#include "utils.hpp"
#include "red_black.hpp"
#include "randomIterator.hpp"
#include "iterator_map.hpp"


namespace ft
{
template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
class map{
	public :
		typedef Key			 key_type;
		typedef T			 mapped_type;
		typedef ft::pair<Key, T>	 value_type;
		typedef Compare 		key_compare;
		typedef ft::node<value_type>	node_type;
		typedef Allocator 		allocator_type;
		typedef typename Allocator::reference 		reference;
		typedef typename Allocator::const_reference	 const_reference;
		typedef typename ft::btree_iterator<value_type, node_type>		iterator; // See 23.1
		typedef typename ft::btree_iterator<const value_type, node_type> const_iterator; // See 23.1
		typedef unsigned long		size_type; // See 23.1
		typedef ft::iterator_traits<iterator> 		difference_type;// See 23.1
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::allocator<ft::node<ft::pair<Key, T> > > alloc_node;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map<key_type, mapped_type, key_compare, Allocator>;

		protected :
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public :
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

	private :
			allocator_type	_alloc;
			Compare		_comp;
			alloc_node			_alloc_node;
			
	public :
			ft::node<value_type>*	_root;

		public :
		

/*-------------------------------construtors/destroy----------------------------*/
		explicit map(const Compare& comp = Compare(), const Allocator& alloc= Allocator()) : _alloc(alloc), _comp(comp), _root() {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc= Allocator()) : _alloc(alloc), _comp(comp), _root(NULL) {
			insert(first, last);
		}
		map(const map<Key, T, Compare, Allocator>& x) : _alloc(x._alloc), _comp(x._comp), _root(NULL) {
			insert(x.begin(), x.end());

		}
/*
		~map() {
			clear();
		}

		map<Key, T, Compare, Allocator>&x	operator=(const map<Key, T, Compare, Allocator>&x);

*/
/*----------------------------------------interator---------------------------------*/

		iterator	begin() {
			node<value_type> *start;

			if (!_root)
				return iterator();
			start = _root;
			while (start->left)
				start = start->left;
			return (iterator(start));

		}

		const_iterator	begin() const {
			node<value_type> *start;

			if (!_root)
				return const_iterator();
			start = _root;
			while (start->left)
				start = start->left;
			return (const_iterator(start));



		}

		iterator	end() {
			node<value_type> *start;

			//return (iterator());
			if (!_root)
				return iterator();
			start = _root;
			while (start->right)
				start = start->right;
			iterator last;
			last._back = start;
			return (last);
		}

		const_iterator	end() const {
			node<value_type> *start;

			if (!_root)
				return const_iterator();
			start = _root;
			while (start->right)
				start = start->right;
			const_iterator last;
			last._back = start;
			return (last);

		}

		reverse_iterator	rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator	rbegin() const{
			return const_reverse_iterator(end());
		}

		reverse_iterator	rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		}

/*-------------------------------------capacity---------------------------------------*/

		bool empty() const {
			if (!_root)
				return (true);
			return (false);
		}

		size_type size() const {
			if (empty())
				return (0);
			int i = 0;
			iterator start = begin();
			iterator last = (end());
			while (start!= last)
			{
				start++;
				i++;
			}
			return i;
		}

		size_type max_size() const {
			return (alloc_node().max_size());
		};


/*---------------------------------------element access------------------------------------*/
/*
		T& iterator[](const key_type& x);

*/
/*-------------------------------------------------modifier----------------------------------*/

		ft::pair<iterator, bool> insert(const value_type& x) {
			ft::node<value_type> * node_to_insert = _alloc_node.allocate(1);

			_alloc_node.construct(node_to_insert, x);

			if (!_root)
			{
				_root = node_to_insert;
				return (ft::make_pair(begin(), true));
			}
			else
			{
				iterator find = begin();
				iterator last = end();
				while (find != end())
				{
					if (find._node->value.first == x.first)
						return (ft::make_pair(find, false));
					find++;
				}
				_root->insert(node_to_insert);
				while (_root->back)
					_root = _root->back;
				iterator ret(node_to_insert);
				return (ft::make_pair(ret, true));
			}
			iterator ret(node_to_insert);
			return (ft::make_pair(ret, true));
		}


		void	printmap() {
			_root->print_tree();
		}

		iterator		insert(iterator position, const value_type& x) {
			(void)position;
			ft::pair<iterator, bool> ret;
			ret = insert(x);
			return ret.first;

		}

		template	<class InputIterator>
		void		insert(InputIterator first, InputIterator last){
			while (first != last)
			{
				insert(*first);
				first++;
			}
		//	_root->insert((first._node));
		}

/*		void	erase(iterator position);
		size_type	erase(const key_type& x);
		void	erase(iterator first, iterator last);
		void	swap(map<Key, T, Compare, Allocator>&); */
		void clear(){}

		

/*---------------------------------observers--------------------------------------*/
/*
		key_compare key_comp() const;
		value_compare value_comp() const;

*/

/*------------------------------map operation----------------------------------*/
/*
		iterator find(const key_type& x);
		const_iterator find(const key_type& x) const;
		size_type	count(const key_type& x) const;
		iterator	lower_bound(const key_type& x);
		const_iterator	lower_bound(const key_type& x) const;
		iterator	upper_bound(const key_type& x);
		const_iterator	upper_bound(const key_type& x) const;
		
		pair<iterator, iterator>	equal_range(const key_type& x);
		pair<const_iterator, const_iterator>	equal_range(const key_type& x) const;
			
*/

};

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, ft::map<T1, T2>& to_print){
	out << "test first, second " << to_print._root->value.first << " " << to_print._root->value.second << std::endl;
	return out;
}
/*
template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key, T, Compare, Allocator>& x, 
		const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool	operator<(const map<Key, T, Compare, Allocator>& x, 
		const map<Key, T, Compare, Allocator>& y);

template >class Key, class T, class Compare, class Allocator>
bool	operator<(const map<Key, T, Compare, Allocator>& x, 
		const map<Key, T, Compare, Allocator>& y);


template <class Key, class T, class Compare, class Allocator>
bool	operator!=(const map<Key, T, Compare, Allocator>& x, 
		const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool	operator<=(const map<Key, T, Compare, Allocator>& x, 
		const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool	operator>=(const map<Key, T, Compare, Allocator>& x, 
		const map<Key, T, Compare, Allocator>& y);


template<class Key, class T, class Compare, class Allocator>
void	swap(map<Key, T, Compare, Allocator>& x,map<Key, T, Compare, Allocator>& y);


*/



}

#endif
