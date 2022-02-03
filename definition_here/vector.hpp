#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>

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
				/*	typedef	VectorIterator<T> 				iterator; //to define;
					typedef	VectorIterator<const T>				const_iterator;
					typedef	VectorReverseIterator<iterator> 		reverse_iterator;
					typedef	VectorReverseIterator<const_iterator> 		const_reverse_iterator;
					typedef	VectorIteratorTraits<iterator> 			difference_type; */
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


/*					template <class InputIterator>
						vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
					
}*/

/*	Copy constructor
**	Constructs a constainer with a copy of each of the elements in cpy, in the same order.
**
*/

//	besoin des menbre priver donc besoin de geter				vector (const vector& cpy) : _alloc(cpy.


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
					}
					else
					{
						if (val)
							return ;
					}
						// insert to do here

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
						throw (std::invalid_argument("reserve overflow max size"));
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

/*	Swap
**	Swap two vector (contenue)
*/
			void	swap(vector& x)
			{
			//	if (x == *this)
			//		return ;
				pointer	p_tmp = x._first;
				size_type c_tmp = x._capacity;
				size_type s_tmp = x._size;
				Alloc a_tmp = x._alloc;

				x._first = _first;
				x._capacity = _capacity;
				x._size = _size;
				x._alloc = _alloc;

				_first = p_tmp;
				_capacity= c_tmp;
				_size = s_tmp;
				_alloc = a_tmp;
				return ;
				
					
			}
		

/*---------------------------------------Element Access-----------------------------------------*/

/*	Operator[]
**	Access to vector val in position n.
*/
	reference operator[] (size_type n) {return (*(_first + n));} //check buserror

};
}
#endif
