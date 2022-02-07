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
	
	public :
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type		value_type;	
		typedef typename Iterator::difference_type	difference_type;	
		typedef typename Iterator::pointer		pointer;	
		typedef typename Iterator::reference		reference;	

}; //to do


template<class T>
class iterator_traits<T*> {

	public :
		typedef random_access_iterator_tag	iterator_category;	
		typedef T		value_type;	
		typedef std::ptrdiff_t		difference_type;	
		typedef T*		pointer;	
		typedef T&		reference;
}; //to do


template<class T>
class iterator_traits<const T*> {
	public :
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

template<class T, class Distance = std::ptrdiff_t,
		class Pointer = T*, class Reference = T&>
class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T> {

		private :

  			T* _p;

		protected :
			
		public :

	
	//	typedef Category		iterator_category;	
		typedef T		value_type;	
		typedef Distance		difference_type;	
		typedef Pointer		pointer;	
		typedef Reference		reference;	


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
			VectorIterator& operator++(int) {
				++_p;
				return *this;
			}

			VectorIterator 	operator++(void) {
				VectorIterator tmp(*this);
				operator+(1); 
				return tmp;
			}


/*--------------------input----------------*/
 			bool 		operator==(const VectorIterator& cpy) const {return _p == cpy._p;}
  			bool		operator!=(const VectorIterator& cpy) const {return _p != cpy._p;}

			reference	operator*() const {return *_p;}
			reference	operator->() const {return *_p;}
/*--------------------output----------------*/
 // 			T&		operator*() {return _p;}
			

/*------------------Bidirectional---------------*/
			VectorIterator& operator--(int) {
				--_p;
				return *this;
			}

			VectorIterator	operator--(void) {
				VectorIterator tmp(*this);
				operator-(1);
				return tmp;
			}

			
		//	T&	operator--(
/*--------------------RandomAccess--------------------------*/	
			VectorIterator	operator+(difference_type n){
				VectorIterator	ret;
				ret._p = _p + n;
				return (ret);	
			}
		
			VectorIterator operator-(difference_type n) {
				VectorIterator	ret;
				ret._p = _p - n;
				return (ret);
			}

			VectorIterator operator+=(difference_type n) {
				_p = _p + n;
				return (*this);
			}	
			
			VectorIterator operator-=(difference_type n) {
				_p = _p - n;
				return (*this);
			}

			bool	operator<(VectorIterator& ptr) {
				if (_p < ptr._p)
					return (1);
				return (0);
			}

			bool	operator>(VectorIterator& ptr) {
				if (_p > ptr._p)
					return (1);
				return (0);
			}

			bool	operator<=(VectorIterator& ptr) {
				if (_p <= ptr._p)
					return (1);
				return (0);
			}

			bool	operator>=(VectorIterator& ptr) {
				if (_p >= ptr._p)
					return (1);
				return (0);
			}


			reference operator[](int n) {
				return (*(_p + n));

			}


};

/*-------------------------------------------fonction---------------------------------*/

			template<class VectorIterator>
			typename ft::iterator_traits<VectorIterator>::difference_type
			distance (VectorIterator first, VectorIterator last)
			{
				int i = 0;
				while (first != last)
				{
					i++;
					first = first+1;
				}	
				return (i);
			}


}


#endif
