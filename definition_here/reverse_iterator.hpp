#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iterator>
	class reverse_iterator : public
		iterator<typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type, typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference> {

	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename iterator_traits<Iterator>::reference		reference;
		typedef typename iterator_traits<Iterator>::pointer		pointer;

	private:
		pointer  _p;

	public :

		reverse_iterator() : _p(NULL) {}
		explicit reverse_iterator(pointer value ) : _p(value) {}
		explicit reverse_iterator(Iterator value) : _p(value.getter()) {}
		template <class U> reverse_iterator(const reverse_iterator<U>& u): _p(u.base()) {}


		iterator_type base()const {
			return (_p);
		}	
		
		pointer getter()const {
			return (_p);
		}
		reference operator*() const {
			pointer tmp = _p;

			return (*(--tmp));

		}
		pointer operator->() const {return &(operator*());}
		reverse_iterator& operator++() {
			--_p;
			return (*this);
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
			return (*(_p + n));
		}
	};
	template <class Iterator>
		bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
	return (x.base() == y.base());

	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() < y.base());
	}

	template <class Iterator>
	bool operator!=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() > y.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() >= y.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& x,const reverse_iterator<Iterator>& y) {
		return (x.base() <= y.base());
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x,const reverse_iterator<Iterator>& y) {
		return (x.base() - y.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return (x - n);
	}
}

#endif
