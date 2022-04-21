#ifndef REVERSEITE_CLASS_HPP
# define REVERSEITE_CLASS_HPP

# include "utils.hpp"
# include "randomIterator.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator_map {
	protected:
		typedef Iterator	super;
		Iterator _start;
	public:
		typedef Iterator							iterator_type;
		typedef typename super::difference_type		difference_type;
		typedef typename super::reference			reference;
		typedef typename super::pointer				pointer;

		reverse_iterator_map(void);
		explicit reverse_iterator_map(Iterator x);
		template <class U> reverse_iterator_map(const reverse_iterator_map<U> &u);
		template <class U> reverse_iterator_map &operator=(const reverse_iterator_map<U> &u);
		Iterator base(void) const { return this->_start; };

		reference			operator*(void) const { return (--super(this->_start)).operator*(); };
		pointer				operator->(void) const { return &this->operator*(); };

		reverse_iterator_map	&operator++(void) { this->_start.operator--(); return *this; };
		reverse_iterator_map	operator++(int) { return reverse_iterator_map(this->_start.operator--(0)); };
		reverse_iterator_map	&operator--(void) { this->_start.operator++(); return *this; };
		reverse_iterator_map	operator--(int) { return reverse_iterator_map(this->_start.operator++(0)); };

		template <class U>
		difference_type		operator-(const reverse_iterator_map<U> &u) { return u.base().operator-(this->_start); };
		reverse_iterator_map	operator+ (difference_type n) const { return reverse_iterator_map(this->_start.operator-(n)); };
		reverse_iterator_map	&operator+=(difference_type n) { this->_start.operator-=(n); return *this; };
		reverse_iterator_map	operator- (difference_type n) const { return reverse_iterator_map(this->_start.operator+(n)); };
		reverse_iterator_map	&operator-=(difference_type n) { this->_start.operator+=(n); return *this; };
		reference			operator[](difference_type n) const { return *this->operator+(n); };

		friend reverse_iterator_map	operator+(difference_type n, const reverse_iterator_map &rhs)
			{ return rhs.operator+(n); };

		template <class U> bool	operator==(const reverse_iterator_map<U> &rhs) const { return this->_start.operator==(rhs.base()); };
		template <class U> bool	operator!=(const reverse_iterator_map<U> &rhs) const { return this->_start.operator!=(rhs.base()); };
		template <class U> bool	operator< (const reverse_iterator_map<U> &rhs) const { return this->_start.operator> (rhs.base()); };
		template <class U> bool	operator<=(const reverse_iterator_map<U> &rhs) const { return this->_start.operator>=(rhs.base()); };
		template <class U> bool	operator> (const reverse_iterator_map<U> &rhs) const { return this->_start.operator< (rhs.base()); };
		template <class U> bool	operator>=(const reverse_iterator_map<U> &rhs) const { return this->_start.operator<=(rhs.base()); };

};

template <class Iterator>
reverse_iterator_map<Iterator>::reverse_iterator_map(void) : _start() { };

template <class Iterator>
reverse_iterator_map<Iterator>::reverse_iterator_map(Iterator x) : _start(x) { };

template <class Iterator> template <class U>
reverse_iterator_map<Iterator>::reverse_iterator_map(const reverse_iterator_map<U> &u) : _start(u.base()) { };

template <class Iterator> template <class U>
reverse_iterator_map<Iterator>	&reverse_iterator_map<Iterator>::operator=(const reverse_iterator_map<U> &u) {
	if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
		return (*this);
	this->_start = u.base();
	return (*this);
};

} 

#endif 
