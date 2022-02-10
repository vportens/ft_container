#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "randomIterator.hpp"
# include "reverse_iterator.hpp"
	#include <iostream>
# include "utils.hpp"

namespace ft
{
template <class T, class Alloc = std::allocator<T> >
class vector {
				


		public :
					typedef	T 				value_type;
					typedef	Alloc 							allocator_type;
					typedef	typename allocator_type::reference 				reference;
					typedef	typename allocator_type::const_reference 			const_reference;
					typedef	typename allocator_type::pointer				pointer;
					typedef	typename allocator_type::const_pointer			const_pointer;
					typedef	ft::VectorIterator<value_type> 				iterator; //to define;
					typedef	ft::VectorIterator<value_type>				const_iterator;
					typedef	ft::reverse_iterator<iterator> 		reverse_iterator;
					typedef	ft::reverse_iterator<const_iterator> 		const_reverse_iterator;
					typedef	std::ptrdiff_t			difference_type; 
					typedef	unsigned long					size_type;
		private :
				allocator_type	_alloc;
				size_type	_capacity;
				pointer		_first;
				size_type	_size;

		public :

/*----------------------------------------constructor-----------------------------------------------------------*/

/*	Default constructor 			
**	Construct an empty container, with no elements.
**		
*/

					explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(0), _first(NULL), _size(0) {}

/*	Fill constructor 			
**	Construct a container with n elements. Each element is a copy of val.
**	Allocate n elementes with allocator::allocate(size_type n) that return a pointer to the first elem;	
**	Construct put val in pointer cur;	
*/

					explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc =allocator_type()) : _alloc(alloc), _capacity(n), _first(NULL), _size(n) 
					{
					_first = _alloc.allocate( n );	
					
					pointer	cur = _first;
					for (size_type i = 0; i < n; i++)
					{
						_alloc.construct(cur, val);	
						cur++;
					}
					}

/*	Range constructor 			
**	Construct a container with as many elements as the range [first, last), with each element constructed from its corresponding element in that range, in the same order.
**
**
**
*/


					template <class InputIterator>
					vector ( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()
					,		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) : _alloc(alloc) {
				difference_type n = ft::distance(first, last);
				_first= _alloc.allocate( n );
				_size = n;
				_capacity = n;
	
				pointer cur = _first;
				while (n--)
				{
					_alloc.construct(_first, *first);
					first++;
					_first++;
					
				}
				_first = cur;
			}				//		difference_type	n = ft::distance(first, last);							
						
				


/*	Copy constructor
**	Constructs a constainer with a copy of each of the elements in cpy, in the same order.
**
*/

					vector (const vector& cpy) : _alloc(cpy._alloc), _capacity(cpy._capacity), _size(cpy._size) {
						_first = _alloc.allocate(_capacity);
						pointer cur = _first;
						for (size_type i = 0; i < _size; i++)
						{
							_alloc.construct(cur, cpy._first[i]);
							cur++;
						}
					//	return (*this);
					}


				vector& operator=(const vector& cpy) {
					clear();
					insert(end(), cpy.begin(), cpy.end());
					return (*this);

				}


			~vector() {
				clear();
				_alloc.deallocate(_first, _capacity);
			}

/*-----------------------------------------------iterator--------------------------------------------------*/

/*	Begin
**	Returns an iterator pointing to the first elements
// */
 		iterator begin(){
 			return (iterator(_first));
 		}

		const_iterator begin() const {
			return (const_iterator(_first));
		}


/*	End
**	Returns an iterator pointing to the past end elements
*/
		iterator end() {
			return (_first + _size);
		}

		const_iterator end() const {
			return (_first + _size);

		}

		reverse_iterator rbegin() {
			return (reverse_iterator(end()));
		}

		const_iterator rbegin()const  {
			return (reverse_iterator(_first + _size));
		}

		reverse_iterator rend() {
			return (reverse_iterator(_first));
		}

		const_iterator rend()const  {
			return (reverse_iterator(_first));
		}
		

/*---------------------------------------------capacity--------------------------------------------------------------*/

/*	Size
**	Actual nbr of obj in vector != storage capacity
*/
				size_type size(void) const {return (_size);}


/*	Max_size	
**	Return nbr of obj vector can old due to systeme or lyb limitations .	
*/
				size_type max_size(void) const {return (allocator_type().max_size());}


/*	Resize
**	Resize the vector, if n < v.size(), cut it to n;
**	else	create size - n elements to vector of value val.
*/
				void	resize(size_type n, value_type val = value_type()) {
					if (n > max_size())
						throw (std::invalid_argument("resize overflow max size"));
					else if (_size > n)
					{
						for (size_type i = n; i < _size; i++)
						{
							allocator_type().destroy(_first + i);
						}
						_size = n;
					}
					else
					{
						insert(_first + _size, n - _size, val);
					}

				}
				
/*	Capacity
**	Capacity show the storage space currently allocated for the vector
*/

				size_type capacity(void) const {return (_capacity);}


/*	Empty
**	Return whether the vector is empty
*/

				bool	empty(void) const {
					if (!_size)	
						return (1);
					return (0);
				}
/*	Reserve
**	Realloc element to vector if capacity is not at leat egal to n
*/

				void	reserve(size_type n) {
					if (n > max_size())
						throw (std::invalid_argument("vector::reserve"));
					if (n <= _capacity)
						return ;
					pointer	start = _first;
					pointer	cur_prec = start;
					pointer	cur;
					size_type nbr = _size;
					_first = _alloc.allocate( n );
					cur = _first;
					for (size_type i = 0; i < nbr; i++)
					{
						_alloc.construct(cur, *cur_prec);
						cur++;
						cur_prec++;
					}
					_capacity = n;
					_alloc.deallocate(start, nbr);
				}

/*------------------------------------------Modifiers----------------------------------------------*/

/*	Assign, range
**	change the element from first to end to val
*/
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) {
					int i = 0;
					size_t n = ft::distance(first, last);
					if (n <= _size)
					{
						clear();
						for (size_t i = 0; i < n; i++)
						{
							_alloc.construct(_first + i, *first);
							first++;
						}
						_size = n;
						return ;
					
					}
					clear();
					_first = _alloc.allocate(n);
					_size = n;
					_capacity = n;
					while (first != last)
					{
						_first[i] = *first;	
						first++;
						i++;	
					}
					
				}

/*	Assign, fill
**	change the n first value to val	
*/
			void	assign(size_type n, const value_type& val) {
				clear();
				if (n <= _size)
				{
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_first + i, val);
				}
				else
				{
					_alloc.deallocate(_first, _capacity);
					_first = _alloc.allocate(n);
					_capacity = n;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_first+i,  val);
					
				}
				_size = n;
				
			}

/*		Push_back
**		Add new element at the end of the vector.
*/
			void	push_back(const value_type& val) {
				if (_size == 0)
					reserve(1);
				else if (_size == _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_first + _size, val);
				_size++;
			
			}

/*	Pop_back
**	Remove the last element reducing the size by one.
*/
			void	pop_back() {
				if (_size == 0)
					return ;
				_alloc.destroy(_first + _size -1);
				_size--;
			}

/*	Insert
**	Insert an element at the position give by ite pos
*/
			iterator insert (iterator position, const value_type&val)
			{
				size_t n = &(*position) - _first;
				//std::cout << "position du ite: " << n<< std::endl;
				//std::cout << "          " << n << std::endl;
			
				if (_capacity >= _size + 1)
				{
					int i = 0;
					while (_size -i > n)
					{
						_alloc.construct(_first + _size - i, *(_first + _size -i-1));
						i++;
					}
					_alloc.construct(_first + _size - i , val);
					_size++;


				}
				else
				{
					int i = 0;
					if (_capacity != 0)
						reserve(_capacity *2);
					else
						reserve(1);
					while (_size -i > n)
					{
						_alloc.construct(_first + _size - i, *(_first + _size -i-1));
						i++;
					}
					_alloc.construct(_first + _size - i , val);
					_size++;

				}
				return (_first + n);
			}

			
			void	insert (iterator position, size_type n, const value_type& val)
			{
				size_t last = &(*position) - _first;
				if (position == end())
					last -=1;
				if (_capacity >= _size + n)
				{
					int i = 0;
					while ( _size -i > last)	
					{
						_alloc.construct(_first + _size - i + n - 1, *(_first + _size -i - 1));
						i++;
					}	
					size_type j = 0;
					while (j < n)
					{
						_alloc.construct(_first + _size - i + n - 1, val);
						i++;
						j++;

					}
					_size += n;	
				}
				else
				{
					if (_capacity != 0)
						reserve(_capacity * 2);
					if (_capacity < _size + n)
						reserve(_size + n);
					int i = 0;
					while (_size -i > last)	
					{
						_alloc.construct(_first + _size - i + n-1, *(_first + _size -i - 1));
						i++;
					}	
					size_type j = 0;
					while (j < n)
					{
						_alloc.construct(_first + _size - i + n-1, val);
						i++;
						j++;

					}
					_size += n;	
			
				
				}	
			}


			template<class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) {
				size_t lastone = &(*position) - _first;
				size_type n = ft::distance(first, last);
				if (_capacity >= _size + n)
				{
					int i = 0;
					while ( _size -i > lastone)	
					{
						_alloc.construct(_first + _size - i + n - 1, *(_first + _size -i - 1));
						i++;
					}	
					size_type j = 0;
					while (j < n)
					{

						last -= 1;
						_alloc.construct(_first + _size - i + n - 1, *last);
						i++;
						j++;

					}
					_size += n;	
				}
				else
				{
					reserve(_capacity * 2);
					if (_capacity < _size + n)
						reserve(_size + n);
					int i = 0;
					while (_size -i > lastone)	
					{
						_alloc.construct(_first + _size - i + n-1, *(_first + _size -i - 1));
						i++;
					}	
					size_type j = 0;
					while (j < n)
					{
						last -= 1;
						_alloc.construct(_first + _size - i + n-1, *last);
						i++;
						j++;

					}
					_size += n;	
			
				
				}	


			}



			iterator erase (iterator position) {
				iterator cur = position;
				size_t n = ft::distance(begin(), position);
				if (position == end()-1)
				{
					_size--;
					_alloc.destroy(&(*position));
				}
				else
				{
					while (n < _size-1)
					{
						*(_first + n) = *(_first + n + 1);
						n++;
					}
					_alloc.destroy(&(*(_first + n)));
					_size--;
				}
				return (cur);
			}


			iterator erase(iterator first, iterator last) {
				size_t n  = ft::distance(begin(), last) -1;
				size_t start_c = ft::distance(begin(), first);
				size_t diff = n - start_c + 1;
					
				while (n < _size -1)
				{
					*(_first + start_c) = *(_first + n + 1);
					n++;
					start_c++;
				}
				size_t i = 0;
				while (i < diff)
				{
					_alloc.destroy(&(*(end() - i)));
					i++;
				}
				_size -= diff;
				return (first);
	
			}

/*	Swap
**	Swap two vector (contenue)
*/
			void	swap(vector& x)
			{
			//	if (x == *this)
			//		return ;
				if (x._alloc != _alloc)
					return ;
				pointer	p_tmp = x._first;
				size_type c_tmp = x._capacity;
				size_type s_tmp = x._size;
				

				x._first = _first;
				x._capacity = _capacity;
				x._size = _size;

				_first = p_tmp;
				_capacity= c_tmp;
				_size = s_tmp;
				return ;
				
					
			}
/*	Clean
**	Destroy all elements
*/	
			void	clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_first + i);
			_size = 0;
			}

/*---------------------------------------Element Access-----------------------------------------*/

/*	Operator[]
**	Access to vector val in position n.
*/
	reference operator[] (size_type n) {return (*(_first + n));} //check buserror
	const_reference operator[] (size_type n) const {return (*(_first + n));} //check buserror

/*	At
**	Return the reference to the element at position n in vector
*/
	reference	at(size_type n) {
		if (n >= size())
			throw (std::out_of_range("out of range in fonction at"));
		return (*(_first + n));

	}
	
	const_reference at(size_type n) const {
		if (n >= _size)
			throw (std::out_of_range("out of range in fonction at"));
		return (*(_first + n));
	
	}

/*	Front
**	Return a reference to the first elem in vector
*/
	reference front() {
		return (*(_first));
	}

	const_reference front() const {
		return (*(_first));
	}

/*	Back
**	Return a reference to the last elem in vector
*/
	reference	back() {
		return (*(_first + _size -1));
	}

	const_reference	back() const{
		return (*(_first + _size -1));
	}


};

	template<typename T, typename Allocator>
 	bool operator==(const ft::vector<T, Allocator>& vec1, const ft::vector<T, Allocator>& vec2) {
		if (vec1.size() != vec2.size())
			return (false);
		for (size_t i = 0; i < vec1.size(); i++)
		{
			if (vec1[i] != vec2[i])
				return (false);
		}
		return (true);
	}

	template<typename T, typename Allocator>
 	bool operator!=(const ft::vector<T, Allocator>& vec1, const ft::vector<T, Allocator>& vec2) {
		return (!(vec1 == vec2));
	}


	template<typename T, typename Allocator>
 	bool operator>(const ft::vector<T, Allocator>& vec1, const ft::vector<T, Allocator>& vec2) {
		size_t i = 0;
		while (i < vec1.size() && i < vec2.size())
		{
			if (vec1[i] > vec2[i])
				return (true);
			if (vec2[i] > vec1[i])
				return (false);
			i++;
		}	
		if (i == vec1.size() && i < vec2.size()) 
			return (false);
		if (i == vec1.size() && i == vec2.size())
			return (false);
		return (true);
	}

	template<typename T, typename Allocator>
 	bool operator<(const ft::vector<T, Allocator>& vec1, const ft::vector<T, Allocator>& vec2) {
		size_t i = 0;
		while (i < vec1.size() && i < vec2.size())
		{
			if (vec1[i] < vec2[i])
				return (true);
			if (vec2[i] < vec1[i])
				return (false);
			i++;
		}	
		if (i == vec2.size() && i < vec1.size())
			return (false);
		if (i == vec1.size() && i == vec2.size())
			return (false);
		return (true);
	}

	template<typename T, typename Allocator>
 	bool operator>=(const ft::vector<T, Allocator>& vec1, const ft::vector<T, Allocator>& vec2) {
			return (!(vec1 < vec2));
	}
	

	template<typename T, typename Allocator>
 	bool operator<=(const ft::vector<T, Allocator>& vec1, const ft::vector<T, Allocator>& vec2) {
			return (!(vec1 > vec2));
		}



}
#endif
