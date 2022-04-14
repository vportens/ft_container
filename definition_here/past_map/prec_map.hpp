#ifndef MAP_H
# define MAP_H

#include <map>
#include "utils.hpp"
//#include "red_black.hpp"
#include "rb_tree.hpp"
#include "randomIterator.hpp"
#include "iterator_map.hpp"
#include "map_ite.hpp"


namespace ft
{
template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
class map{
	public :
		typedef Key			 key_type;
		typedef T			 mapped_type;
		typedef ft::pair<Key, T>	 value_type;
		typedef Compare 		key_compare;
		typedef ft::Node<value_type>	node_type;
		typedef Allocator 		allocator_type;
		typedef typename Allocator::reference 		reference;
		typedef typename Allocator::const_reference	 const_reference;
		typedef typename ft::mapIte<value_type, node_type>		iterator; // See 23.1
		typedef typename ft::mapIte<const value_type, node_type> const_iterator; // See 23.1
		typedef unsigned long		size_type; // See 23.1
		typedef ft::iterator_traits<iterator> 		difference_type;// See 23.1
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::allocator<ft::Node<ft::pair<Key, T> > > alloc_node;

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
			ft::RedBlackTree<value_type>	rb;

		public :
		

/*-------------------------------construtors/destroy----------------------------*/
		explicit map(const Compare& comp = Compare(), const Allocator& alloc= Allocator()) : _alloc(alloc), _comp(comp), rb() {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc= Allocator()) : _alloc(alloc), _comp(comp), rb() {
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}
		map(const map<Key, T, Compare, Allocator>& x) : _alloc(x._alloc), _comp(x._comp), rb() {
			insert(x.begin(), x.end());

		}

		~map() {
			clear();
		}


		map<Key, T, Compare, Allocator>&	operator=(const map<Key, T, Compare, Allocator>&x)
		{
			clear();
			insert(x.begin(), x.end());
			return *this;
		}


/*----------------------------------------interator---------------------------------*/

		iterator	begin() {
			Node<value_type> *start;

			if (!rb.root)
				return iterator();
			start = rb.root;
		//	std::cout << "l'init ce passe bien" << std::endl;
			while (start->left && start->left != nullptr && start->left != rb.TNULL)
			{
				start = start->left;
			}
			return (iterator(start));

		}

		const_iterator	begin() const {
			Node<value_type> *start;

			if (!rb.root)
				return const_iterator();
			start = rb.root;
			while (start->left && start->left != nullptr && start->left != rb.TNULL)
				start = start->left;
			return (const_iterator(start));



		}

		iterator	end() {
			Node<value_type> *start;

			//return (iterator());
			if (!rb.root)
				return iterator();
			start = rb.root;
			while (start->right)
				start = start->right;
//			if (start == rb.TNULL)
//				std::cout << "last == TNULL" << std::endl;
			iterator last(start);
	//		last._back = start;
		
			return (last);
		}

		const_iterator	end() const {
			Node<value_type> *start;

			if (!rb.root)
				return const_iterator();
			start = rb.root;
			while (start->right)
				start = start->right;
			const_iterator last(start);
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
			if (!rb.root)
				return (true);
			return (false);
		}

		size_type size() const {
			if (empty())
				return (0);
			int i = 0;
			ft::Node<value_type> *start;
			ft::Node<value_type> *last;
			start = rb.root;
			last = rb.root;
			while (start->left && start->left != nullptr && start->left != rb.TNULL)
				start = start->left;
			while (last->right)
				last =last->right;
			iterator lilstart = iterator(start);
			
			iterator lilend = iterator(last);
		//	lilend.back = last;
			while (lilstart != lilend )
			{
				lilstart++;
				i++;
			}
		
			return i;
		}

		size_type max_size() const {
			return (alloc_node().max_size());
		}


/*---------------------------------------element access------------------------------------*/

		T& operator[](const key_type& x) {
			iterator tmp;

			tmp = find(x);
			if (tmp == end())
			{
				insert(ft::make_pair(x, mapped_type()));
			}
			tmp = find(x);
			return ((*tmp).second);
		}


/*-------------------------------------------------modifier----------------------------------*/

		ft::pair<iterator, bool> insert(const value_type& x) {
			ft::Node<value_type> * node_to_insert = _alloc_node.allocate(1);

			_alloc_node.construct(node_to_insert, x);

			if (!rb.root)
			{
				rb.root = node_to_insert;
				return (ft::make_pair(begin(), true));
			}
			else
			{
				iterator find = begin();
			//	iterator last = end();
				while (find != end())
				{
					if (find._node != rb.TNULL && find._node->value.first == x.first)
					{
						delete node_to_insert;
						return (ft::make_pair(find, false));
					}
//					std::cout << "fuck" << std::endl;
					find++;
				}
				rb.insert(node_to_insert);
				iterator ret(node_to_insert);
				return (ft::make_pair(ret, true));
			}
			iterator ret(node_to_insert);

			return (ft::make_pair(ret, true));
		}


		void	printmap() {
			if (rb.root == NULL)
				return ;
			rb.print_tree();
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
		}

		void	erase(iterator position) {
			rb.deleteNode(position._node);
		}

		void erase(ft::Node<value_type> *to_erase) {
			ft::Node<value_type> *tmp;

			if (to_erase == rb.root && to_erase->left == NULL && to_erase->right == NULL)
			{
				delete to_erase;
				rb.root == NULL;
				return ;
			}

			
			/*
			while (tmp != NULL) 
			{
				if (tmp->first == x)
					break ;
				if (tmp->first > x)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			if (tmp == NULL)
				return (0);
			*/
			rb.deleteNode(to_erase);
			
		}

		void	erase(iterator first, iterator last)
		{
			iterator tmp;
			while (first != last)
			{
//				std::cout << "nbr de passage" << std::endl;
				if (first._node->parent == NULL && first._node->left == NULL && first._node->right == NULL)
				{
//					std::cout << "last one" << std::endl;
					delete first._node;
					rb.root = NULL;
					return ;
				}
				else {
				tmp = first;
				first++;
//				std::cout << "go to erase" << std::endl;

				rb.deleteNode(tmp._node);
				}
			}
		}
	
	/*
		void	swap(map<Key, T, Compare, Allocator>&); */
		void clear(){
			//erase(begin(), end());
		}

		

/*---------------------------------observers--------------------------------------*/
/*
		key_compare key_comp() const;
		value_compare value_comp() const;

*/

/*------------------------------map operation----------------------------------*/

		iterator find(const key_type& x) {
			iterator tmp = begin();
			
			while (tmp != end())
			{
				if (tmp._node->value.first == x)
					return (tmp);
				tmp++;
			}
			return tmp;

		}
		const_iterator find(const key_type& x) const {
			const_iterator tmp = begin();
			
			while (tmp != end())
			{
				if (tmp._node->first == x)
					return (tmp);
				tmp++;
			}
			return tmp;


		}
/*		size_type	count(const key_type& x) const;
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
