#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator>
	class reverse_iterator : public
		std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
		typename std::iterator_traits<Iterator>::value_type, typename std::iterator_traits<Iterator>::difference_type,
		typename std::iterator_traits<Iterator>::pointer, typename std::iterator_traits<Iterator>::reference> {

	public:
		typedef Iterator iterator_type;
		typedef typename std::iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename std::iterator_traits<Iterator>::reference		reference;
		typedef typename std::iterator_traits<Iterator>::pointer		pointer;

	private:
		pointer  _p;

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

		pointer getter()const {
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
			operator++();
			return tmp;
		}
		reverse_iterator& operator--() {
			++_p;
			return (*this);
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			operator--();
			return(tmp);
		}
		reverse_iterator operator+ (difference_type n) const {
			reverse_iterator ret;
			ret._p = _p - n;
			return (ret);
		}
		reverse_iterator& operator+=(difference_type n) {
			_p = _p - n;
			return (*this);
		}
		reverse_iterator operator- (difference_type n) const {
			reverse_iterator ret;
			ret._p = _p + n;
			return (ret);
		}
		reverse_iterator& operator-=(difference_type n) {
			_p = _p + n;
			return (*this);
		}
		reference operator[](difference_type n) const {
			return (*(_p - n-1));
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


	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x,const reverse_iterator<Iterator>& y) {
		return (x.base() + y.base());
	}

	template <class Iterator, class T>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x,const reverse_iterator<T>& y) {
		return (x.base() + y.base());
	}


	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return (x - n);
	}


//	template<class Iterator>
//	reverse_iterator<Iterator> opera


}

#endif
