#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};



template<class Iterator>
class iterator_traits {
	
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type		value_type;	
		typedef typename Iterator::difference_type	difference_type;	
		typedef typename Iterator::pointer		pointer;	
		typedef typename Iterator::reference		reference;	

}; //to do


template<class T>
class iterator_traits<T*> {

		typedef random_access_iterator_tag	iterator_category;	
		typedef T		value_type;	
		typedef std::ptrdiff_t		difference_type;	
		typedef T*		pointer;	
		typedef T&		reference;
}; //to do


template<class T>
class iterator_traits<const T*> {

		typedef random_access_iterator_tag	iterator_category;	
		typedef T		value_type;	
		typedef std::ptrdiff_t		difference_type;	
		typedef const T*		pointer;	
		typedef const T&		reference;
}; //to do







template <class Category, class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*, class Reference = T&>
struct iterator {

		typedef Category		iterator_category;	
		typedef T		value_type;	
		typedef Distance		difference_type;	
		typedef Pointer		pointer;	
		typedef Reference		reference;	

};

template<class T>
class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T> {

		private :

  			T* _p;

		protected :
			
		public :



			VectorIterator(): _p(NULL) {}

			VectorIterator(T* value) : _p(value) {}

 			VectorIterator(const VectorIterator& cpy) {
				*this = cpy;
			}
			
			VectorIterator&	operator=(const VectorIterator& cpy) {
				_p = cpy._p;
				return *this;
			};


			~VectorIterator() {};

/*----------all category--------------*/
			VectorIterator& operator++() {
				++_p;
				return *this;
			}

			VectorIterator 	operator++(T) {
				VectorIterator tmp(*this);
				operator++(); 
				return tmp;
			}


/*--------------------input----------------*/
 			bool 		operator==(const VectorIterator& cpy) const {return _p == cpy._p;}
  			bool		operator!=(const VectorIterator& cpy) const {return _p != cpy._p;}

			T&	operator*() const {return *_p;}
			T&	operator->() const {return *_p;}
/*--------------------output----------------*/
 // 			T&		operator*() {return _p;}
			

/*------------------Bidirectional---------------*/
			VectorIterator& operator--() {
				--_p;
				return *this;
			}

			VectorIterator	operator--(T) {
				VectorIterator tmp(*this);
				operator--();
				return tmp;
			}

			
		//	T&	operator--(
			

			

};
}


#endif
