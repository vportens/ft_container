#ifndef VECTOR_HPP
# define VECTOR_HPP
//#include <vector>

# include <memory>

namespace ft
{
template <class T, class Alloc = allocator<T> >
class Vector {

		public :
					typedef	T 				value_type;
					typedef	Alloc 							allocator_type;
					typedef	allocator_type::reference 				reference;
					typedef	allocator_type::const_reference 			const_reference;
					typedef	allocator_type::pointer				pointer;
					typedef	allocator_type::const_pointer			const_pointer;
					typedef	VectorIterator<T> 				iterator; //to define;
					typedef	VectorIterator<const T>				const_iterator;
					typedef	VectorReverseIterator<iterator> 		reverse_iterator;
					typedef	VectorReverseIterator<const_iterator> 		const_reverse_iterator;
					typedef	VectorIteratorTraits<iterator> 			difference_type;
					typedef	unsigned long					size_type;


};




}

#endif