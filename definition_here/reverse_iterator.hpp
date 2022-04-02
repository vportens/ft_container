#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "randomIterator.hpp"

namespace ft
{

template <class Iterator>
	class reverse_iterator : public
		ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
		typename ft::iterator_traits<Iterator>::value_type, typename ft::iterator_traits<Iterator>::difference_type,
		typename ft::iterator_traits<Iterator>::pointer, typename ft::iterator_traits<Iterator>::reference> {

	public:
		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference		reference;
		typedef typename ft::iterator_traits<Iterator>::pointer		pointer;

	private:
		iterator_type _p;

	public :

		reverse_iterator() : _p(NULL) {}
		explicit reverse_iterator(pointer value ) : _p(value) {}
		explicit reverse_iterator(Iterator value) : _p(value.getter()) {}
		explicit reverse_iterator(const reverse_iterator& cpy) : _p(cpy.getter()){}
		template <class U> reverse_iterator(const reverse_iterator<U>& u): _p(u.getter()) {}

		reverse_iterator& operator=(const reverse_iterator& cpy) {
		_p = cpy._p;
		return *this;
}

		iterator_type base()const {
			return (_p);
		}	
		
		 operator reverse_iterator<const Iterator> () const
       		         { return (reverse_iterator<const Iterator>(this->_p)); }

		iterator_type getter()const {
			return (_p);
		}
		reference operator*() const {
			iterator_type tmp = _p;

			return (*(--tmp));

		}
		pointer operator->() const {return &(operator*());}

		reverse_iterator& operator++() {
			--_p;
			return (*this);
		}

		reference operator[](int n) {
			return (base()[- n -1]);
		}
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		reverse_iterator& operator--() {
			++_p;
			return (*this);
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			--(*this);
			return(tmp);
		}
		reverse_iterator operator+ (difference_type n) const {
			return (reverse_iterator(_p - n));
			reverse_iterator ret;
			ret._p = _p - n;
			return (ret);
		}
		reverse_iterator& operator+=(difference_type n) {
			_p = _p - n;
			return (*this);
		}
		reverse_iterator operator- (difference_type n) const {
			return (reverse_iterator(_p + n));
			reverse_iterator ret;
			ret._p = _p + n;
			return (ret);
		}
		reverse_iterator& operator-=(difference_type n) {
			_p = _p + n;
			return (*this);
		}
		reference operator[](difference_type n) const {
			return (base()[- n-1]);
		}
	};
	template <class Iterator>
		bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
	return (x.base() == y.base());

	}

	template <class Iterator, class T>
		bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<T>& y) {
	return (x.base() == y.base());

	}



	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() > y.base());
	}

	template <class Iterator, class T>
	bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<T>& y) {
		return (x.base() > y.base());
	}

	template <class Iterator>
	bool operator!=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}

	template <class Iterator, class T>
	bool operator!=( const reverse_iterator<Iterator>& x, const reverse_iterator<T>& y) {
		return !(x == y);
	}




	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() < y.base());
	}

	template <class Iterator, class T>
	bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<T>& y) {
		return (x.base() < y.base());
	}


	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() <= y.base());
	}

	template <class Iterator, class T>
	bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<T>& y) {
		return (x.base() <= y.base());
	}


	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& x,const reverse_iterator<Iterator>& y) {
		return (x.base() >= y.base());
	}

	template <class Iterator, class T>
	bool operator<=(const reverse_iterator<Iterator>& x,const reverse_iterator<T>& y) {
		return (x.base() >= y.base());
	}
/*
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator>& y) {
		return (y.base()- n);
	}


	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x,const reverse_iterator<Iterator>& y) {
		return (x.base() - y.base());
	}

	template <class Iterator, class T>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x,const reverse_iterator<T>& y) {
		return (x.base() - y.base());
	}
*/
/*
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator+(const reverse_iterator<Iterator>& x,const reverse_iterator<Iterator>& y) {
		return (x.base() + y.base());
	}

	template <class Iterator, class T>
	typename reverse_iterator<Iterator>::difference_type operator+(const reverse_iterator<Iterator>& x,const reverse_iterator<T>& y) {
		return (x.base() - y.base());
	}
*/
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return (x + n);
	}


//	template<class Iterator>
//	reverse_iterator<Iterator> opera
    template <class Iterator>
        typename reverse_iterator<Iterator>::difference_type operator- (
            const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

    /* For reverser_iterator - const_reverse_iterator */
    template <class Iterator_L, class Iterator_R>
      typename reverse_iterator<Iterator_L>::difference_type operator- (const reverse_iterator<Iterator_L>& lhs,
                        const reverse_iterator<Iterator_R>& rhs) { return (rhs.base() - lhs.base()); }


}

#endif
