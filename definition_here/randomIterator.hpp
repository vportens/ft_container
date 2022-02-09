#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<typename Iterator>
struct iterator_traits;

template<typename Tp>
struct iterator_traits<Tp*> {

	public :
		typedef random_access_iterator_tag	iterator_category;	
		typedef Tp		value_type;	
		typedef std::ptrdiff_t		difference_type;	
		typedef Tp*		pointer;	
		typedef Tp&		reference;
}; //to do

/*
template<class Iterator>
struct iterator_traits {
	
	public :
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type		value_type;	
		typedef typename Iterator::difference_type	difference_type;	
		typedef typename Iterator::pointer		pointer;	
		typedef typename Iterator::reference		reference;	

}; //to do
*/



template<typename Tp>
struct iterator_traits<const Tp*> {
	public :
		typedef random_access_iterator_tag	iterator_category;	
		typedef Tp		value_type;	
		typedef std::ptrdiff_t		difference_type;	
		typedef const Tp*		pointer;	
		typedef const Tp&		reference;
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

		protected :
		typedef typename ft::iterator_traits<T> _trait;
		private :

  			T* _p;

		protected :
			
		public :

	
	//	typedef Category		iterator_category;	
		typedef T		value_type;	
		typedef Distance		difference_type;	
		typedef Pointer		pointer;	
		typedef Reference		reference;	
		typedef const T*		const_pointer;	
		typedef const T&		const_reference;


			VectorIterator(): _p(NULL) {}

			VectorIterator(pointer value) : _p(value) {}

	//		VectorIterator(const_pointer value) : _p(value) {}

 			VectorIterator(const VectorIterator& cpy) : _p(cpy._p){
			}
			
			VectorIterator&	operator=(const VectorIterator& cpy) {
				_p = cpy._p;
				return *this;
			};


			~VectorIterator() {};

/*----------all category--------------*/
			VectorIterator operator++(int) {
				VectorIterator tmp(*this);
				operator++(); 
				return tmp;
			}

			VectorIterator& 	operator++(void) {
				++_p;
				return *this;
			}


			pointer	getter() const {
				return (_p);
			}
/*--------------------input----------------*/



  			bool		operator!=(const VectorIterator& cpy) const {return _p != cpy._p;}

			reference	operator*() const {return *_p;}
			pointer		operator->() {return &(operator*());}
/*--------------------output----------------*/
 // 			T&		operator*() {return _p;}
			

/*------------------Bidirectional---------------*/
			VectorIterator operator--(int) {
				VectorIterator tmp(*this);
				operator--();
				return tmp;
			}

			VectorIterator&	operator--(void) {
				--_p;
				return *this;
			}

		//	VectorIterator&	operator--(VectorIterator& stc) {
		//		VectorIterator tmp = stc;		
		//		operator--();
		//		return *tmp;
		//	}

			
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

	     //           operator VectorIterator<const T> () const
       	//	         { return (VectorIterator<const T>(this->_p)); }

	        //        operator VectorIterator<const T> () const
       		  //       { return (VectorIterator<const T>(this->_p)); }

};
/*
template<class T, class Distance = std::ptrdiff_t,
		class Pointer = T*, class Reference = T&>
class ConstVectorIterator {
		private :

  		T* _p;

		public :	

		typedef T		value_type;	
		typedef Distance		difference_type;	

		typedef const T*		const_pointer;	
		typedef const T&		const_reference;


			ConstVectorIterator(): _p(NULL), _c(1) {}

			ConstVectorIterator(const_pointer value) : _p(value) , _c(1)  {}


 			ConstVectorIterator(const ConstVectorIterator& cpy) : _p(cpy._p), _c(1){
			}
			
			ConstVectorIterator&	operator=(const ConstVectorIterator& cpy) {
				_p = cpy._p;
				return *this;
			};


			~ConstVectorIterator() {};



};*/


/*-------------------------------------------fonction---------------------------------*/

			//typename ft::iterator_traits<VectorIterator>::difference_type
			template<class InputIterator>
			size_t distance(InputIterator first, InputIterator last)
			{
				size_t i = 0;
				while (first != last)
				{
					i++;
					first++;
				}	
				return (i);
			}

			template<typename T>
 			bool operator==(const ft::VectorIterator<T> ite1, const ft::VectorIterator<T> ite2) {return (ite1.getter() == ite2.getter());}

			template<typename T, typename T1>
			typename ft::VectorIterator<T>::different_type 
 			operator==(const ft::VectorIterator<T> ite1, const ft::VectorIterator<T1> ite2) {return ite1.getter() == ite2.getter();} 

		   	template <typename T>
    			typename ft::VectorIterator<T>::difference_type
 			operator-(const ft::VectorIterator<T> vec1, const ft::VectorIterator<T> vec2)
   			{
       				return (vec1.getter() - vec2.getter());
   			}


}


#endif
